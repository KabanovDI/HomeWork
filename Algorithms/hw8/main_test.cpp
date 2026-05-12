#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "algorithms.hpp"

TEST_CASE("Maximum sum subarray of length K", "[task1]") {
    SECTION("Basic cases") {
        std::vector<int> arr1 = {2, -3, 5, 1, -2, 4, 6, -1, 3};
        REQUIRE(maxSumSubarray(arr1, 3) == 9);
        
        std::vector<int> arr2 = {1, 2, 3, 4, 5};
        REQUIRE(maxSumSubarray(arr2, 2) == 9);
        
        std::vector<int> arr3 = {-1, -2, -3, -4};
        REQUIRE(maxSumSubarray(arr3, 2) == -3);
    }
    
    SECTION("Single element") {
        std::vector<int> arr = {10};
        REQUIRE(maxSumSubarray(arr, 1) == 10);
    }
    
    SECTION("All zeros") {
        std::vector<int> arr = {0, 0, 0, 0, 0};
        REQUIRE(maxSumSubarray(arr, 3) == 0);
    }
    
    SECTION("K equals array length") {
        std::vector<int> arr = {5, -2, 3, 1};
        REQUIRE(maxSumSubarray(arr, 4) == 7);
    }
    
    SECTION("Throws on invalid input") {
        std::vector<int> arr = {1, 2, 3};
        REQUIRE_THROWS_AS(maxSumSubarray(arr, 5), std::string);
        REQUIRE_THROWS_AS(maxSumSubarray(arr, 0), std::string);
    }
}

TEST_CASE("Subarray sum equals K", "[task2]") {
    SECTION("Basic cases") {
        std::vector<int> nums1 = {1, 2, 3, -2, 1, 4, -3, 2, 1};
        REQUIRE(subarraySumEqualsK(nums1, 3) == 8);
        
        std::vector<int> nums2 = {1, 1, 1};
        REQUIRE(subarraySumEqualsK(nums2, 2) == 2);
        
        std::vector<int> nums3 = {1, 2, 3};
        REQUIRE(subarraySumEqualsK(nums3, 6) == 1);
    }
    
    SECTION("Zero K") {
        std::vector<int> nums = {1, -1, 2, -2, 3, -3};
        REQUIRE(subarraySumEqualsK(nums, 0) == 6);
    }
    
    SECTION("Single element") {
        std::vector<int> nums = {5};
        REQUIRE(subarraySumEqualsK(nums, 5) == 1);
        REQUIRE(subarraySumEqualsK(nums, 3) == 0);
    }
    
    SECTION("All zeros") {
        std::vector<int> nums = {0, 0, 0};
        REQUIRE(subarraySumEqualsK(nums, 0) == 6);
    }
    
    SECTION("Negative numbers") {
        std::vector<int> nums = {-1, -2, -3, 6};
        REQUIRE(subarraySumEqualsK(nums, 0) == 1);
        REQUIRE(subarraySumEqualsK(nums, -3) == 2);
    }
    
    SECTION("Empty array") {
        std::vector<int> nums = {};
        REQUIRE(subarraySumEqualsK(nums, 5) == 0);
    }
}

TEST_CASE("Maximum length subarray with equal zeros and ones", "[task3]") {
    SECTION("Basic cases") {
        std::vector<int> nums1 = {0, 1, 0, 0, 1, 1, 0, 1, 0, 0};
        REQUIRE(findMaxLength(nums1) == 8);
        
        std::vector<int> nums2 = {0, 1};
        REQUIRE(findMaxLength(nums2) == 2);
        
        std::vector<int> nums3 = {0, 0, 1, 1, 0};
        REQUIRE(findMaxLength(nums3) == 4);
    }
    
    SECTION("All zeros") {
        std::vector<int> nums = {0, 0, 0, 0};
        REQUIRE(findMaxLength(nums) == 0);
    }
    
    SECTION("All ones") {
        std::vector<int> nums = {1, 1, 1, 1};
        REQUIRE(findMaxLength(nums) == 0);
    }
    
    SECTION("Single element") {
        std::vector<int> nums1 = {0};
        REQUIRE(findMaxLength(nums1) == 0);
        
        std::vector<int> nums2 = {1};
        REQUIRE(findMaxLength(nums2) == 0);
    }
    
    SECTION("Already balanced entire array") {
        std::vector<int> nums = {0, 1, 1, 0, 1, 0};
        REQUIRE(findMaxLength(nums) == 6);
    }
    
    SECTION("Empty array") {
        std::vector<int> nums = {};
        REQUIRE(findMaxLength(nums) == 0);
    }
}

TEST_CASE("Find pivot index in rotated sorted array", "[task4]") {
    SECTION("Basic cases") {
        std::vector<int> nums1 = {4, 5, 6, 7, 0, 1, 2};
        REQUIRE(findPivotIndex(nums1) == 4);
        REQUIRE(nums1[findPivotIndex(nums1)] == 0);
        
        std::vector<int> nums2 = {3, 4, 5, 1, 2};
        REQUIRE(findPivotIndex(nums2) == 3);
        REQUIRE(nums2[findPivotIndex(nums2)] == 1);
        
        std::vector<int> nums3 = {11, 13, 15, 17};
        REQUIRE(findPivotIndex(nums3) == 0);
        REQUIRE(nums3[findPivotIndex(nums3)] == 11);
    }
    
    SECTION("Single element") {
        std::vector<int> nums = {42};
        REQUIRE(findPivotIndex(nums) == 0);
    }
    
    SECTION("Two elements") {
        std::vector<int> nums1 = {1, 2};
        REQUIRE(findPivotIndex(nums1) == 0);
        
        std::vector<int> nums2 = {2, 1};
        REQUIRE(findPivotIndex(nums2) == 1);
    }
    
    SECTION("Array rotated once") {
        std::vector<int> nums = {5, 1, 2, 3, 4};
        REQUIRE(findPivotIndex(nums) == 1);
    }
    
    SECTION("Array fully rotated") {
        std::vector<int> nums = {1, 2, 3, 4, 5};
        REQUIRE(findPivotIndex(nums) == 0);
    }
    
    SECTION("Array with duplicate values") {
        std::vector<int> nums = {2, 2, 2, 0, 2};
        REQUIRE(findPivotIndex(nums) == 3);
    }
}

TEST_CASE("Balanced parentheses check", "[task5]") {
    SECTION("Valid sequences") {
        std::string s1 = "()";
        REQUIRE(isBalancedParentheses(s1) == true);
        
        std::string s2 = "()()";
        REQUIRE(isBalancedParentheses(s2) == true);
        
        std::string s3 = "(())";
        REQUIRE(isBalancedParentheses(s3) == true);
        
        std::string s4 = "(()())";
        REQUIRE(isBalancedParentheses(s4) == true);
        
        std::string s5 = "((()))";
        REQUIRE(isBalancedParentheses(s5) == true);
        
        std::string s6 = "";
        REQUIRE(isBalancedParentheses(s6) == true);
    }
    
    SECTION("Invalid sequences") {
        std::string s1 = ")(";
        REQUIRE(isBalancedParentheses(s1) == false);
        
        std::string s2 = "(()";
        REQUIRE(isBalancedParentheses(s2) == false);
        
        std::string s3 = "())";
        REQUIRE(isBalancedParentheses(s3) == false);
        
        std::string s4 = "((())";
        REQUIRE(isBalancedParentheses(s4) == false);
        
        std::string s5 = "(()))(";
        REQUIRE(isBalancedParentheses(s5) == false);
        
        std::string s6 = "(";
        REQUIRE(isBalancedParentheses(s6) == false);
        
        std::string s7 = ")";
        REQUIRE(isBalancedParentheses(s7) == false);
    }
    
    SECTION("Long sequences") {
        std::string valid = "((((()))))";
        REQUIRE(isBalancedParentheses(valid) == true);
        
        std::string invalid = "((((()))))(";
        REQUIRE(isBalancedParentheses(invalid) == false);
    }
}