#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include "algorithms.hpp"

using namespace std;


TEST_CASE("rotateArray - cyclic rotation of array part", "[task1]") {
    SECTION("Basic case") {
        vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
        rotateArray(arr, 3);
        REQUIRE(arr == vector<int>{5, 6, 7, 1, 2, 3, 4});
    }
    
    SECTION("Rotation by 0") {
        vector<int> arr = {1, 2, 3, 4, 5};
        rotateArray(arr, 0);
        REQUIRE(arr == vector<int>{1, 2, 3, 4, 5});
    }
    
    SECTION("Rotation by array size") {
        vector<int> arr = {1, 2, 3};
        rotateArray(arr, 3);
        REQUIRE(arr == vector<int>{1, 2, 3});
    }
    
    SECTION("Rotation by negative number") {
        vector<int> arr = {1, 2, 3, 4};
        rotateArray(arr, -2);
        REQUIRE(arr == vector<int>{1, 2, 3, 4});
    }
    
    SECTION("Rotation by number larger than size") {
        vector<int> arr = {1, 2, 3};
        rotateArray(arr, 5);
        REQUIRE(arr == vector<int>{2, 3, 1});
    }
    
    SECTION("Empty array") {
        vector<int> arr;
        rotateArray(arr, 5);
        REQUIRE(arr.empty());
    }
}

TEST_CASE("mergeArrays - merging sorted arrays", "[task2]") {
    SECTION("Both arrays non-empty") {
        vector<int> arr1 = {1, 3, 5, 7};
        vector<int> arr2 = {2, 4, 6, 8};
        auto result = mergeArrays(arr1, arr2);
        REQUIRE(result == vector<int>{1, 2, 3, 4, 5, 6, 7, 8});
    }
    
    SECTION("First array empty") {
        vector<int> arr1;
        vector<int> arr2 = {1, 2, 3};
        auto result = mergeArrays(arr1, arr2);
        REQUIRE(result == vector<int>{1, 2, 3});
    }
    
    SECTION("Second array empty") {
        vector<int> arr1 = {4, 5, 6};
        vector<int> arr2;
        auto result = mergeArrays(arr1, arr2);
        REQUIRE(result == vector<int>{4, 5, 6});
    }
    
    SECTION("Arrays with duplicate elements") {
        vector<int> arr1 = {1, 2, 2, 3};
        vector<int> arr2 = {2, 3, 4};
        auto result = mergeArrays(arr1, arr2);
        REQUIRE(result == vector<int>{1, 2, 2, 2, 3, 3, 4});
    }
    
    SECTION("Negative numbers") {
        vector<int> arr1 = {-5, -3, -1};
        vector<int> arr2 = {-4, -2, 0};
        auto result = mergeArrays(arr1, arr2);
        REQUIRE(result == vector<int>{-5, -4, -3, -2, -1, 0});
    }
}

TEST_CASE("mergeArraysInPlays - merging without extra memory", "[task3]") {
    SECTION("Basic case") {
        vector<int> arr1 = {1, 3, 5, 0, 0, 0};
        vector<int> arr2 = {2, 4, 6};
        mergeArraysInPlays(arr1, 3, arr2, 3);
        REQUIRE(arr1 == vector<int>{1, 2, 3, 4, 5, 6});
    }
    
    SECTION("One array empty") {
        vector<int> arr1 = {1, 2, 3, 0, 0, 0};
        vector<int> arr2;
        mergeArraysInPlays(arr1, 3, arr2, 0);
        REQUIRE(arr1 == vector<int>{1, 2, 3, 0, 0, 0});
    }
    
    SECTION("All elements of first smaller than second") {
        vector<int> arr1 = {1, 2, 3, 0, 0};
        vector<int> arr2 = {4, 5};
        mergeArraysInPlays(arr1, 3, arr2, 2);
        REQUIRE(arr1 == vector<int>{1, 2, 3, 4, 5});
    }
    
    SECTION("All elements of second smaller than first") {
        vector<int> arr1 = {4, 5, 6, 0, 0};
        vector<int> arr2 = {1, 2};
        mergeArraysInPlays(arr1, 3, arr2, 2);
        REQUIRE(arr1 == vector<int>{1, 2, 4, 5, 6});
    }
}

TEST_CASE("sort0_1 - sorting 0 and 1", "[task4]") {
    SECTION("Random order") {
        vector<int> arr = {0, 1, 1, 0, 1, 0, 1};
        sort0_1(arr);
        REQUIRE(arr == vector<int>{0, 0, 0, 1, 1, 1, 1});
    }
    
    SECTION("All zeros") {
        vector<int> arr = {0, 0, 0, 0};
        sort0_1(arr);
        REQUIRE(arr == vector<int>{0, 0, 0, 0});
    }
    
    SECTION("All ones") {
        vector<int> arr = {1, 1, 1, 1};
        sort0_1(arr);
        REQUIRE(arr == vector<int>{1, 1, 1, 1});
    }
    
    SECTION("Empty array") {
        vector<int> arr;
        sort0_1(arr);
        REQUIRE(arr.empty());
    }
    
    SECTION("Single element") {
        vector<int> arr = {0};
        sort0_1(arr);
        REQUIRE(arr == vector<int>{0});
        
        arr = {1};
        sort0_1(arr);
        REQUIRE(arr == vector<int>{1});
    }
}

TEST_CASE("sort0_1_2 - sorting 0, 1 and 2", "[task5]") {
    SECTION("Random order") {
        vector<int> arr = {2, 0, 2, 1, 1, 0};
        sort0_1_2(arr);
        REQUIRE(arr == vector<int>{0, 0, 1, 1, 2, 2});
    }
    
    SECTION("All zeros") {
        vector<int> arr = {0, 0, 0};
        sort0_1_2(arr);
        REQUIRE(arr == vector<int>{0, 0, 0});
    }
    
    SECTION("All ones") {
        vector<int> arr = {1, 1, 1};
        sort0_1_2(arr);
        REQUIRE(arr == vector<int>{1, 1, 1});
    }
    
    SECTION("All twos") {
        vector<int> arr = {2, 2, 2};
        sort0_1_2(arr);
        REQUIRE(arr == vector<int>{2, 2, 2});
    }

    SECTION("Only zeros and ones") {
        vector<int> arr = {0, 1, 0, 0, 1};
        sort0_1_2(arr);
        REQUIRE(arr == vector<int>{0, 0, 0, 1, 1});
    }

    SECTION("Only ones and twos") {
        vector<int> arr = {2, 1, 1, 2, 1};
        sort0_1_2(arr);
        REQUIRE(arr == vector<int>{1, 1, 1, 2, 2});
    }

    SECTION("Only zeros and twos") {
        vector<int> arr = {0, 2, 0, 2, 2};
        sort0_1_2(arr);
        REQUIRE(arr == vector<int>{0, 0, 2, 2, 2});
    }
    
    SECTION("Combination of all three") {
        vector<int> arr = {2, 0, 1};
        sort0_1_2(arr);
        REQUIRE(arr == vector<int>{0, 1, 2});
    }
    
    SECTION("Empty array") {
        vector<int> arr;
        sort0_1_2(arr);
        REQUIRE(arr.empty());
    }
}

TEST_CASE("evenFirst - even numbers to front", "[task6]") {
    SECTION("Basic case") {
        vector<int> arr = {3, 2, 4, 1, 11, 8, 9};
        evenFirst(arr);
        REQUIRE(arr == vector<int>{2, 4, 8, 1, 11, 3, 9});
    }
    
    SECTION("All even") {
        vector<int> arr = {2, 4, 6, 8};
        evenFirst(arr);
        REQUIRE(arr == vector<int>{2, 4, 6, 8});
    }
    
    SECTION("All odd") {
        vector<int> arr = {1, 3, 5, 7};
        evenFirst(arr);
        REQUIRE(arr == vector<int>{1, 3, 5, 7});
    }
    
    SECTION("Empty array") {
        vector<int> arr;
        evenFirst(arr);
        REQUIRE(arr.empty());
    }
    
    SECTION("With negative numbers") {
        vector<int> arr = {-3, 2, -5, 4, -1};
        evenFirst(arr);
        REQUIRE(arr == vector<int>{2, 4, -5, -3, -1});
    }
}

TEST_CASE("zeroLast - zeros to end", "[task7]") {
    SECTION("Basic case") {
        vector<int> arr = {0, 1, 0, 3, 12};
        zeroLast(arr);
        REQUIRE(arr == vector<int>{1, 3, 12, 0, 0});
    }
    
    SECTION("All zeros") {
        vector<int> arr = {0, 0, 0};
        zeroLast(arr);
        REQUIRE(arr == vector<int>{0, 0, 0});
    }
    
    SECTION("No zeros") {
        vector<int> arr = {1, 2, 3, 4};
        zeroLast(arr);
        REQUIRE(arr == vector<int>{1, 2, 3, 4});
    }
    
    SECTION("Empty array") {
        vector<int> arr;
        zeroLast(arr);
        REQUIRE(arr.empty());
    }
    
    SECTION("Zeros at beginning") {
        vector<int> arr = {0, 0, 1, 2, 3};
        zeroLast(arr);
        REQUIRE(arr == vector<int>{1, 2, 3, 0, 0});
    }
    
    SECTION("Zeros at end") {
        vector<int> arr = {1, 2, 3, 0, 0};
        zeroLast(arr);
        REQUIRE(arr == vector<int>{1, 2, 3, 0, 0});
    }
}