#include "R2_interpol.hpp"

using namespace std;


double exactFunction(double x, double y) {
    double r = sqrt(x*x + y*y);

    return max(0.0, 1.0 - r);
}

void buildInitialMesh(const double R, vector<Point>& nodes, vector<Triangle>& elements) {
    nodes.clear();
    elements.clear();

    nodes.push_back({0.0, 0.0}); //center

    for (int k = 0; k < 6; ++k) {
        double angle = M_PI * k / 3.0;

        nodes.push_back({R * cos(angle), R * sin(angle)});
    }

    for (int k = 0; k < 6; ++k) {
        int a = 0;
        int b = k + 1;
        int c = (k + 1) % 6 + 1;

        elements.push_back({a, b, c});
    }
}

int getMidpoint(int v1, int v2, vector<Point>& nodes, map<Edge,int>& edgeMap) {
    Edge e(v1, v2);

    auto it = edgeMap.find(e);

    if (it != edgeMap.end())
        return it->second;

    Point p1 = nodes[v1];
    Point p2 = nodes[v2];

    Point mid;

    mid.x = 0.5 * (p1.x + p2.x);
    mid.y = 0.5 * (p1.y + p2.y);

    int index = (int)nodes.size();

    nodes.push_back(mid);

    edgeMap[e] = index;

    return index;
}

void refineMesh(vector<Point>& nodes, vector<Triangle>& elements) {
    map<Edge,int> edgeMap;
    vector<Triangle> newElements;

    for (const Triangle& t : elements) {
        int a = t.v1;
        int b = t.v2;
        int c = t.v3;

        int mab = getMidpoint(a, b, nodes, edgeMap);

        int mbc = getMidpoint(b, c, nodes, edgeMap);

        int mca = getMidpoint(c, a, nodes, edgeMap);

        newElements.push_back({a, mab, mca});

        newElements.push_back({mab, b, mbc});

        newElements.push_back({mca, mbc, c});

        newElements.push_back({mab, mbc, mca});
    }

    elements.swap(newElements);
}

vector<vector<int>> buildNodeTriangles(const vector<Point>& nodes, const vector<Triangle>& elements) {
    vector<vector<int>> nodeTriangles(nodes.size());

    for(size_t t = 0; t < elements.size(); ++t) {
        const Triangle& T = elements[t];

        nodeTriangles[T.v1].push_back(t);
        nodeTriangles[T.v2].push_back(t);
        nodeTriangles[T.v3].push_back(t);
    }

    return nodeTriangles;
}

vector<double> buildInterpolationCoefficients(const vector<Point>& nodes) {
    vector<double> c(nodes.size());

    for (size_t i = 0; i < nodes.size(); ++i) {
        c[i] = exactFunction(nodes[i].x, nodes[i].y);
    }

    return c;
}

Barycentric barycentricCoordinates(const Point& p, const Point& a, const Point& b, const Point& c) {
    double S2 = (b.x - a.x)*(c.y - a.y) - (c.x - a.x)*(b.y - a.y);

    Barycentric bc;

    bc.l1 = ((b.x*c.y - c.x*b.y) + (b.y - c.y)*p.x + (c.x - b.x)*p.y) / S2;

    bc.l2 = ((c.x*a.y - a.x*c.y) + (c.y - a.y)*p.x + (a.x - c.x)*p.y) / S2;

    bc.l3 = 1.0 - bc.l1 - bc.l2;

    return bc;
}

double interpolateInTriangle(const Point& p, const Triangle& T, const vector<Point>& nodes, const vector<double>& coeffs) {
    const Point& a = nodes[T.v1];
    const Point& b = nodes[T.v2];
    const Point& c = nodes[T.v3];

    Barycentric bc = barycentricCoordinates(p, a, b, c);

    return coeffs[T.v1] * bc.l1 + coeffs[T.v2] * bc.l2 + coeffs[T.v3] * bc.l3;
}

Point randomPointInTriangle(const Point& a, const Point& b, const Point& c, mt19937& gen) {
    uniform_real_distribution<double> dist(0.0, 1.0);

    double r1 = dist(gen);
    double r2 = dist(gen);

    double u = sqrt(r1);

    double l1 = 1.0 - u;
    double l2 = u * (1.0 - r2);
    double l3 = u * r2;

    Point p;

    p.x = l1 * a.x + l2 * b.x + l3 * c.x;

    p.y = l1 * a.y + l2 * b.y + l3 * c.y;

    return p;
}

SamplePoint makeSample(const Point& p, const Triangle& T, const LinearPolynomial& poly, const vector<Point>& nodes, const vector<double>& coeffs) {
    SamplePoint s;

    s.x = p.x;
    s.y = p.y;

    s.exact = exactFunction(p.x, p.y);

    s.interp = interpolateInTriangle(p, T, nodes, coeffs);

    s.lsq = evaluate(poly, p.x, p.y);

    s.interpError = abs(s.exact - s.interp);

    s.lsqError = abs(s.exact - s.lsq);

    return s;
}

double evaluateLSQAtNode(int nodeId, const vector<Point>& nodes, const vector<vector<int>>& nodeTriangles, const vector<LinearPolynomial>& polys) {
    const Point& p = nodes[nodeId];

    double sum = 0.0;

    for(int triId : nodeTriangles[nodeId]) {
        sum += evaluate(polys[triId], p.x, p.y);
    }

    return sum / nodeTriangles[nodeId].size();
}

vector<SamplePoint> collectSamples(int m, const vector<Point>& nodes, const vector<Triangle>& elements, 
                                   const vector<double>& coeffs, const vector<LinearPolynomial>& polys, const vector<vector<int>>& nodeTriangles) {
    vector<SamplePoint> samples;

    mt19937 gen(12345);

    //Mesh node
    for (size_t i = 0; i < nodes.size(); ++i) {
        SamplePoint s;

        s.x = nodes[i].x;
        s.y = nodes[i].y;

        s.exact = exactFunction(s.x, s.y);

        s.interp = coeffs[i];

        s.lsq = evaluateLSQAtNode(static_cast<int>(i), nodes, nodeTriangles, polys);

        s.interpError = abs(s.exact - s.interp);

        s.lsqError = abs(s.exact - s.lsq);

        samples.push_back(s);
    }

    //M random samples in each triangle
    for(size_t elemId = 0; elemId < elements.size(); ++elemId) {
        const Triangle& T = elements[elemId];

        const Point& A = nodes[T.v1];

        const Point& B = nodes[T.v2];

        const Point& C = nodes[T.v3];

        const LinearPolynomial& poly = polys[elemId];

        for(int k = 0; k < m; ++k) {
            Point p = randomPointInTriangle(A, B, C, gen);

            SamplePoint s = makeSample(p, T, poly, nodes, coeffs);

            samples.push_back(s);
        }
    }

    return samples;
}

double computeInterpRMS(const vector<SamplePoint>& samples) {
    double sum = 0.0;

    for (const auto& s : samples)
        sum += s.interpError * s.interpError;

    return sqrt(sum / samples.size());
}

double computeLSQRMS(const vector<SamplePoint>& samples) {
    double sum = 0.0;

    for (const auto& s : samples)
        sum += s.lsqError * s.lsqError;

    return sqrt(sum / samples.size());
}

double computeInterpMaxError(const vector<SamplePoint>& samples) {
    double maxErr = 0.0;

    for (const auto& s : samples) {
        maxErr = max(maxErr, abs(s.interpError));
    }

    return maxErr;
}

double computeLSQMaxError(const vector<SamplePoint>& samples) {
    double maxErr = 0.0;

    for (const auto& s : samples) {
        maxErr = max(maxErr, abs(s.lsqError));
    }

    return maxErr;
}

LinearPolynomial solve3x3(double A[3][3], double rhs[3]) {
    double M[3][4];

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j)
            M[i][j] = A[i][j];

        M[i][3] = rhs[i];
    }

    for (int k = 0; k < 3; ++k) {
        int pivot = k;

        for (int i = k + 1; i < 3; ++i) {
            if (abs(M[i][k]) > abs(M[pivot][k])) {
                pivot = i;
            }
        }

        for (int j = k; j < 4; ++j)
            swap(M[k][j], M[pivot][j]);

        double diag = M[k][k];

        for (int j = k; j < 4; ++j)
            M[k][j] /= diag;

        for (int i = 0; i < 3; ++i) {
            if (i == k)
                continue;

            double factor = M[i][k];

            for (int j = k; j < 4; ++j)
                M[i][j] -= factor * M[k][j];
        }
    }

    return {
        M[0][3],
        M[1][3],
        M[2][3]};
}

LinearPolynomial fitLeastSquares(int k, const Triangle& T, const vector<Point>& nodes) {
    mt19937 gen(54321);

    const Point& A = nodes[T.v1];
    const Point& B = nodes[T.v2];
    const Point& C = nodes[T.v3];

    vector<Point> pts;

    pts.push_back(A);
    pts.push_back(B);
    pts.push_back(C);

    for (int i = 0; i < k; ++i) {
        pts.push_back(randomPointInTriangle(A, B, C, gen));
    }

    double Sx = 0.0;
    double Sy = 0.0;
    double Sxx = 0.0;
    double Syy = 0.0;
    double Sxy = 0.0;

    double Sf = 0.0;
    double Sxf = 0.0;
    double Syf = 0.0;

    for (const auto& p : pts) {
        double f = exactFunction(p.x, p.y);

        Sx += p.x;
        Sy += p.y;

        Sxx += p.x * p.x;
        Syy += p.y * p.y;
        Sxy += p.x * p.y;

        Sf += f;
        Sxf += p.x * f;
        Syf += p.y * f;
    }

    double m = (double)pts.size();

    double M[3][3] = {{m,   Sx,  Sy},
                      {Sx, Sxx, Sxy},
                      {Sy, Sxy, Syy}};

    double rhs[3] = {Sf, Sxf, Syf};

    return solve3x3(M, rhs);
}

vector<LinearPolynomial> buildLeastSquaresApproximation(int k, const vector<Point>& nodes, const vector<Triangle>& elements) {
    vector<LinearPolynomial> polys;

    for (const auto& T : elements) {
        polys.push_back(fitLeastSquares(k, T, nodes));
    }

    return polys;
}

double evaluate(const LinearPolynomial& p, double x, double y) {
    return p.a + p.b * x + p.c * y;
}

void writeReport(const std::string& filename, const std::vector<SamplePoint>& samples) {
    ofstream out(filename);

    out << fixed << setprecision(10);

    out << left << setw(15) << "  x"
                << setw(15) << "  y"
                << setw(15) << "  exact"
                << setw(15) << "  interp"
                << setw(15) << "  lsq"
                << setw(15) << "  interp_error"
                << setw(15) << "  lsq_error" << endl;

    for (const auto& s : samples) {
        out << right << setw(15) << s.x
                     << setw(15) << s.y
                     << setw(15) << s.exact
                     << setw(15) << s.interp
                     << setw(15) << s.lsq
                     << setw(15) << s.interpError
                     << setw(15) << s.lsqError << endl;
    }

    cout << "Total points: " << samples.size() << endl;

    cout << "--------------------------------" << endl;
    cout << endl;
    cout << "Interpolation" << endl;

    cout << "RMS error: " 
        << computeInterpRMS(samples) << endl;

    cout << "Max error: "
        << computeInterpMaxError(samples) << endl;

    cout << "--------------------------------" << endl;
    cout << endl;
    cout << "LSQ" << endl;

    cout << "RMS error: " 
        << computeLSQRMS(samples) << endl;

    cout << "Max error: "
        << computeLSQMaxError(samples) << endl;

    cout << "--------------------------------" << endl;
}

void savePlot(FILE* gp, const char* pngName, const char* title, int column) {
    fprintf(gp, "set terminal pngcairo size 1600,1200\n");

    fprintf(gp, "set output '%s'\n", pngName);

    fprintf(gp, "set title '%s'\n", title);

    fprintf(gp, "set hidden3d\n");

    fprintf(gp, "set dgrid3d 50,50\n");

    fprintf(gp, "splot 'out.txt' using 1:2:%d with lines\n", column);

    fprintf(gp, "unset output\n");
}

void buildPlots() {
    FILE* gp = popen("gnuplot", "w");

    if(!gp)
        return;

    savePlot(gp, "exact.png", "Exact function", 3);

    savePlot(gp, "interp.png", "Interpolation", 4);

    savePlot(gp, "lsq.png", "Least squares", 5);

    savePlot(gp, "interp_error.png", "Interpolation error", 6);

    savePlot(gp, "lsq_error.png", "Least squares error", 7);

    pclose(gp);
}