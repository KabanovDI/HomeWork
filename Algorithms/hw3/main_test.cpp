#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "algorithms.hpp"
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

using namespace std;

TEST_CASE("Search integer square root of n", "[task1]") {
    SECTION("n = 0") {
        REQUIRE(findSquareRoot(0) == 0);
    }
    SECTION("n = 1") {
        REQUIRE(findSquareRoot(1) == 1);
    }
    SECTION("n = 2") {
        REQUIRE(findSquareRoot(2) == 1);
    }
    SECTION("n = 3") {
        REQUIRE(findSquareRoot(3) == 1);
    }
    SECTION("n = 4") {
        REQUIRE(findSquareRoot(4) == 2);
    }
    SECTION("n = 5") {
        REQUIRE(findSquareRoot(5) == 2);
    }
    SECTION("n = 111") {
        REQUIRE(findSquareRoot(111) == 10);
    }
}

TEST_CASE("Minimum copy time", "[task2]") {
    vector<tuple<int, int, int, int>> test_cases = {
        {1, 1, 2, 1},
        {2, 1, 2, 2},
        {3, 2, 3, 5},
        {4, 1, 1, 3},
        {5, 2, 3, 8},
        {10, 1, 100, 10},
        {1, 100, 200, 100},
        {100, 2, 2, 102}
    };
    
    for (const auto& [N, x, y, expected] : test_cases) {
        DYNAMIC_SECTION("N = " << N << ", x = " << x << ", y = " << y) {
            int result = timeCopying(N, x, y);
            REQUIRE(result == expected);

            REQUIRE(canCopy(N - 1, x, y, result - min(x, y)) == true);
            
            if (result -  min(x, y) > 0)
            REQUIRE(canCopy(N - 1, x, y, result -  min(x, y) - 1) == false);
        }
    }
}

TEST_CASE("Count of fed animals", "[task3]") {
    SECTION("Everyone can be fed") {
        vector<int> animals = {3, 2, 1};
        vector<int> portions = {1, 2, 3};
        REQUIRE(countFedAnimals(animals, portions) == 3);
    }

    SECTION("No one can be fed") {
        vector<int> animals = {5, 6, 7};
        vector<int> portions = {1, 2, 3};
        REQUIRE(countFedAnimals(animals, portions) == 0);
    }

    SECTION("Empty arrays") {
        vector<int> animals = {};
        vector<int> portions = {1, 2, 3};
        REQUIRE(countFedAnimals(animals, portions) == 0);
        
        vector<int> animals2 = {1, 2, 3};
        vector<int> portions2 = {};
        REQUIRE(countFedAnimals(animals2, portions2) == 0);
        
        vector<int> empty = {};
        REQUIRE(countFedAnimals(empty, empty) == 0);
    }

    SECTION("Not enough necessary portions") {
        vector<int> animals = {4, 5, 6};
        vector<int> portions = {3, 4, 5};
        REQUIRE(countFedAnimals(animals, portions) == 2);
    }

    SECTION("Excess of portions") {
        vector<int> animals = {2, 3};
        vector<int> portions = {1, 1, 2, 2, 3, 3};
        REQUIRE(countFedAnimals(animals, portions) == 2);
    }

    SECTION("Lack of portions") {
        vector<int> animals = {1, 2, 3, 4, 5};
        vector<int> portions = {3, 4, 5};
        REQUIRE(countFedAnimals(animals, portions) == 3);
    }

    SECTION("Duplicate values") {
        vector<int> animals = {2, 2, 2, 2};
        vector<int> portions = {2, 2, 2};
        REQUIRE(countFedAnimals(animals, portions) == 3);
    }
}

TEST_CASE("Search extra letter", "[task4]") {
    SECTION("Basic cases") {
        REQUIRE(findDiff("abcd", "abcde") == 'e');
        REQUIRE(findDiff("", "a") == 'a');
        REQUIRE(findDiff("a", "aa") == 'a');
    }

    SECTION("Digits") {
        REQUIRE(findDiff("12345", "123456") == '6');
        REQUIRE(findDiff("9876", "98765") == '5');
    }

    SECTION("Random order") {
        string a = "abcdefghijklmnopqrstuvwxyz";
        string b = a + 'z';
        random_device rd;
        mt19937 g(rd());
        shuffle(b.begin(), b.end(), g);
        REQUIRE(findDiff(a, b) == 'z');
    }
}

bool isValidPair(vector<int>& nums, vector<int>& result, int target) {
    if (result.size() != 2) return false;
    int i = result[0], j = result[1];
    if (i < 0 || i >= nums.size() || j < 0 || j >= nums.size()) return false;
    if (i == j) return false;
    return nums[i] + nums[j] == target;
}

string vecToString(const vector<int>& v) {
    string s = "[";
    for (size_t i = 0; i < v.size(); i++) {
        if (i > 0) s += ", ";
        s += to_string(v[i]);
    }
    s += "]";
    return s;
}

TEST_CASE("Search for two elements in a sum equal to the target", "[task5]") {
    vector<tuple<vector<int>, int, bool>> test_cases = {
        {{2, 7, 11, 15}, 9, true},
        {{-3, 4, 3, 90}, 0, true},
        {{1, 2, 3, 4}, 10, false},
        {{-1, -2, -3, -4, -5}, -8, true},
        {{0, 4, 3, 0}, 0, true},
        {{5}, 5, false},
        {{5, 5, 5}, 10, true}
    };
    
    for (auto& [nums, target, answ] : test_cases) {
        DYNAMIC_SECTION("Array " << vecToString(nums) << ", target = " 
                        << target << ", answer = " << (answ ? "Yes" : "No")) {
            vector<int> result = twoSum(nums, target);
            REQUIRE(isValidPair(nums, result, target) == answ);
        }
    }
}