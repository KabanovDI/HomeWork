#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <fstream>
#include <filesystem>
#include "myfun.h"


using namespace std;
namespace fs = filesystem;


int main() 
{
    string data_dir = "data";
    string graphs_dir = "graphs";
    fs::create_directories(data_dir);
    fs::create_directories(graphs_dir);

    vector<double> A_values = { 1.0, 10.0, 100.0 };
    vector<int> n_values = { 1, 2, 3, 6 };

    // Vector of functions for all schemes
    vector<function<double(double, double, vector<double>&)>> schemes = {
        scheme1, scheme2, scheme3, scheme4, scheme5, scheme6
    };

    cout << scientific << setprecision(3);

    for (double A : A_values) {
        cout << "\n==============================================================\n";
        cout << "RESULTS FOR A = " << A << "\n";
        cout << "================================================================\n";
        cout << "Scheme|    E1    |    E2    |    E3    |    E6    |   Order m  |\n";
        cout << "------|----------|----------|----------|----------|------------|\n";

        for (int scheme_num = 0; scheme_num < 5; scheme_num++) {
            vector<double> errors;
            vector<double> y; 

            // Calculate errors for different h
            for (int n : n_values) {
                double h = pow(10.0, -n);
                double error = schemes[scheme_num](A, h, y);
                errors.push_back(error);
            }

            // Calculate the order of convergence
            double m = calculate_order(errors, n_values);

            // Display the results
            cout << setw(4) << scheme_num + 1 << "  | "
                << setw(6) << errors[0] << " | "
                << setw(6) << errors[1] << " | "
                << setw(6) << errors[2] << " | "
                << setw(6) << errors[3] << " | "
                << fixed << setw(8) << setprecision(2) << m
                << scientific << "     |\n";
        }
    }

    // Plotting graphs for all schemes and all A
    for (double A : A_values) {
        for (int scheme_num = 0; scheme_num < 5; scheme_num++) {
            plot_scheme(scheme_num + 1, A, schemes[scheme_num], data_dir);
        }
    }
    cout << "  python3 plot_schemes.py\n\n";

    return 0;
}
