#include "ratio_inter.hpp"

using namespace std;


int main() {
    // Define interval [a, b]
    double a = -1.0;
    double b = 1.0;
    int n = 10; // number of points
    // Type of pattern for x 
    // 1 - Uniform
    // 2 - Chebyshev
    // 3 - Random
    int mode_x = 1;
    // and function f
    // 1 - 0.2*x^5 + x^3 + 5.0*x + 1.0
    // 2 - Runge
    // 3 - Sign
    // 4 - Abs
    int mode_f = 3;

    // Write to in.txt
    fill_out_infile("in.txt", a, b, n, mode_x, mode_f);

    cout << "Edit 'int.txt' and press 'Enter' to continue..." << endl;
    cin.sync();
    cin.get();

    vector<double> x;
    vector<double> f;
    vector<double> d;
    int rep = parsingFile("in.txt", x, f, d);
    if (rep) return -1;
    
    vector<double> h(n - 1);
    for (int i = 0; i < n - 1; i++) {
        h[i] = x[i + 1] - x[i];
    }

    vector<double> delta(n - 1);
    for (int i = 0; i < n - 1; i++) {
        delta[i] = (f[i + 1] - f[i]) / h[i];
    }

    vector<double> r(n - 1);
    for (int i = 0; i < n - 1; i++) {
        r[i] = abs(delta[i]) > numeric_limits<double>::min() ? 1.0 + (d[i + 1] + d[i]) / delta[i] : 3.0;
    }

    // Write to out.txt
    ofstream outFile("out.txt");
    outFile << fixed << setprecision(5);
    
    // Write header
    outFile << left
            << setw(15) <<  "       x" << " "
            << setw(15) << "    f(x)" << " "
            << setw(15) << "    SR(x)" << " "
            << setw(15) << "     Err(x)" << endl;
    
    // Evaluate and write results
    for (int i = 0; i < n - 1; i++) {
        // Generate extra points
        double x1 = x[i] + h[i] / 8.0;
        double x2 = x[i] + 2.0 * h[i] / 8.0;
        double x3 = x[i] + 3.0 * h[i] / 8.0;
        double x4 = x[i] + 4.0 * h[i] / 8.0;
        double x5 = x[i] + 5.0 * h[i] / 8.0;
        double x6 = x[i] + 6.0 * h[i] / 8.0;
        double x7 = x[i] + 7.0 * h[i] / 8.0;

        // Calculate coefficients
        double A = f[i];
        double D = f[i + 1];
        double B = r[i] * f[i] + h[i] * d[i];
        double C = r[i] * f[i + 1] - h[i] * d[i + 1];

        // Calculate S = P / Q
        auto P = [=](double t) -> double {
            return A * pow(1 - t, 3) + B * t * pow(1 - t, 2) + C * pow(t, 2) * (1 - t) + D * pow(t, 3);
        };
    
        auto Q = [=](double t) -> double {
            return pow(1 - t, 3) + r[i] * t * pow(1 - t, 2) + r[i] * pow(t, 2) * (1 - t) + pow(t, 3);
        };

        // Calculate output
        for (double xx : {x[i], x1, x2, x3, x4, x5, x6, x7}) {
            double t = (xx - x[i]) / h[i];
            outFile << right 
                    << setw(15) << xx << " "
                    << setw(15) << func(xx, mode_f) << " "
                    << setw(15) << P(t) / Q(t) << " "
                    << setw(15) << func(xx, mode_f) - P(t) / Q(t) << endl;
        }

        if (i == n - 2) {
            outFile << right 
                    << setw(15) << x[n - 1] << " "
                    << setw(15) << func(x[n - 1], mode_f) << " "
                    << setw(15) << P(1.0) / Q(1.0) << " "
                    << setw(15) << func(x[n - 1], mode_f) - P(1.0) / Q(1.0) << endl;
        }
    }
    
    outFile.close();
    
    cout << "Files generated successfully!" << endl;
    cout << "Check out.txt for results." << endl;
    cout << "Plotting results..." << endl;
    plotSimple();
    
    return 0;
}
