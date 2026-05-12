#include "algorithms.hpp"

using namespace std;

int maxSumSubarray(const vector<int>& arr, int k) {
    int n = arr.size();
    if (n < k || k <= 0) throw string{"Incorrect k or size of array!"};

    vector<int> pref_sum(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        pref_sum[i + 1] = pref_sum[i] + arr[i];
    }

    int ans = INT_MIN;
    for (int i = 0; i <= n - k; ++i) {
        int cur_sum = pref_sum[i + k] - pref_sum[i];
        ans = max(ans, cur_sum);
    }

    return ans;
}

int subarraySumEqualsK(const vector<int>& nums, int k) {
    unordered_map<int, int> pref_count;
    pref_count[0] = 1;
    
    int count = 0;
    int pref_sum = 0;
    
    for (int num : nums) {
        pref_sum += num;
        
        if (pref_count.find(pref_sum - k) != pref_count.end()) {
            count += pref_count[pref_sum - k];
        }
        
        pref_count[pref_sum]++;
    }
    
    return count;
}

int findMaxLength(vector<int>& nums) {
    unordered_map<int, int> first_occur;
    first_occur[0] = -1;
    
    int pref_sum = 0;
    int max_len = 0;
    
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == 1) {
            pref_sum += 1;
        } else {
            pref_sum += -1;
        }
        
        if (first_occur.find(pref_sum) != first_occur.end()) {
            max_len = max(max_len, i - first_occur[pref_sum]);
        } else {
            first_occur[pref_sum] = i;
        }
    }
    
    return max_len;
}

int findPivotIndex(vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;
    
    if (nums[left] < nums[right]) {
        return 0;
    }
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] > nums[right]) {
            left = mid + 1;
        } else if (nums[mid] < nums[right]) {
            right = mid;
        } else {
            if (nums[mid] > nums[mid + 1]) {
                left = mid + 1;
            } else {
                right = mid;
            }   
        }
    }

    return left;
}

bool isBalancedParentheses(string& s) {
    int n = s.length();
    vector<int> pref_sum(n + 1, 0);
    
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            pref_sum[i + 1] = pref_sum[i] + 1;
        } else if (s[i] == ')') {
            pref_sum[i + 1] = pref_sum[i] - 1;
        }
        
        if (pref_sum[i + 1] < 0) {
            return false;
        }
    }
    
    return pref_sum[n] == 0;
}