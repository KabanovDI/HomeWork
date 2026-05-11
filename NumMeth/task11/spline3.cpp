#include "spline3.hpp"

using namespace std;


int parsingFile(const string& fileName, int& N, vector<double>& x, vector<double>& f, 
                vector<double>& w, double& df0, double& dfN) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Cannot open file" << endl;
        return -1;
    }

    string line;

    // Read N from comment line
    getline(file, line);
    sscanf(line.c_str(), "#N = %d", &N);

    // Skip header line
    getline(file, line);

    // Read data points
    for (int i = 0; i <= N; i++) {
        getline(file, line);
        istringstream iss(line);
        double xi, fi, wi;
        iss >> xi >> fi >> wi;
        x.push_back(xi);
        f.push_back(fi);
        w.push_back(wi);
    }

    // Read derivative values
    getline(file, line);
    sscanf(line.c_str(), "#f'_0 = %lf", &df0);
    getline(file, line);
    sscanf(line.c_str(), "#f'_N = %lf", &dfN);

    file.close();

    return 0;
}

vector<double> solveProgonka(int N, const vector<double>& h, const vector<double>& w,
                             const vector<double>& f, double df0, double dfN) {
    vector<double> a(N + 1), b(N + 1), c(N + 1), y(N + 1), alpha(N + 1), beta(N + 1), M(N + 1);

    c[0] = h[1] / (3.0 * w[1]);
    c[N] = h[N] / (3.0 * w[N]);
    for (int i = 1; i < N; i++) {
        c[i] = (h[i] / w[i] + h[i + 1] / w[i + 1]) / 3.0;
    }

    for (int i = 1; i <= N; i++) {
        a[i] = -(h[i]) / (6.0 * w[i]);
    }

    for (int i = 0; i < N; i++) {
        b[i] = -(h[i + 1]) / (6.0 * w[i + 1]);
    }

    y[0] = (f[1] - f[0]) / h[1] - df0;
    y[N] = dfN - (f[N] - f[N - 1]) / h[N];
    for (int i = 1; i < N; i++) {
        y[i] = (f[i + 1] - f[i]) / h[i + 1] - (f[i] - f[i - 1]) / h[i];
    }

    // Left condition: y[0] = 0
    alpha[1] = b[0] / c[0];
    beta[1] = y[0] / c[0];

    // Straight move
    for (int i = 1; i < N; i++) {
        alpha[i + 1] = b[i] / (c[i] - a[i] * alpha[i]);
        beta[i + 1] = (y[i] + a[i] * beta[i]) / (c[i] - a[i] * alpha[i]);
    }

    M[N] = (y[N] + a[N] * beta[N]) / (c[N] - a[N] * alpha[N]);

    // Reverse move
    for (int i = N - 1; i >= 0; i--) {
        M[i] = alpha[i + 1] * M[i + 1] + beta[i + 1];
    }

    return M;
}

void plotSimple() {
    FILE* gnuplot = popen("gnuplot -persist", "w");
    
    fprintf(gnuplot, "set title 'Weighted cubic spline'\n");
    
    // First plot - interpolation
    fprintf(gnuplot, "set xlabel 'x'\n");
    fprintf(gnuplot, "set ylabel 'S3(x)'\n");
    fprintf(gnuplot, "set grid\n");
    fprintf(gnuplot, "plot 'in.txt' using 1:2 with points pt 7 ps 2 lc rgb 'red' title 'Points', \\\n");
    fprintf(gnuplot, "     'out.txt' using 1:2 with lines lw 2 lc rgb 'blue' title 'S3(x)', \n");

    pclose(gnuplot);
}
