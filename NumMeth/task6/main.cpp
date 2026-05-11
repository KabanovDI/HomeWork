#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <functional>
#include "myfun.h"

using namespace std;


int main() {
    // Parameters for variant 7
    double x0 = -5.0;
    double y0 = exact_solution(x0);
    double x_end = 15.0;
    double h0 = 0.01;
    double eps = 1e-4;
    double mean_h;

    cout << "==============================================" << endl;
    cout << "VARIANT 7 SOLUTION" << endl;
    cout << "ODE: y' = 2(2-x)y + (x+2)*exp(3x-x^2)" << endl;
    cout << "Initial conditions: x0 = " << x0 << ", y0 = " << y0 << endl;
    cout << "Integration interval: [" << x0 << ", " << x_end << "]" << endl;
    cout << "Initial step: h0 = " << h0 << endl;
    cout << "Tolerance: eps = " << eps << endl;
    cout << "Step control method: Doubling/halving" << endl;
    cout << "==============================================" << endl << endl;
    
    // 1. Solution with automatic step (Runge's rule)
    cout << "1. AUTOMATIC STEP SELECTION (RUNGE'S RULE)" << endl;
    auto sol1 = solve_auto_step(method1, mean_h, x0, y0, x_end, 5, h0, eps);
    cout << "Mean h: " << mean_h << endl;
    cout << "Final point: x = " << sol1.back().first 
         << ", y = " << sol1.back().second << endl;
    cout << "Absolute error: " << fabs(sol1.back().second - exact_solution(sol1.back().first)) << endl << endl;

    // 2. Solution with automatic step (combination of formulas)
    cout << "2. AUTOMATIC STEP SELECTION (COMBINATION OF FORMULAS)" << endl;
    auto sol2 = solve_auto_step(method2, mean_h, x0, y0, x_end, 6, h0, eps);
    cout << "Final point: x = " << sol2.back().first 
         << ", y = " << sol2.back().second << endl;
    cout << "Absolute error: " << fabs(sol2.back().second - exact_solution(sol2.back().first)) << endl << endl;

    // 3. Solution with automatic step (control term)
    cout << "3. AUTOMATIC STEP SELECTION (CONTROL TERM)" << endl;
    auto sol3 = solve_auto_step(method3, mean_h, x0, y0, x_end, 6, h0, eps);
    cout << "Final point: x = " << sol3.back().first 
         << ", y = " << sol3.back().second << endl;
    cout << "Absolute error: " << fabs(sol3.back().second - exact_solution(sol3.back().first)) << endl << endl;

    // 4. Solution with constant step (average from method 1)
    cout << "4. CONSTANT STEP (AVERAGE FROM METHOD 1)" << endl;
    auto sol4 = solve_constant_step(x0, y0, x_end, mean_h);
    cout << "Final point: x = " << sol4.back().first 
         << ", y = " << sol4.back().second << endl;
    double abs_err = fabs(sol4.back().second - exact_solution(sol4.back().first));
    cout << "Absolute error: " << abs_err << endl;
    //cout << "Order: " << log(abs_err)/log(h0) << endl << endl;

    // Save results to files for plotting
    ofstream file1("solution_1.txt");
    ofstream file2("solution_2.txt");
    ofstream file3("solution_3.txt");
    ofstream file4("solution_4.txt");
    ofstream file5("solution_5.txt");
    ofstream file_exact("exact_solution.txt");

    file1 << fixed << setprecision(10);
    file2 << fixed << setprecision(10);
    file3 << fixed << setprecision(10);
    file4 << fixed << setprecision(10);
    file5 << fixed << setprecision(10);
    file_exact << fixed << setprecision(10);

    double prev = x0;
    for (auto& point : sol1) {
        file1 << point.first << " " << point.second << endl;
        file5 << point.first << " " << point.first - prev << endl;
        prev = point.first;
    }
    
    for (auto& point : sol2) {
        file2 << point.first << " " << point.second << endl;
    }

    for (auto& point : sol3) {
        file3 << point.first << " " << point.second << endl;
    }

    for (auto& point : sol4) {
        file4 << point.first << " " << point.second << endl;
    }
    /*
    for (int n = 1; n<6; n++){
        auto sol4 = solve_constant_step(x0, y0, x_end, pow(10, -n));
        double abs_err = fabs(sol4.back().second - exact_solution(sol4.back().first));
        file4 << pow(10, -n) << " " << abs_err << endl;
    }*/
    // Generate exact solution at many points
    int n_points = 1000;
    for (int i = 0; i <= n_points; i++) {
        double x = x0 + i * (x_end - x0) / n_points;
        file_exact << x << " " << exact_solution(x) << endl;
    }

    file1.close();
    file2.close();
    file3.close();
    file4.close();
    file5.close();
    file_exact.close();
    
    cout << "Results saved to files" << endl;
    
    return 0;
}
