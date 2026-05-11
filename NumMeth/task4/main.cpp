#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>
#include "myfun.h"
using namespace std;


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

    for (int m = 0; m < size; m++)
    {
        for(int i = 0; i < size; i++)
        {
            cout << mat[m][i] << " | ";
        }
        cout << "\n";
    }

    for (int m = 0; m < size; m++)
    {
        for (int i = 0; i < N; i++)
        {
            double Ayi = 0;
            for (int j = 0; j < size; j++)
            {
                Ayi += mat[i][j] * vectors[j][m];
            }
            cout << Ayi << " | ";
        }
        cout << " " << values[m] << "  | " << "\n";
        for (int i = 0; i < N; i++)
        {
            cout << values[m] * vectors[i][m] << " | ";
        }
        cout << "\n";
    }

    double maxError = max_error(errors, size);
    printf("Loo = %10.10e\n", maxError);

    double maxErrorNorm = max_error_normalized(errors, values, size);
    printf("Loo (normalized) = %10.10e\n", maxErrorNorm);


    double maxScalMult = 0.0;
    for (int n = 0; n < size; n++)
    {
        vector<double> vect1;
        for (vector<double>& row1 : vectors)
        {
            vect1.push_back(row1[n]);
        }
        for (int m = 0; m < size; m++)
        {
            if (m == n) break;
            vector<double> vect2;
            for (vector<double>& row2 : vectors)
            {
                vect2.push_back(row2[m]);
            }
            maxScalMult = max(maxScalMult, scal_mult(vect1, vect2, size));
        }
    }
    printf("Maximum scalar multiplication = %10.10e\n", maxScalMult);

    return 0;
}
