#include "spline3.hpp"

using namespace std;


int main() {
    int N;
    vector<double> x, f, w;
    double df0, dfN;

    int rep = parsingFile("in.txt", N, x, f, w, df0, dfN);
    if (rep) return -1;
    
    vector<double> h(N + 1);
    for (int i = 1; i <= N; i++) {
        h[i] = x[i] - x[i - 1];
    }

    vector<double> M;
    M = solveProgonka(N, h, w, f, df0, dfN);

    // Write to out.txt
    ofstream outFile("out.txt");
    outFile << fixed << setprecision(5);
    
    // Write header
    outFile << left
            << setw(15) <<  "      #x" << " "
            << setw(15) << "   #S3(x)" << endl;
    
    // Evaluate and write results
    for (int i = 1; i <= N; i++) {
        // Generate extra points
        double x1 = x[i - 1] + h[i] / 3.0;
        double x2 = x[i - 1] + 2.0 * h[i] / 3.0;

        // Calculate S3
        auto S3 = [=](double xx) -> double {
            return (M[i - 1] / w[i]) * (pow(x[i] - xx, 3) / (6.0 * h[i])) +
                   (M[i] / w[i]) * (pow(xx - x[i - 1], 3) / (6.0 * h[i])) +
                   (f[i - 1] - M[i - 1] * h[i] * h[i] / (6.0 * w[i])) * (x[i] - xx) / h[i] +
                   (f[i] - M[i] * h[i] * h[i] / (6.0 * w[i])) * (xx - x[i - 1]) / h[i];};
    
        // Calculate output
        for (double xx : {x[i - 1], x1, x2, x[i]}) {
            outFile << right 
                    << setw(15) << xx << " "
                    << setw(15) << S3(xx) << endl;
        }
    }
    
    outFile.close();
    
    cout << "Files generated successfully!" << endl;
    cout << "Check out.txt for results." << endl;
    cout << "Plotting results..." << endl;
    plotSimple();
    
    return 0;
}
