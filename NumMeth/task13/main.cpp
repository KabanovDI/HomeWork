#include "R2_interpol.hpp"

using namespace std;


int main() {
    double R = 1.0;
    int N = 2;
    int m = 10; //Number of samples
    int k = 10; //Number of nodes in MNK

    vector<Point> nodes;
    vector<Triangle> elements;

    buildInitialMesh(R, nodes, elements);

    for (int i = 0; i < N; ++i)
        refineMesh(nodes, elements);

    vector<vector<int>> nodeTriangles = buildNodeTriangles(nodes, elements);

    vector<double> coeffs = buildInterpolationCoefficients(nodes);

    vector<LinearPolynomial> polys = buildLeastSquaresApproximation(k, nodes, elements);

    vector<SamplePoint> samples = collectSamples(m, nodes, elements, coeffs, polys, nodeTriangles);

    writeReport("out.txt", samples);

    buildPlots();

    return 0;
}