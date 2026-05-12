#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "algorithms.hpp"
#include <vector>
#include <unordered_map>
#include <string>


using namespace std;

TEST_CASE("largestIncreasingSequence", "[task1]") {
    SECTION("Basic cases") {
        vector<int> arr1 = {3, 2, 8, 9, 5, 10};
        CHECK(largestIncreasingSequence(arr1) == 3);
        
        vector<int> arr2 = {1, 2, 7, 9, 0, 10};
        CHECK(largestIncreasingSequence(arr2) == 4);
        
        vector<int> arr3 = {8, 8, 8, 8};
        CHECK(largestIncreasingSequence(arr3) == 1);
    }
    
    SECTION("Empty array") {
        vector<int> arr = {};
        CHECK(largestIncreasingSequence(arr) == 0);
    }
    
    SECTION("Single element") {
        vector<int> arr = {2};
        CHECK(largestIncreasingSequence(arr) == 1);
    }
    
    SECTION("Strictly increasing array") {
        vector<int> arr = {1, 2, 3, 4, 5};
        CHECK(largestIncreasingSequence(arr) == 5);
    }
    
    SECTION("Strictly decreasing array") {
        vector<int> arr = {5, 4, 3, 2, 1};
        CHECK(largestIncreasingSequence(arr) == 1);
    }
    
    SECTION("Sequence with equal elements") {
        vector<int> arr = {1, 1, 2, 2, 3, 3};
        CHECK(largestIncreasingSequence(arr) == 2);
    }
    
    SECTION("Multiple increasing sequences") {
        vector<int> arr = {1, 2, 3, 1, 2, 3, 4, 5, 0, 1};
        CHECK(largestIncreasingSequence(arr) == 5);
    }
}

TEST_CASE("buildPascalTriangle", "[task2]") {
    SECTION("n = 0") {
        auto result = buildPascalTriangle(0);
        CHECK(result.empty());
    }
    
    SECTION("n = 1") {
        auto result = buildPascalTriangle(1);
        REQUIRE(result.size() == 1);
        CHECK(result[0] == vector<int>{1});
    }
    
    SECTION("n = 2") {
        auto result = buildPascalTriangle(2);
        REQUIRE(result.size() == 2);
        CHECK(result[0] == vector<int>{1});
        CHECK(result[1] == vector<int>{1, 1});
    }
    
    SECTION("n = 3") {
        auto result = buildPascalTriangle(3);
        REQUIRE(result.size() == 3);
        CHECK(result[0] == vector<int>{1});
        CHECK(result[1] == vector<int>{1, 1});
        CHECK(result[2] == vector<int>{1, 2, 1});
    }
    
    SECTION("n = 5") {
        auto result = buildPascalTriangle(5);
        REQUIRE(result.size() == 5);
        
        CHECK(result[0] == vector<int>{1});
        CHECK(result[1] == vector<int>{1, 1});
        CHECK(result[2] == vector<int>{1, 2, 1});
        CHECK(result[3] == vector<int>{1, 3, 3, 1});
        CHECK(result[4] == vector<int>{1, 4, 6, 4, 1});
    }
    
    SECTION("Negative n") {
        auto result = buildPascalTriangle(-5);
        CHECK(result.empty());
    }
}

TEST_CASE("minCoinsNumber", "[task3]") {
    SECTION("Standard cases") {
        vector<int> coins1 = {1, 2, 5};
        unordered_map<int, int> memo1;
        CHECK(minCoinsNumber(coins1, 11, memo1) == 3);
        
        vector<int> coins2 = {2};
        unordered_map<int, int> memo2;
        CHECK(minCoinsNumber(coins2, 3, memo2) == -1);
        
        vector<int> coins3 = {1};
        unordered_map<int, int> memo3;
        CHECK(minCoinsNumber(coins3, 0, memo3) == 0);
    }
    
    SECTION("Amount = 0") {
        vector<int> coins = {1, 2, 5};
        unordered_map<int, int> memo;
        CHECK(minCoinsNumber(coins, 0, memo) == 0);
    }
    
    SECTION("Empty coins array") {
        vector<int> coins = {};
        unordered_map<int, int> memo;
        CHECK(minCoinsNumber(coins, 10, memo) == -1);
    }
    
    SECTION("Negative amount") {
        vector<int> coins = {1, 2, 5};
        unordered_map<int, int> memo;
        CHECK(minCoinsNumber(coins, -5, memo) == -1);
    }
    
    SECTION("Amount equals coin denomination") {
        vector<int> coins = {1, 3, 4, 5};
        unordered_map<int, int> memo;
        CHECK(minCoinsNumber(coins, 4, memo) == 1);
    }
    
    SECTION("Multiple ways, need minimal coins") {
        vector<int> coins = {1, 3, 4};
        unordered_map<int, int> memo;
        CHECK(minCoinsNumber(coins, 6, memo) == 2);
    }
    
    SECTION("Large amount with coin 1") {
        vector<int> coins = {1};
        unordered_map<int, int> memo;
        CHECK(minCoinsNumber(coins, 100, memo) == 100);
    }
    
    SECTION("Unreachable amount") {
        vector<int> coins = {2, 4, 6};
        unordered_map<int, int> memo;
        CHECK(minCoinsNumber(coins, 5, memo) == -1);
        CHECK(minCoinsNumber(coins, 7, memo) == -1);
    }

    SECTION("Large amount") {
        vector<int> coins = {1, 2, 5};
        unordered_map<int, int> memo;
        CHECK(minCoinsNumber(coins, 100, memo) == 20);
    }
}

TEST_CASE("maxPalindrome", "[task4]") {
    SECTION("Basic cases") {
        CHECK(maxPalindrome("babad") == "bab");
        CHECK(maxPalindrome("cbbd") == "bb");
        CHECK(maxPalindrome("a") == "a");
        CHECK(maxPalindrome("ac") == "a");
    }
    
    SECTION("Single character") {
        CHECK(maxPalindrome("a") == "a");
        CHECK(maxPalindrome("z") == "z");
    }
    
    SECTION("Empty string") {
        CHECK(maxPalindrome("") == "");
    }
    
    SECTION("All characters same") {
        CHECK(maxPalindrome("aaaaa") == "aaaaa");
        CHECK(maxPalindrome("bbbb") == "bbbb");
    }
    
    SECTION("Even length palindrome") {
        CHECK(maxPalindrome("abba") == "abba");
        CHECK(maxPalindrome("123321") == "123321");
    }
    
    SECTION("Odd length palindrome") {
        CHECK(maxPalindrome("racecar") == "racecar");
        CHECK(maxPalindrome("abcba") == "abcba");
    }
    
    SECTION("Palindrome at the end") {
        CHECK(maxPalindrome("abccdfgdcaba") == "aba");
    }
    
    SECTION("Palindrome at the beginning") {
        CHECK(maxPalindrome("abacdfg") == "aba");
    }
    
    SECTION("No palindrome longer than 1") {
        string result = maxPalindrome("abcdef");
        CHECK((result == "a" || result == "b" || result == "c" || 
               result == "d" || result == "e" || result == "f"));
    }
}