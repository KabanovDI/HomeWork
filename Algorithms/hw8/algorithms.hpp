#pragma once

#include <vector>
#include <algorithm>
#include <climits>
#include <string>
#include <unordered_map>

int maxSumSubarray(const std::vector<int>& arr, int k);
int subarraySumEqualsK(const std::vector<int>& nums, int k);
int findMaxLength(std::vector<int>& nums);
int findPivotIndex(std::vector<int>& nums);
bool isBalancedParentheses(std::string& s);