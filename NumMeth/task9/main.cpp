#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

// Function f(x) = sin(x) as an example 
double f(double x) {
    return sin(x);
}

// Function to solve Vandermonde system using Gaussian elimination
vector<double> solveVandermonde(const vector<double>& x, const vector<double>& y) {
    int n = x.size();
    vector<vector<double>> A(n, vector<double>(n));
    vector<double> b = y;
    
    // Construct Vandermonde matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = pow(x[i], j);
        }
    }
    
    // Gaussian elimination
    for (int i = 0; i < n; i++) {
        // Find pivot
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (abs(A[k][i]) > abs(A[maxRow][i])) {
                maxRow = k;
            }
        }
        
        // Swap rows
        swap(A[i], A[maxRow]);
        swap(b[i], b[maxRow]);
        
        // Make diagonal 1 and eliminate below
        double pivot = A[i][i];
        for (int j = i; j < n; j++) {
            A[i][j] /= pivot;
        }
        b[i] /= pivot;
        
        for (int k = i + 1; k < n; k++) {
            double factor = A[k][i];
            for (int j = i; j < n; j++) {
                A[k][j] -= factor * A[i][j];
            }
            b[k] -= factor * b[i];
        }
    }
    
    // Back substitution
    vector<double> a(n);
    for (int i = n - 1; i >= 0; i--) {
        a[i] = b[i];
        for (int j = i + 1; j < n; j++) {
            a[i] -= A[i][j] * a[j];
        }
    }
    
    return a;
}

// Evaluate polynomial given coefficients (power form)
double evalPoly(const vector<double>& coeff, double x) {
    double result = 0;
    double xpow = 1;
    for (int i = 0; i < coeff.size(); i++) {
        result += coeff[i] * xpow;
        xpow *= x;
    }
    return result;
}

// Lagrange interpolation
double lagrangeInterp(const vector<double>& x, const vector<double>& y, double x_eval) {
    int n = x.size();
    double result = 0;
    
    for (int i = 0; i < n; i++) {
        double term = y[i];
        for (int j = 0; j < n; j++) {
            if (j != i) {
                term *= (x_eval - x[j]) / (x[i] - x[j]);
            }
        }
        result += term;
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
    fprintf(gnuplot, "     'out.txt' using 1:2 with lines lw 2 lc rgb 'blue' title 'Vandermonde', \\\n");
    fprintf(gnuplot, "     'out.txt' using 1:3 with lines lw 2 lc rgb 'green' title 'Lagrange'\n");
    
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
    double a = 0.0;
    double b = 10.0;
    int n = 5; // number of points
    
    // Generate points according to some law (here: equally spaced)
    vector<double> x_orig(n);
    for (int i = 0; i < n; i++) {
        x_orig[i] = a + i * (b - a) / n;
    }
    
    // Calculate f(x) for original points
    vector<double> y_orig(n);
    for (int i = 0; i < n; i++) {
        y_orig[i] = f(x_orig[i]);
    }
    
    // Write to in.txt
    ofstream inFile("in.txt");
    inFile << fixed << setprecision(15);

    // Write header
    inFile <<  left << setw(25) << "            x" 
           << " " << setw(25) << "          f(x)" << endl;

    for (int i = 0; i < n; i++) {
        inFile << right << setw(25) << x_orig[i] << " " << setw(25) << y_orig[i] << endl;
    }
    inFile.close();
    
    // Solve Vandermonde system to get coefficients for Pn-1
    vector<double> coeff = solveVandermonde(x_orig, y_orig);
    
    // Generate all evaluation points
    vector<double> x_eval;
    vector<double> x_extra;
    
    // Add original points and extra points
    for (int i = 0; i < n - 1; i++) {
        double hi = x_orig[i + 1] - x_orig[i];
        
        // Original point
        x_eval.push_back(x_orig[i]);
        
        // Extra points
        x_eval.push_back(x_orig[i] + hi / 3.0);
        x_eval.push_back(x_orig[i] + 2.0 * hi / 3.0);
        
        // Store extra points separately for reference
        x_extra.push_back(x_orig[i] + hi / 3.0);
        x_extra.push_back(x_orig[i] + 2.0 * hi / 3.0);
    }
    // Add last original point
    x_eval.push_back(x_orig[n - 1]);
    
    // Write to out.txt
    ofstream outFile("out.txt");
    outFile << fixed << setprecision(5);
    
    // Write header
    outFile << left
            << setw(15) <<  "       x" << " "
            << setw(15) << "    Pn-1(x)" << " "
            << setw(15) << "    Ln-1(x)" << " "
            << setw(15) << "     Err(x)" << endl;
    
    // Evaluate and write results
    for (double x : x_eval) {
        double p_val = evalPoly(coeff, x);
        double l_val = lagrangeInterp(x_orig, y_orig, x);
        double err = f(x) - p_val;
        
        outFile << right 
                << setw(15) << x << " "
                << setw(15) << p_val << " "
                << setw(15) << l_val << " "
                << setw(15) << err << endl;
    }
    
    outFile.close();
    
    cout << "Files generated successfully!" << endl;
    cout << "Check in.txt and out.txt for results." << endl;
    cout << "\nPlotting results..." << std::endl;
    plot_simple();
    
    return 0;
}
