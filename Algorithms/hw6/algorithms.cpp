#include "algorithms.hpp"
#include <vector>
#include <unordered_map>
#include <string>


using namespace std;

int largestIncreasingSequence(const vector<int>& arr) {
    if (arr.empty()) return 0;

    int answer = 1;
    int temp = 1;

    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] > arr[i - 1]) {
            temp++;
        } else {
            if (temp > answer) answer = temp;
            temp = 1;
        }
    }

    return temp > answer ? temp : answer;
}

vector<vector<int>> buildPascalTriangle(int n) {
    if (n <= 0) return {};

    vector<vector<int>> triangle(n);
    for (int i = 0; i < n; i++) {
        triangle[i].resize(i + 1, 1);
    }

    for (int i = 2; i < n; i++) {
        for (int j = 1; j < i; j++) {
            triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
        }
    }

    return triangle;
}

int minCoinsNumber(const vector<int>& coins, int amount, unordered_map<int, int>& memo) {
    if (coins.empty() || amount < 0) return -1;

    if (amount == 0) return 0;

    if (memo.find(amount) != memo.end()) return memo[amount];

    memo[amount] = amount + 1;
    for (int coin : coins) {
        int temp = minCoinsNumber(coins, amount - coin, memo);
        if (temp < memo[amount] && temp >= 0) memo[amount] = temp + 1;
    }
    if (memo[amount] == amount + 1) memo[amount] = -1;

    return memo[amount];
}

string maxPalindrome(string str) {
    if (str.empty()) return "";

    int n = str.length();
    vector<vector<bool>> dp(n, vector<bool>(n, true));

    for (int i = 0; i < n - 1; i++) {
        if (str[i] != str[i + 1]) dp[i][i + 1] = false;
    }

    for (int j = 2; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            if (!dp[i + 1][i + j - 1]) {
                dp[i][i + j] = false;
            } else if (str[i] == str[i + j]) {
                dp[i][i + j] = true;
            } else {
                dp[i][i + j] = false;
            }
        }
    }

    for (int j = n - 1; j >= 0; j--) {
        for (int i = 0; i < n - j; i++) {
            if (dp[i][i + j]) return str.substr(i, j + 1);
        }
    }
}
