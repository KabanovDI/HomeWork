#include <vector>
#include <iostream>
#include <string>
#include "algorithms.hpp"

using namespace std;

void swap(int& a, int& b) {
    int temp;
    temp = a;
    a = b;
    b = temp;
}

void reverseArray(vector<int>& arr, int start, int end) {
    while (start < end) {
        swap(arr[start], arr[end]);
        start++;
        end--;
    }
}

void rotateArray(vector<int>& arr, int k) {
    int n = arr.size();
    if (n == 0 || k <= 0) {
        return;
    }
    k = k % n;
    reverseArray(arr, 0, n - 1 - k);
    reverseArray(arr, n - k, n - 1);
    reverseArray(arr, 0, n - 1);
}

vector<int> mergeArrays(const vector<int>& arr1, const vector<int>& arr2) {
    int a = arr1.size();
    int b = arr2.size();
    vector<int> result;
    result.reserve(a + b);
    int i = 0;
    int j = 0;
    while (i < a and j < b) {
        if (arr1[i] < arr2[j]) {
            result.push_back(arr1[i]);
            i++;
        } else {
            result.push_back(arr2[j]);
            j++;
        }
    }
    while (i < a) {
        result.push_back(arr1[i]);
        i++;
    }
    while (j < b) {
        result.push_back(arr2[j]);
        j++;
    }
    return result;
}

void mergeArraysInPlays(vector<int>& arr1, int n, vector<int>& arr2, int m) {
    int i = arr1.size() - 1;
    n--;
    m--;
    while (m >= 0) {
        if (n < 0) {
            arr1[i] = arr2[m];
            m--; 
            i--;
            continue;
        }
        if (arr1[n] > arr2[m]){
            arr1[i] = arr1[n];
            n--;
            i--;
        } else {
            arr1[i] = arr2[m];
            m--; 
            i--;
        }
    }
}

void sort0_1(vector<int>& arr) {
    int i = 0;
    int j = arr.size() - 1;
    while (i < j) {
        if (arr[j]) {
            j--;
        } else if (arr[i]) {
            arr[i] = 0;
            arr[j] = 1;
            i++;
            j--;
        } else {
            i++;
        }
    }
}

void sort0_1_2(vector<int>& arr) {
    int i = 0;
    int j = 0;
    int k = arr.size() - 1;
    while (j <= k) {
        switch (arr[j]) {
            case 0:
                swap(arr[i], arr[j]);
                i++;
                j++;
                break;
            case 1:
                j++;
                break;
            case 2:
                swap(arr[j], arr[k]);
                k--;
                break;
        }
    }
}

void evenFirst(vector<int>& arr) {
    int i = 0;
    int j = 0;
    while (i < arr.size() && arr[i] % 2 == 0) {
        i++;
    }
    j = i;
    while (j < arr.size()) {
        if (arr[j] % 2 == 0) {
            swap(arr[i], arr[j]);
            i++;
        }
        j++;
    }
}

void zeroLast(vector<int>& arr) {
    int zero_count = 0;
    int i = 0;
    while (i < arr.size()) {
        if (arr[i]) {
            arr[i - zero_count] = arr[i];
        } else {
            zero_count++;
        }
        i++;
    }
    for (int j = 0; j < zero_count; j++) {
        arr[arr.size() - 1 - j] = 0;
    }
}

