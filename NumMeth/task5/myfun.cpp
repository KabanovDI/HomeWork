#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "myfun.h"

using namespace std;


void filling_mat(vector<vector<double>>& mat, double h, int size)
{
    for (int i = 1; i < size - 1; i++)
    {
        mat[i][i] = 2.0 / (h * h);
        mat[i][i - 1] = -1.0 / (h * h);
        mat[i][i + 1] = -1.0 / (h * h);
    }
    mat[size - 1][size - 1] = 2.0 / (h * h);
    mat[size - 1][size - 2] = -1.0 / (h * h);
}


void find_vect(vector<vector<double>>& vectors, int size, int N)
{
    double C = 1.0;

    for (int m = 0; m < size; m++)
    {
        for (int k = 0; k < size; k++)
        {
            vectors[k][m] = C * sin(M_PI * (k / 2.0 + m * k) / static_cast<double>(N));
        }
    }
}


void find_values(vector<double>& values, int size, int N, double h)
{
    for (int m = 0; m < size; m++)
    {
        values[m] = pow(2.0 * sin(M_PI * (1.0 / 4.0 + m / 2.0) / static_cast<double>(N)) / h, 2);
    }
}


void find_errors(vector<vector<double>>& errors, int size, vector<vector<double>>& mat,
    vector<vector<double>>& vectors, vector<double>& values)
{
    for (int m = 0; m < size; m++)
    {
        for (int i = 0; i < size - 1; i++)
        {
            double Ayi = 0.0;
            for (int k = 0; k < size; k++)
            {
                Ayi += mat[i][k] * vectors[k][m];
            }
            errors[i][m] = Ayi - values[m] * vectors[i][m];
        }
    }
}


double max_error(vector<vector<double>>& errors, int size)
{
    double ans = 0.0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            ans = max(ans, errors[i][j]);
        }
    }
    return ans;
}


double max_error_normalized(vector<vector<double>>& errors, vector<double>& values, int size)
{
    double ans = 0.0;
    for (int m = 0; m < size; m++)
    {
        if (abs(values[m]) < 1e-15) continue;
        for (int k = 0; k < size; k++)
        {
            double normError = abs(errors[k][m] / values[m]);
            ans = max(ans, normError);
        }
    }
    return ans;
}


double scal_mult(vector<double>& vect1, vector<double>& vect2, int size)
{
    double ans = 0.0;
    for (int k = 0; k < size - 1; k++)
    {
        ans += vect1[k] * vect2[k];
    }
    return ans;
}

// Right end of the segment
const double X = 1.0;

// The exact solution
double exact_solution(double x, double A)
{
    return exp(-A * x);
}

// Calculating the maximum error
double max_error(double A, double h, vector<double>& y)
{
    double max_err = 0.0;
    int N = static_cast<int>(X / h);

    for (int k = 0; k <= N; k++)
    {
        double x = k * h;
        double error = abs(exact_solution(x, A) - y[k]);
        max_err = max(max_err, error);
    }

    return max_err;
}

double scheme1(double A, double h, vector<double>& y)
{
    int N = static_cast<int>(X / h);
    y.resize(N + 1);
    y[0] = 1.0;

    for (int k = 0; k < N; k++)
    {
        y[k + 1] = (1.0 - A * h) * y[k];
    }

    return max_error(A, h, y);
}

double scheme2(double A, double h, vector<double>& y)
{
    int N = static_cast<int>(X / h);
    y.resize(N + 1);
    y[0] = 1.0;

    for (int k = 0; k < N; k++)
    {
        y[k + 1] = y[k] / (1.0 + A * h);
    }

    return max_error(A, h, y);
}

double scheme3(double A, double h, vector<double>& y)
{
    int N = static_cast<int>(X / h);
    y.resize(N + 1);
    y[0] = 1.0;

    double factor = (1.0 - A * h / 2.0) / (1.0 + A * h / 2.0);
    for (int k = 0; k < N; k++)
    {
        y[k + 1] = factor * y[k];
    }

    return max_error(A, h, y);
}

double scheme4(double A, double h, vector<double>& y)
{
    int N = static_cast<int>(X / h);
    y.resize(N + 1);
    y[0] = 1.0;
    y[1] = 1.0 - A * h;

    for (int k = 1; k < N; k++)
    {
        y[k + 1] = y[k - 1] - 2.0 * h * A * y[k];
    }

    return max_error(A, h, y);
}

double scheme5(double A, double h, vector<double>& y)
{
    int N = static_cast<int>(X / h);
    y.resize(N + 1);
    y[0] = 1.0;
    y[1] = 1.0 - A * h;

    for (int k = 2; k <= N; k++)
    {
        y[k] = (2.0 * y[k - 1] - 0.5 * y[k - 2]) / (1.5 + A * h);
    }

    return max_error(A, h, y);
}

double scheme6(double A, double h, vector<double>& y)
{
    int N = static_cast<int>(X / h);
    y.resize(N + 1);
    y[0] = 1.0;
    y[1] = 1.0 - A * h;

    for (int k = 0; k <= N - 2; k++)
    {
        y[k + 2] = 4.0 * y[k + 1] + (2.0 * A * h - 3.0) * y[k];
    }

    return max_error(A, h, y);
}

// Calculating the order of convergence
double calculate_order(const vector<double>& errors, const vector<int>& n)
{
    if (errors.size() < 2) return 0.0;

    double total_order = 0.0;
    int count = 0;
    int k = 0;

    for (size_t i = 0; i < errors.size() - 1; i++)
    {
        if (errors[i + 1] > 1e-15 && errors[i] > 1e-15)
        {
            k = n[i + 1] - n[i];
            double order = log(errors[i] / errors[i + 1]) / (k * log(10.0));
            total_order += order;
        }
        count++;
    }

    return total_order / count;
}

// Function for plotting graphs
void plot_scheme(int scheme_num, double A, function<double(double, double, vector<double>&)> scheme, const string& data_dir)
{
    vector<double> log_inv_h;
    vector<double> log_error;
    vector<double> y;

    string filename = data_dir + "/scheme_" + to_string(scheme_num) + "_A_" + to_string((int)A) + ".txt";
    ofstream file(filename);

    for (int n = 1; n <= 7; n++)
    {
        double h = pow(10.0, -n);
        scheme(A, h, y);
        double error = abs(exact_solution(X, A) - y.back());
        if (((n==4)or(n==5)or(n==6)or(n==7))and(A-1.0 < 1e-100)and(scheme_num==4)) cout << error << "\n";

        if (error > 1e-15) 
        {
            double ln_inv_h = log(1.0 / h);  
            double ln_inv_error = log(1.0 / error);  

            log_inv_h.push_back(ln_inv_h);
            log_error.push_back(ln_inv_error);

            file << ln_inv_h << " " << ln_inv_error << "\n";
        }
    }

    file.close();
}
