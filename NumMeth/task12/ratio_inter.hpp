#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <set>
#include <limits>


double func(const double x, const int mode);

double fDer(const double x, const int mode);

std::vector<double> points(const double a, const double b, const int n, const int mode);

void fill_out_infile(const std::string& fileName, const double a, const double b, const int n, const int mode_x, const int mode_f);

int parsingFile(const std::string& fileName, std::vector<double>& x, std::vector<double>& f, 
                std::vector<double>& d);

std::vector<double> solveProgonka(int N, const std::vector<double>& h, const std::vector<double>& w,
                             const std::vector<double>& f, double df0, double dfN);

void plotSimple();