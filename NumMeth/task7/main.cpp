#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

const double PI = 3.14159265358979323846;

// Test function p(x)
double p_func(double x) {
    return x * x + 1.0; 
}

// Test right part f(x)
double f_func(double x) {
    return (PI * PI / 4.0 + p_func(x)) * sin(PI * x / 2.0);
}

// Exact solution
double u_exact(double x) {
    return sin(PI * x / 2.0);
}

// 1. Sweep method (for variable p(x))
void solve_progonka(int N, double h, vector<double>& y) {
    vector<double> a(N + 1), b(N + 1), alpha(N + 1), beta(N + 1);

    // Left condition: y[0] = 0
    alpha[1] = 0;
    beta[1] = 0;

    // Straight move
    for (int k = 1; k < N; ++k) {
        double x_k = k * h;
        double A = 1.0/pow(h, 2);
        double B = 1.0/pow(h, 2);
        double C = 2.0/pow(h, 2) + p_func(x_k);
        double F = f_func(x_k);

        alpha[k + 1] = B / (C - A * alpha[k]);
        beta[k + 1] = (F + A * beta[k]) / (C - A * alpha[k]);
    }

    // Right condition: (1 + h^2/2 * p_N)y_N - y_{N-1} = h^2/2 * f_N
    y[N] = (f_func(1.0) + 2.0 * beta[N] / pow(h, 2)) / (2.0 / pow(h, 2) + p_func(1.0) - 2.0 * alpha[N] / pow(h, 2));

    // Reverse move
    for (int k = N - 1; k >= 0; --k) {
        y[k] = alpha[k + 1] * y[k + 1] + beta[k + 1];
    }
}

// 2. Fourier`s method (for p = const)
void solve_fourier(int N, double h, double p_const, vector<double>& y) {
    vector<double> c(N + 1, 0.0);
    
    auto get_eigenvalue = [&](int m) {
        double alpha_m = PI * (m - 0.5) / (2.0 * N);
        return (4.0 / (h * h)) * pow(sin(alpha_m), 2);
    };

    auto get_eigenvector = [&](int m, int k) {
        double alpha_m = PI * (m - 0.5) / N;
        return sin(alpha_m * k);
    };

    // For every eigen vector[m]
    for (int m = 1; m <= N; ++m) {
        double numerator = 0;
        double denominator = 0;

        // Scalar multiplication (f, v_m)
        for (int k = 1; k < N; ++k) {
            numerator += f_func(k * h) * get_eigenvector(m, k) * h;
            denominator += pow(get_eigenvector(m, k), 2) * h;
        }
        // Add half knot on the right side (x=1)
        numerator += 0.5 * h * f_func(1.0) * get_eigenvector(m, N);
        denominator += 0.5 * h * pow(get_eigenvector(m, N), 2);

        double lambda_m = get_eigenvalue(m);
        c[m] = numerator / (denominator * (lambda_m + p_const));
    }

    // Solution assembly
    for (int k = 0; k <= N; ++k) {
        y[k] = 0;
        for (int m = 1; m <= N; ++m) {
            y[k] += c[m] * get_eigenvector(m, k);
        }
    }
}

int main() {
    int N = 20; 
    double h = 1.0 / N;
    vector<double> y_prog(N + 1), y_four(N + 1);

    solve_progonka(N, h, y_prog);
    solve_fourier(N, h, 2.0, y_four); // p = 2.0

    // Print results & find max errors
    double max_error_prog = 0.0;
    double max_error_four = 0.0;

    cout << setw(10) << "x" << setw(15) << "Exact" << setw(15) << "Progonka" << setw(15) << "Fourier" << endl;
    cout << string(55, '-') << endl;

    for (int k = 0; k <= N; ++k) {
        double x = k * h;
        double exact = u_exact(x);
        
        double err_p = fabs(y_prog[k] - exact);
        double err_f = fabs(y_four[k] - exact);

        if (err_p > max_error_prog) max_error_prog = err_p;
        if (err_f > max_error_four) max_error_four = err_f;

        if (k % 2 == 0) {
            cout << fixed << setprecision(5) << setw(10) << x 
                 << setw(15) << exact 
                 << setw(15) << y_prog[k] 
                 << setw(15) << y_four[k] << endl;
        }
    }

    cout << string(55, '-') << endl;
    cout << scientific << setprecision(4); 
    cout << "Max Error (Progonka): " << max_error_prog << endl;
    cout << "Max Error (Fourier):  " << max_error_four << endl;

    // Write data
    ofstream out("results.txt");
    out << "x,exact,numerical" << endl;
    for (int k = 0; k <= N; ++k) {
        out << k * h << "," << u_exact(k * h) << "," << y_prog[k] << endl;
    }
    out.close();

    ofstream conv("convergence.txt");
    conv << "h,error" << endl;
    for (int n_val : {10, 20, 40, 80, 160, 320}) {
        double hn = 1.0 / n_val;
        vector<double> yn(n_val + 1);
        solve_progonka(n_val, hn, yn);
        double max_err = 0;
        for (int k = 0; k <= n_val; ++k) max_err = max(max_err, abs(yn[k] - u_exact(k * hn)));
        conv << hn << "," << max_err << endl;
    }
    conv.close();

    return 0;
}