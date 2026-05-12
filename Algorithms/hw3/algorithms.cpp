#include "algorithms.hpp"
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

int findSquareRoot(int n) {
    int left = 0;
    int right = n / 2 + 1;
    while (left != right) {
        int mid = (left + right) / 2 + 1;
        if (mid * mid > n) {
            right = (right == mid) ? (right - 1) : mid;
        } else {
            left = (left == mid) ? (left + 1) : mid;
        }
    }
    return left;
}

bool canCopy(int N, int x, int y, int t) {
    int copies1 = t / x;
    int copies2 = t / y;
    return (copies1 + copies2) >= N;
}

int timeCopying(int N, int x, int y) {   
    int left = 0;
    int right = min(x, y) * (N - 1);
    
    while (left <= right) {
        int mid = (left + right) / 2;
        
        if (canCopy(N - 1, x, y, mid)) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return left + min(x, y);
}

int countFedAnimals(vector<int>& animals, vector<int>& portions) {
    sort(animals.begin(), animals.end());
    sort(portions.begin(), portions.end());
    
    int i = 0, j = 0;
    
    while (i < animals.size() && j < portions.size()) {
        if (portions[j] >= animals[i]) {
            i++;
            j++;
        } else {
            j++;
        }
    }
    
    return i;
}

char findDiff(string a, string b) {
    char result = 0;
    
    for (char c : a) {
        result ^= c;
    }
    for (char c : b) {
        result ^= c;
    }
    
    return result;
}

vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> seen; 
    
    for (int i = 0; i < nums.size(); i++) {
        int diff = target - nums[i];
        
        if (seen.find(diff) != seen.end()) {
            return {seen[diff], i};
        }
        
        seen[nums[i]] = i;
    }
    
    return {}; 
}