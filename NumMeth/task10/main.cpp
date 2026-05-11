#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <fstream>
#include <limits>
#include <set>


using namespace std;

// Function f(x)
double f(double x, int mode) {
    switch (mode) {
        case 1:
            return 0.2 * pow(x, 5) + pow(x, 3) + 5.0 * x + 1.0;
            break;
        case 2:
            return 1.0 / (1.0 + 25.0 * x * x);
            break;
        case 3:
            if (x < 0) return -1;
            else if (x > 0) return 1;
            else return 0;
        default:
            return abs(x);
    }
}
// Derivative of f(x)
double fDer(double x, int mode) {
    switch (mode) {
        case 1:
            return pow(x, 4) + 3.0 * pow(x, 2) + 5.0;
            break;
        case 2:
            return - (50.0 * x) / pow(1.0 + 25.0 * x * x, 2);
            break;
        default:
            return x ? 0: 1;
    }
}

// Pattern for x
vector<double> points(double a, double b, int n, int mode) {
    vector<double> x(n);
    switch (mode) {
        case 1: {
            double h = (b - a) / (n - 1);
            for (int i = 0; i < n; i++) 
                x[i] = a + i * h;
            break;
        }
        case 2: {
            for (int i = 0; i < n; i++)
                x[i] = 0.5 * (a + b) + 0.5 * (b - a) * cos((2 * i + 1) * M_PI / (2 * n));
            break;
        }
        default: {
            set<int> unique_set;
            unique_set.insert(0);
            while (unique_set.size() < n)
                unique_set.insert(a + (b - a) * rand() / RAND_MAX);
            x.insert(x.end(), unique_set.begin(), unique_set.end());
        }
    }
    return x;
}

// Function to solve system using Gaussian elimination
vector<double> solveSystem(const vector<double>& x, vector<double> y) {
    vector<vector<double>> A(4, vector<double>(4));
    
    // Construct matrix
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            A[i][j] = pow(x[i], j);
        }
    }
    for (int i = 2; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            A[i][j] = pow(x[i], j - 1) * j;
        }
    }
    
    // Gaussian elimination
    for (int i = 0; i < 4; i++) {
        // Find pivot
        int maxRow = i;
        for (int k = i + 1; k < 4; k++) {
            if (abs(A[k][i]) > abs(A[maxRow][i])) {
                maxRow = k;
            }
        }
        
        // Swap rows
        swap(A[i], A[maxRow]);
        swap(y[i], y[maxRow]);
        
        // Make diagonal 1 and eliminate below
        double pivot = A[i][i];
        for (int j = i; j < 4; j++) {
            A[i][j] /= pivot;
        }
        y[i] /= pivot;
        
        for (int k = i + 1; k < 4; k++) {
            double factor = A[k][i];
            for (int j = i; j < 4; j++) {
                A[k][j] -= factor * A[i][j];
            }
            y[k] -= factor * y[i];
        }
    }
    
    // Back substitution
    vector<double> a(4);
    for (int i = 3; i >= 0; i--) {
        a[i] = y[i];
        for (int j = i + 1; j < 4; j++) {
            a[i] -= A[i][j] * a[j];
        }
    }
    
    return a;
}

// Evaluate polynomial given coefficients (power form)
double evalPoly(const vector<double>& a, double x) {
    double result = a[a.size() - 1];
    for (int i = a.size() - 2; i >= 0; i--) {
        result = result * x + a[i];
    }
    return result;
}

void plot_simple() {
    FILE* gnuplot = popen("gnuplot -persist", "w");
    
    fprintf(gnuplot, "set multiplot layout 2,1 title 'Interpolation Results'\n");
    
    // First plot - interpolation
    fprintf(gnuplot, "set xlabel 'x'\n");
    fprintf(gnuplot, "set ylabel 'f(x)'\n");
    fprintf(gnuplot, "set grid\n");
    fprintf(gnuplot, "plot 'in.txt' using 1:2 with points pt 7 ps 2 lc rgb 'red' title 'Points', \\\n");
    fprintf(gnuplot, "     'out.txt' using 1:2 with lines lw 2 lc rgb 'blue' title 'f(x)', \\\n");
    fprintf(gnuplot, "     'out.txt' using 1:3 with lines lw 2 lc rgb 'green' title 'S3'\n");
    
    // Second plot - error
    fprintf(gnuplot, "set xlabel 'x'\n");
    fprintf(gnuplot, "set ylabel 'Error'\n");
    fprintf(gnuplot, "set grid\n");
    fprintf(gnuplot, "plot 'out.txt' using 1:4 with lines lw 2 lc rgb 'red' title 'Err(x)', \\\n");
    fprintf(gnuplot, "     0 with lines lt 0 lc rgb 'gray' notitle\n");
    
    fprintf(gnuplot, "unset multiplot\n");
    pclose(gnuplot);
}

int main() {
    // Define interval [a, b]
    double a = -1.0;
    double b = 1.0;
    int n = 10; // number of points
    // Type of pattern for x and function f
    int mode_x = 1;
    int mode_f = 3;
    
    // Generate points 
    vector<double> x_orig = points(a, b, n, mode_x);
    
    // Calculate f(x) for original points
    vector<double> y_orig(n);
    for (int i = 0; i < n; i++) {
        y_orig[i] = f(x_orig[i], mode_f);
    }

    // Calculate derivative of f(x)
    vector<double> f_der(n);
    for (int i = 0; i < n; i++) {
        f_der[i] = fDer(x_orig[i], mode_f);
    }
    
    // Write to in.txt
    ofstream inFile("in.txt");
    inFile << fixed << setprecision(15);

    // Write header
    inFile <<  left << setw(25) << "            x" 
           << " " << setw(25) << "          f(x)" 
           << " " << setw(25) << "          d(x)" << endl;


    for (int i = 0; i < n; i++) {
        inFile << right << setw(25) << x_orig[i] << " " << setw(25) << y_orig[i] << " " << setw(25) << f_der[i] << endl;
    }
    inFile.close();
    
    // Write to out.txt
    ofstream outFile("out.txt");
    outFile << fixed << setprecision(5);
    
    // Write header
    outFile << left
            << setw(15) <<  "       x" << " "
            << setw(15) << "    f(x)" << " "
            << setw(15) << "    S3(x)" << " "
            << setw(15) << "     Err(x)" << endl;
    
    // Evaluate and write results
    for (int i = 0; i < n - 1; i++) {
        // Generate extra points
        double hi = x_orig[i + 1] - x_orig[i];
        double x1 = x_orig[i] + hi / 3.0;
        double x2 = x_orig[i] + 2.0 * hi / 3.0;

        // Solve system to get coefficients for S3
        vector<double> x_i = {x_orig[i], x_orig[i + 1], x_orig[i], x_orig[i + 1]};
        vector<double> f_i = {f(x_orig[i], mode_f), f(x_orig[i + 1], mode_f), f_der[i], f_der[i + 1]};
        vector<double> coeff = solveSystem(x_i, f_i);
    
        // Calculate output
        for (double xx : {x_orig[i], x1, x2, x_orig[i + 1]}) {
            double f_val = f(xx, mode_f);   
            double S3 = evalPoly(coeff, xx);
            double err = f_val - S3;
        
            outFile << right 
                    << setw(15) << xx << " "
                    << setw(15) << f_val << " "
                    << setw(15) << S3 << " "
                    << setw(15) << err << endl;
        }
    }
    
    outFile.close();
    
    cout << "Files generated successfully!" << endl;
    cout << "Check in.txt and out.txt for results." << endl;
    cout << "Plotting results..." << endl;
    plot_simple();
    
    return 0;
}
