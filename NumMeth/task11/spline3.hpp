#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>


int parsingFile(const std::string& fileName, int& N, std::vector<double>& x, std::vector<double>& f, 
                std::vector<double>& w, double& df0, double& dfN);

std::vector<double> solveProgonka(int N, const std::vector<double>& h, const std::vector<double>& w,
                             const std::vector<double>& f, double df0, double dfN);

void plotSimple();