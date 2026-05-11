#ifndef MYFUN_H
#define MYFUN_H

#include <vector>
using namespace std;


void filling_mat(vector<vector<double>>& mat, double h, int size);
void find_vect(vector<vector<double>>& vectors, int size, int N);
void find_values(vector<double>& values, int size, int N, double h);
void find_errors(vector<vector<double>>& errors, int size, vector<vector<double>>& mat, vector<vector<double>>& vectors, vector<double>& values);
double max_error(vector<vector<double>>& errors, int size);
double max_error_normalized(vector<vector<double>>& errors, vector<double>& values, int size);
double scal_mult(vector<double>& vect1, vector<double>& vect2, int size);


#endif 
