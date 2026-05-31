#include "ratio_inter.hpp"

using namespace std;


// Function f(x)
double func(const double x, const int mode) {
    switch (mode) {
        case 1: //0.2*x^5 + x^3 + 5.0*x + 1.0
            return 0.2 * pow(x, 5) + pow(x, 3) + 5.0 * x + 1.0;
            break;
        case 2: //Runge
            return 1.0 / (1.0 + 25.0 * x * x);
            break;
        case 3: //Sign
            if (x < - numeric_limits<double>::min()) return -1;
            else if (x > numeric_limits<double>::min()) return 1;
            else return 0;
            break;
        default:
            return abs(x);
    }
}

// Derivative of f(x)
double fDer(const double x, const int mode) {
    switch (mode) {
        case 1:
            return pow(x, 4) + 3.0 * pow(x, 2) + 5.0;
            break;
        case 2:
            return - (50.0 * x) / pow(1.0 + 25.0 * x * x, 2);
            break;
        case 3:
            return abs(x) > numeric_limits<double>::min() ? 0: 1;
            break;
        default:
            if (x < - numeric_limits<double>::min()) return -1;
            else if (x > numeric_limits<double>::min()) return 1;
            else return 0;
    }
}

// Pattern for x
vector<double> points(const double a, const double b, const int n, const int mode) {
    vector<double> x(n);
    switch (mode) {
        case 1: { //Uniform
            double h = (b - a) / (n - 1);
            for (int i = 0; i < n; i++) 
                x[i] = a + i * h;
            break;
        }
        case 2: { //Chebyshev
            for (int i = 0; i < n; i++)
                x[i] = 0.5 * (a + b) + 0.5 * (b - a) * cos((2 * i + 1) * M_PI / (2 * n));
            break;
        }
        default: { //Random
            set<double> unique_set;
            unique_set.insert(0);
            while (unique_set.size() < n)
                unique_set.insert(a + (b - a) * rand() / RAND_MAX);
            x.assign(unique_set.begin(), unique_set.end());
        }
    }
    return x;
}

void fill_out_infile(const string& fileName, const double a, const double b, const int n, const int mode_x, const int mode_f) {
    // Generate points 
    vector<double> x_orig = points(a, b, n, mode_x);
    
    // Calculate f(x) for original points
    vector<double> y_orig(n);
    for (int i = 0; i < n; i++) {
        y_orig[i] = func(x_orig[i], mode_f);
    }

    // Calculate derivative of f(x)
    vector<double> f_der(n);
    for (int i = 0; i < n; i++) {
        f_der[i] = fDer(x_orig[i], mode_f);
    }
    
    // Write to in.txt
    ofstream inFile(fileName);
    // Write N
    inFile << "#N = " << n << endl;
    inFile << fixed << setprecision(15);

    // Write header
    inFile <<  left << setw(25) << "            x" 
           << " " << setw(25) << "          f(x)" 
           << " " << setw(25) << "          d(x)" << endl;


    for (int i = 0; i < n; i++) {
        inFile << right << setw(25) << x_orig[i] << " " << setw(25) << y_orig[i] << " " << setw(25) << f_der[i] << endl;
    }
    inFile.close();
}

int parsingFile(const string& fileName, vector<double>& x, vector<double>& f, vector<double>& d) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Cannot open file" << endl;
        return -1;
    }

    string line;

    // Read N from comment line
    getline(file, line);
    int n;
    sscanf(line.c_str(), "#N = %d", &n);

    // Skip header line
    getline(file, line);

    // Read data points
    for (int i = 0; i < n; i++) {
        getline(file, line);
        istringstream iss(line);
        double xi, fi, di;
        iss >> xi >> fi >> di;
        x.push_back(xi);
        f.push_back(fi);
        d.push_back(di);
    }

    file.close();

    return 0;
}

void plotSimple() {
    FILE* gnuplot = popen("gnuplot -persist", "w");
    
    fprintf(gnuplot, "set multiplot layout 2,1 title 'Interpolation Results'\n");
    
    // First plot - interpolation
    fprintf(gnuplot, "set xlabel 'x'\n");
    fprintf(gnuplot, "set ylabel 'f(x)'\n");
    fprintf(gnuplot, "set grid\n");
    fprintf(gnuplot, "plot 'in.txt' using 1:2 with points pt 7 ps 2 lc rgb 'red' title 'Points', \\\n");
    fprintf(gnuplot, "     'out.txt' using 1:2 with lines lw 2 lc rgb 'blue' title 'f(x)', \\\n");
    fprintf(gnuplot, "     'out.txt' using 1:3 with lines lw 2 lc rgb 'green' title 'SR'\n");
    
    // Second plot - error
    fprintf(gnuplot, "set xlabel 'x'\n");
    fprintf(gnuplot, "set ylabel 'Error'\n");
    fprintf(gnuplot, "set grid\n");
    fprintf(gnuplot, "plot 'out.txt' using 1:4 with lines lw 2 lc rgb 'red' title 'Err(x)', \\\n");
    fprintf(gnuplot, "     0 with lines lt 0 lc rgb 'gray' notitle\n");
    
    fprintf(gnuplot, "unset multiplot\n");
    pclose(gnuplot);
}