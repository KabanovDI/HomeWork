#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <random>
#include <fstream>
#include <iomanip>
#include <iostream>


struct Point {
    double x;
    double y;
};

struct Triangle {
    int v1;
    int v2;
    int v3;
};

struct Edge {
    int a;
    int b;

    Edge(int v1, int v2) {
        a = std::min(v1, v2);
        b = std::max(v1, v2);
    }

    bool operator<(const Edge& other) const {
        if (a != other.a)
            return a < other.a;

        return b < other.b;
    }
};

struct Barycentric {
    double l1;
    double l2;
    double l3;
};

struct SamplePoint {
    double x;
    double y;

    double exact;
    double interp;
    double lsq;

    double interpError;
    double lsqError;
};

struct LinearPolynomial {
    double a;
    double b;
    double c;
};

double exactFunction(double x, double y);

void buildInitialMesh(const double R, std::vector<Point>& nodes, std::vector<Triangle>& elements);

int getMidpoint(int v1, int v2, std::vector<Point>& nodes, std::map<Edge,int>& edgeMap);

void refineMesh(std::vector<Point>& nodes, std::vector<Triangle>& elements);

std::vector<std::vector<int>> buildNodeTriangles(const std::vector<Point>& nodes, const std::vector<Triangle>& elements);

std::vector<double> buildInterpolationCoefficients(const std::vector<Point>& nodes);

Barycentric barycentricCoordinates(const Point& p, const Point& a, const Point& b, const Point& c);

double interpolateInTriangle(const Point& p, const Triangle& T, const std::vector<Point>& nodes, const std::vector<double>& coeffs);

Point randomPointInTriangle(const Point& a, const Point& b, const Point& c, std::mt19937& gen);

SamplePoint makeSample(const Point& p, const Triangle& T, const LinearPolynomial& poly, const std::vector<Point>& nodes, 
                       const std::vector<double>& coeffs);

double evaluateLSQAtNode(int nodeId, const std::vector<Point>& nodes, const std::vector<std::vector<int>>& nodeTriangles, 
                         const std::vector<LinearPolynomial>& polys);

std::vector<SamplePoint> collectSamples(int m, const std::vector<Point>& nodes, const std::vector<Triangle>& elements, const std::vector<double>& coeffs, 
                                        const std::vector<LinearPolynomial>& polys, const std::vector<std::vector<int>>& nodeTriangles);

double computeInterpRMS(const std::vector<SamplePoint>& samples);

double computeLSQRMS(const std::vector<SamplePoint>& samples);

double computeInterpMaxError(const std::vector<SamplePoint>& samples);

double computeLSQMaxError(const std::vector<SamplePoint>& samples);

LinearPolynomial solve3x3(double A[3][3], double rhs[3]);

LinearPolynomial fitLeastSquares(int k, const Triangle& T, const std::vector<Point>& nodes);

std::vector<LinearPolynomial> buildLeastSquaresApproximation(int k, const std::vector<Point>& nodes, const std::vector<Triangle>& elements);

double evaluate(const LinearPolynomial& p, double x, double y);

void writeReport(const std::string& filename, const std::vector<SamplePoint>& samples);

void savePlot(FILE* gp, const char* pngName, const char* title, int column);

void buildPlots();