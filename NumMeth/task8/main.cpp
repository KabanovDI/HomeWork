#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

// Exact solution for error calculation
double exact_u(double t, double x) {
    return exp(-t) * sin(M_PI * x / 2.0);
}

// Source term f(x, t) derived for the exact solution above
double f_source(double t, double x) {
    return (M_PI * M_PI / 4.0) * exact_u(x, t);
}

// Solver function that returns the maximum absolute error
double solve(int N, int M, vector<vector<double>>& y) {
    double L = 1.0, T_max = 1.0, p = 1.0;
    double h = L / N;
    double tau = T_max / M;
    double rou = tau / (h * h);

    vector<double> y_new(N + 1);
    vector<double> alpha(N + 1), beta(N + 1);

    for (int m = 0; m <= N; ++m){
         y[0][m] = exact_u(0, m * h);
    }

    double max_err = 0;

    // Time loop
    for (int n = 0; n < M; ++n) {
        double t_next = (n + 1) * tau;
        double rou = tau / (h * h);

        // 1. Forward sweep (Left boundary: y0 = 0)
        alpha[1] = 0;
        beta[1] = 0;

        for (int m = 1; m < N; ++m) {
            double A = rou;
            double B = rou;
            double C = 1.0 + 2.0 * rou + tau * p;
            double F = y[n][m] + tau * f_source(t_next, m * h);

            alpha[m + 1] = B / (C - A * alpha[m]);
            beta[m + 1] = (F + A * beta[m]) / (C - A * alpha[m]);
        }

        // 2. Right boundary: u_x(1, t) = 0 
        double AN = 2.0 * rou;
        double CN = 1.0 + 2.0 * rou + rou * p;
        double FN = y[n][N] + tau * f_source(t_next, L);
        y_new[N] = (FN + AN * beta[N]) / (CN - AN * alpha[N]);

        // 3. Backward sweep
        for (int m = N - 1; m >= 0; --m) {
            y_new[m] = alpha[m + 1] * y_new[m + 1] + beta[m + 1];
        }

        y[n] = y_new;

        // Calculate max error
        for (int m = 0; m <= N; ++m) {
            double err = abs(y[n][m] - exact_u(t_next, m * h));
            if (err > max_err) max_err = err;
        }
    }
    return max_err;
}

int main() {
    int N = 50;          // Space steps
    int M = 500;         // Time steps
    double L = 1.0;      // Length
    double T = 1.0;      // Total time
    double h = L / N;
    double tau = T / M;
    double p = 1.0;      // Given coefficient
    vector<vector<double>> y(M + 1, vector<double>(N + 1, 0.0));

    // Save data
    ofstream outFile("results.txt");
    double max_error = solve(N, M, y);
    for (int n = 0; n < M; ++n) {
        double t_next = (n + 1) * tau;
        for (int m = 0; m <= N; ++m) {
            outFile << t_next << " " << m * h << " " << y[n][m] << " " << exact_u(t_next, m * h) << "\n";
        }
    }
    cout << "Calculation finished." << endl;
    cout << "Max absolute error: " << max_error << endl;
    outFile.close();

    // 1. Test Space Convergence O(h^2)
    ofstream file_h("conv_h.txt");
    int M_fixed = 500; 
    cout << "Testing O(h^2)..." << endl;
    for (int N : {10, 20, 40, 80, 160}) {
        vector<vector<double>> y(M_fixed + 1, vector<double>(N + 1, 0.0));
        double err = solve(N, M_fixed, y);
        file_h << 1.0/N << " " << err << endl;
    }
    file_h.close();

    // 2. Test Time Convergence O(tau)
    // Keep h very small so space error is negligible
    ofstream file_tau("conv_tau.txt");
    int N_fixed = 50;
    cout << "Testing O(tau)..." << endl;
    for (int M : {50, 100, 200, 400, 800}) {
        vector<vector<double>> y(M + 1, vector<double>(N_fixed + 1, 0.0));
        double err = solve(N_fixed, M, y);
        file_tau << 1.0/M << " " << err << endl;
    }
    file_tau.close();
    return 0;
}