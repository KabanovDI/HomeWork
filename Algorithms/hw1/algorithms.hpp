#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <vector>
#include <string>

void swap(int& a, int& b);
void reverseArray(std::vector<int>& arr, int start, int end);
void rotateArray(std::vector<int>& arr, int k);
std::vector<int> mergeArrays(const std::vector<int>& arr1, const std::vector<int>& arr2);
void mergeArraysInPlays(std::vector<int>& arr1, int n, std::vector<int>& arr2, int m);
void sort0_1(std::vector<int>& arr);
void sort0_1_2(std::vector<int>& arr);
void evenFirst(std::vector<int>& arr);
void zeroLast(std::vector<int>& arr);

#endif