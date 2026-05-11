#ifndef MYFUN_H
#define MYFUN_H

#include <functional>
#include <vector>

using namespace std;


double exact_solution(double x);
double f(double x, double y);
void rk4_step(double x, double& y, double h);
pair<double, double> method1(double x, double y, double h);
void rk5_step(double x, double& y, double h);
pair<double, double> method2(double x, double y, double h);
pair<double, double> method3(double x, double y, double h);
vector<pair<double, double>> solve_auto_step(function<pair<double, double>(double, double, double)> method, double& mean_h,
                                               double x0, double y0, double x_end, int nu, double h0, double eps);
vector<pair<double, double>> solve_constant_step(double x0, double y0, double x_end, double h);

#endif