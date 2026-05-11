#ifndef MYFUN_H
#define MYFUN_H

#include <vector>
#include <functional>
#include <string>

using namespace std;


void filling_mat(vector<vector<double>>& mat, double h, int size);
void find_vect(vector<vector<double>>& vectors, int size, int N);
void find_values(vector<double>& values, int size, int N, double h);
void find_errors(vector<vector<double>>& errors, int size, vector<vector<double>>& mat, vector<vector<double>>& vectors, vector<double>& values);
double max_error(vector<vector<double>>& errors, int size);
double max_error_normalized(vector<vector<double>>& errors, vector<double>& values, int size);
double scal_mult(vector<double>& vect1, vector<double>& vect2, int size);

double exact_solution(double x, double A);
double max_error(double A, double h, vector<double>& y);
double scheme1(double A, double h, vector<double>& y);
double scheme2(double A, double h, vector<double>& y);
double scheme3(double A, double h, vector<double>& y);
double scheme4(double A, double h, vector<double>& y);
double scheme5(double A, double h, vector<double>& y);
double scheme6(double A, double h, vector<double>& y);
double calculate_order(const vector<double>& errors, const vector<int>& n);
void plot_scheme(int scheme_num, double A, function<double(double, double, vector<double>&)> scheme, const string& data_dir);


#endif 
