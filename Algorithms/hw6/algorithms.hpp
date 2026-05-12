#pragma once

#include <vector>
#include <unordered_map>
#include <string>


int largestIncreasingSequence(const std::vector<int>& arr);

std::vector<std::vector<int>> buildPascalTriangle(int n);

int minCoinsNumber(const std::vector<int>& coins, int amount, std::unordered_map<int, int>& memo);

std::string maxPalindrome(std::string str);