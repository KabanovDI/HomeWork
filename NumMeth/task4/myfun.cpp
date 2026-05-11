#include <cmath>
#include <vector>
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

