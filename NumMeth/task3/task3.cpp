#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;


void filling_mat(vector<vector<double>>& mat, double h, int size);
void find_vect(vector<vector<double>>& vectors, int size, int N);
void find_values(vector<double>& values, int size, int N, double h);
void find_errors(vector<vector<double>>& errors, int size, vector<vector<double>>& mat,
    vector<vector<double>>& vectors, vector<double>& values);
double max_error(vector<vector<double>>& errors, int size);
double max_error_normalized(vector<vector<double>>& errors, vector<double>& values, int size);


int main()
{
    int N;
    cin >> N;
    int size = N + 1;
    double h = 1.0 / static_cast<double>(N);
    vector<vector<double>> mat(size, vector<double>(size));
    vector<vector<double>> vectors(size, vector<double>(size));
    vector<double> values(size);
    vector<vector<double>> errors(size, vector<double>(size));


    filling_mat(mat, h, size);
    find_vect(vectors, size, N);
    find_values(values, size, N, h);
    find_errors(errors, size, mat, vectors, values);

    double maxError = max_error(errors, size);
    printf("Loo = %10.10e\n", maxError);

    double maxErrorNorm = max_error_normalized(errors, values, size);
    printf("Loo (normalized) = %10.10e\n", maxErrorNorm);

    return 0;
}


void filling_mat(vector<vector<double>>& mat, double h, int size)
{
    for (int i = 1; i < size - 1; i++)
    {
        mat[i][i] = 2.0 / (h * h);
        mat[i][i - 1] = -1.0 / (h * h);
        mat[i][i + 1] = -1.0 / (h * h);
    }
}


void find_vect(vector<vector<double>>& vectors, int size, int N)
{
    double C = 1.0;

    for (int m = 0; m < size; m++)
    {
        for (int k = 0; k < size; k++)
        {
            vectors[k][m] = C * sin((M_PI * k * m) / static_cast<double>(N));
        }
    }
}


void find_values(vector<double>& values, int size, int N, double h)
{
    for (int m = 0; m < size; m++)
    {
        values[m] = pow(2.0 * sin(M_PI * m / 2 * static_cast<double>(N)) / h, 2);
    }
}


void find_errors(vector<vector<double>>& errors, int size, vector<vector<double>>& mat,
    vector<vector<double>>& vectors, vector<double>& values)
{
    for (int m = 0; m < size; m++)
    {
        for (int i = 0; i < size; i++)
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
        for (int j = 0; j < size; j++)
        {
            double normError = abs(errors[j][m] / values[m]);
            ans = max(ans, normError);
        }
    }
    return ans;
}
