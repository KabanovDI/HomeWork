#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <functional>
#include "myfun.h"

using namespace std;


// Exact solution for the given ODE: y' = 2(2-x)y + (x+2)*exp(3x-x^2)
double exact_solution(double x) {
    //double C = 10.0 * exp(-3.0) + 4.0 * exp(-1.0);
    //return exp(4.0*x - x*x) * (C - exp(-x) * (x + 3.0));
    return exp(-pow(x - 1,2)/2);
}

// Right-hand side function
double f(double x, double y) {
    //return 2.0 * (2.0 - x) * y + (x + 2.0) * exp(3.0*x - x*x);
    return -(x - 1) * y;
}

// Classical 4th order Runge-Kutta (formula 4.1)
void rk4_step(double x, double& y, double h) {
    double k1 = h * f(x, y);
    double k2 = h * f(x + h/2.0, y + k1/2.0);
    double k3 = h * f(x + h/2.0, y + k2/2.0);
    double k4 = h * f(x + h, y + k3);
    
    y = y + (k1 + 2.0*k2 + 2.0*k3 + k4) / 6.0;
}

// Runge's rule for error estimation in 4.1(with halving step)
pair<double, double> method1(double x, double y, double h) {
    // One step with h
    double y_h = y;
    rk4_step(x, y_h, h);
    
    // Two steps with h/2
    double y_h2 = y;
    rk4_step(x, y_h2, h/2.0);
    rk4_step(x + h/2.0, y_h2, h/2.0);
    
    // Error estimate for y_h (more accurate)
    double error = (y_h2 - y_h) / (1.0 - pow(2.0, -4));
    
    return {y_h, error};
}

// 5th order Runge-Kutta (formula 5.1)
void rk5_step(double x, double& y, double h) {
    double k1 = h * f(x, y);
    double k2 = h * f(x + h/2.0, y + k1/2.0);
    double k3 = h * f(x + h/2.0, y + 1.0/4.0*(k1 + k2));
    double k4 = h * f(x + h, y - k2 + 2.0*k3);
    double k5 = h * f(x + 2.0*h/3.0, y + (7.0*k1 + 10.0*k2 + k4)/27.0);
    double k6 = h * f(x + h/5.0, y + (28.0*k1 - 125.0*k2 + 546.0*k3 + 54.0*k4 - 378.0*k5)/625.0);
    
    y = y + k1/24.0 + 5.0*k4/48.0 + 27.0*k5/56.0 + 125.0*k6/336.0;
}

// Error estimation with 4.1 and 5.1(with halving step)
pair<double, double> method2(double x, double y, double h) {
    // One step with 4.1
    double y_h = y;
    rk4_step(x, y_h, h);
    
    // One step with 5.1
    double y_h2 = y;
    rk5_step(x, y_h2, h);
    
    // Error estimate for y_h (more accurate)
    double error = y_h2 - y_h;
    
    return {y_h, error};
}

// Method with control term (formula 5.1K)
pair<double, double> method3(double x, double y, double h) {
    // One step with 4.1
    double y_h = y;
    rk4_step(x, y_h, h);
    
    // Estimation control term
    double k1 = h * f(x, y);
    double k2 = h * f(x + h/2.0, y + k1/2.0);
    double k3 = h * f(x + h/2.0, y + 1.0/4.0*(k1 + k2));
    double k4 = h * f(x + h, y - k2 + 2.0*k3);
    double k5 = h * f(x + 2.0*h/3.0, y + (7.0*k1 + 10.0*k2 + k4)/27.0);
    double k6 = h * f(x + h/5.0, y + (28.0*k1 - 125.0*k2 + 546.0*k3 + 54.0*k4 - 378.0*k5)/625.0);
    
    double control = (-42.0*k1 - 224.0*k3 - 21.0*k4 + 162.0*k5 + 125.0*k6)/336.0;
    
    return {y_h, control};
}

// Automatic step selection using doubling/halving
vector<pair<double, double>> solve_auto_step(function<pair<double, double>(double, double, double)> method, double& mean_h,
                                               double x0, double y0, double x_end, int nu, double h0, double eps) {                                              
    vector<pair<double, double>> solution;
    solution.push_back({x0, y0});
    
    double x = x0;
    double y = y0;
    double h = h0;
    double step_count = 0;
    
    while (x < x_end - 1e-10) {
        if (x + h > x_end) {
            h = x_end - x;
        }
        
        auto [y_next, error] = method(x, y, h);
        
        if (fabs(error) > eps) {
            // Step rejected, halve step
            h = h / 2.0;
            continue;
        }
        
        // Step accepted
        x = x + h;
        y = y_next;
        solution.push_back({x, y});
        step_count++;
        
        // Adjust step for next iteration
        if (fabs(error) < (eps / pow(2.0, nu))) {  // K = 2^nu
            h = 2.0 * h;  // Double step
        }
        // Else keep same step
    }
    
    mean_h = (x - x0)/step_count;
    return solution;
}

// Solve with constant step
vector<pair<double, double>> solve_constant_step(double x0, double y0, double x_end, double h) {                                                 
    vector<pair<double, double>> solution;
    solution.push_back({x0, y0});
    
    double x = x0;
    double y = y0;
    
    while (x < x_end - 1e-10) {
        double step = h;
        if (x + step > x_end) {
            step = x_end - x;
        }
        
        rk4_step(x, y, step);
        x = x + step;
        //cout << error << endl;
        
        solution.push_back({x, y});
    }
    
    return solution;
}
