#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "algorithms.hpp"
#include <vector>
#include <string>

TEST_CASE("Reverse linked list", "[task1]") {
    SECTION("Empty list") {
        ListNode* head = nullptr;
        ListNode* reversed = reverseList(head);
        REQUIRE(reversed == nullptr);
    }
    
    SECTION("Single element list") {
        ListNode* head = new ListNode(42);
        ListNode* reversed = reverseList(head);
        
        REQUIRE(reversed != nullptr);
        REQUIRE(reversed->val == 42);
        REQUIRE(reversed->next == nullptr);
        
        deleteList(reversed);  
    }
    
    SECTION("Multiple elements list") {
        ListNode* head = createList(5); 
        ListNode* reversed = reverseList(head);
        std::vector<int> expected = {5,4,3,2,1};
        REQUIRE(listToVector(reversed) == expected);
        
        deleteList(reversed);  
    }

    SECTION("Double reverse should return original") {
        ListNode* original = createList(4); 
        ListNode* reversed = reverseList(original); 
        ListNode* doubleReversed = reverseList(reversed); 
        
        REQUIRE(listToVector(doubleReversed) == listToVector(original));
        
        deleteList(doubleReversed); 
    }
}

TEST_CASE("Finding middle of list", "[task2]") {
    SECTION("Empty list") {
        ListNode* head = nullptr;
        ListNode* mid = findMiddle(head);

        REQUIRE(mid == nullptr);
    }

    SECTION("Single element list") {
        ListNode* test = new ListNode(1);
        ListNode* mid = findMiddle(test);

        REQUIRE(mid == test);
        REQUIRE(mid->next == nullptr);
        REQUIRE(mid->val == 1);
        
        deleteList(test); 
    }

    SECTION("Two elements list") {
        ListNode* test = createList(2);
        ListNode* mid = findMiddle(test);

        REQUIRE(test->next == mid);
        REQUIRE(mid->val == 2);
        REQUIRE(mid->next == nullptr);
        
        deleteList(test);  
    }

    SECTION("Odd number of elements") {
        ListNode* test = createList(5);
        ListNode* mid = findMiddle(test);

        REQUIRE(mid == test->next->next);
        REQUIRE(mid->val == 3);
        REQUIRE(mid->next == test->next->next->next);
        
        deleteList(test);  
    }

    SECTION("Even number of elements") {
        ListNode* test = createList(4);
        ListNode* mid = findMiddle(test);

        REQUIRE(mid == test->next->next);
        REQUIRE(mid->val == 3);
        REQUIRE(mid->next == test->next->next->next);
        
        deleteList(test);  
    }
}

TEST_CASE("Delete node from linked list", "[task3]") {
    SECTION("Delete head node") {
        ListNode* list = createList(5); 
        list = deleteNode(list, 1);
        std::vector<int> expected = {2,3,4,5};
        REQUIRE(listToVector(list) == expected);
        deleteList(list);
    }
    
    SECTION("Delete middle node") {
        ListNode* list = createList(5); 
        list = deleteNode(list, 3);
        std::vector<int> expected = {1,2,4,5};
        REQUIRE(listToVector(list) == expected);
        deleteList(list);
    }
    
    SECTION("Delete last node") {
        ListNode* list = createList(5); 
        list = deleteNode(list, 5);
        std::vector<int> expected = {1,2,3,4};
        REQUIRE(listToVector(list) == expected);
        deleteList(list);
    }
    
    SECTION("Delete from single element list") {
        ListNode* list = createList(1); 
        list = deleteNode(list, 1);
        REQUIRE(list == nullptr);
    }
    
    SECTION("Delete non-existent element") {
        ListNode* list = createList(3); 
        list = deleteNode(list, 5);
        std::vector<int> expected = {1,2,3};
        REQUIRE(listToVector(list) == expected);
        deleteList(list);
    }
}

TEST_CASE("Compare two strings", "[task4]") {
    
    SECTION("B contains all elements of A in order") {
        std::string A = "123";
        std::string B = "12345";
        
        REQUIRE(compareStrings(A, B) == true);
        
        std::string().swap(A);
        std::string().swap(B);
    }
    
    SECTION("B contains all elements of A but with extra elements in between") {
        std::string A = "123";
        std::string B = "112233";
        
        REQUIRE(compareStrings(A, B) == true);
        
        std::string().swap(A);
        std::string().swap(B);
    }
    
    SECTION("A is empty") {
        std::string A = "";
        std::string B = "12345";
        
        REQUIRE(compareStrings(A, B) == true);
        
        std::string().swap(A);
        std::string().swap(B);
    }
    
    SECTION("B is empty, A non-empty") {
        std::string A = "123";
        std::string B = "";
        
        REQUIRE(compareStrings(A, B) == false);
        
        std::string().swap(A);
        std::string().swap(B);
    }
    
    SECTION("Both strings empty") {
        std::string A = "";
        std::string B = "";
        
        REQUIRE(compareStrings(A, B) == true);
        
        std::string().swap(A);
        std::string().swap(B);
    }
    
    SECTION("A longer than B") {
        std::string A = "12345";
        std::string B = "123";
        
        REQUIRE(compareStrings(A, B) == false);
        
        std::string().swap(A);
        std::string().swap(B);
    }
    
    SECTION("Elements in different order") {
        std::string A = "123";
        std::string B = "32145";
        
        REQUIRE(compareStrings(A, B) == false);
        
        std::string().swap(A);
        std::string().swap(B);
    }
    
    SECTION("Missing elements in B") {
        std::string A = "1236";
        std::string B = "12345";
        
        REQUIRE(compareStrings(A, B) == false);
        
        std::string().swap(A);
        std::string().swap(B);
    }
    
    SECTION("Duplicate elements") {
        std::string A = "12234";
        std::string B = "12345";
        
        REQUIRE(compareStrings(A, B) == false);
        
        std::string().swap(A);
        std::string().swap(B);
    }
    
    SECTION("Single element strings") {
        std::string A = "1";
        std::string B = "1";
        
        REQUIRE(compareStrings(A, B) == true);
   
        A = "1";
        B = "2";
        
        REQUIRE(compareStrings(A, B) == false);
        
        std::string().swap(A);
        std::string().swap(B);
    }
           
    SECTION("Performance with large strings") {
        std::string A, B;
        for (int i = 0; i <= 100; i++) {
            A.append(std::to_string(i));
        }
        for (int i = 0; i <= 200; i++) {
            B.append(std::to_string(i));
        }

        REQUIRE(compareStrings(A, B) == true);
        
        std::string().swap(A);
        std::string().swap(B);
    }
}

TEST_CASE("Find pair sum in sorted array", "[task5]") {
    SECTION("Target sum exists") {
        std::vector<int> arr = {1,2,3,4,5,6};
        REQUIRE(findMatch(arr, 7) == true); 
        REQUIRE(findMatch(arr, 3) == true);  
        REQUIRE(findMatch(arr, 11) == true); 
    }
    
    SECTION("Target sum doesn't exist") {
        std::vector<int> arr = {1,2,3,4,5,6};
        REQUIRE(findMatch(arr, 1) == false);
        REQUIRE(findMatch(arr, 13) == false);
        REQUIRE(findMatch(arr, 0) == false);
    }
    
    SECTION("Empty array") {
        std::vector<int> arr;
        REQUIRE(findMatch(arr, 5) == false);
    }
    
    SECTION("Single element array") {
        std::vector<int> arr = {5};
        REQUIRE(findMatch(arr, 5) == false);
        REQUIRE(findMatch(arr, 10) == false);
    }
    
    SECTION("Array with negative numbers") {
        std::vector<int> arr = {-5,-3,-1,0,2,3,6};
        REQUIRE(findMatch(arr, -4) == true);  
        REQUIRE(findMatch(arr, 0) == true);   
        REQUIRE(findMatch(arr, -7) == false);
    }
}

TEST_CASE("Check if string is palindrome", "[task6]") {
    SECTION("Valid palindromes") {
        std::string s1 = "racecar";
        REQUIRE(isPalindrome(s1) == true);
        
        std::string s2 = "madam";
        REQUIRE(isPalindrome(s2) == true);
        
        std::string s3 = "a";
        REQUIRE(isPalindrome(s3) == true);
        
        std::string s4 = "aa";
        REQUIRE(isPalindrome(s4) == true);
    }
    
    SECTION("Invalid palindromes") {
        std::string s1 = "hello";
        REQUIRE(isPalindrome(s1) == false);
        
        std::string s2 = "racecarx";
        REQUIRE(isPalindrome(s2) == false);
        
        std::string s3 = "ab";
        REQUIRE(isPalindrome(s3) == false);
    }
    
    SECTION("Empty string") {
        std::string s = "";
        REQUIRE(isPalindrome(s) == true);
    }
    
    SECTION("Case sensitivity") {
        std::string s1 = "Racecar"; 
        REQUIRE(isPalindrome(s1) == false); 
    }
}

TEST_CASE("Remove duplicates from sorted list", "[task7]") {
    SECTION("List with duplicates") {
        ListNode* list = createListFromVector({1,2,3,3,4,5,5});   
        removeDuplicate(list);
        std::vector<int> expected = {1,2,3,4,5};
        REQUIRE(listToVector(list) == expected);
        deleteList(list);
    }
    
    SECTION("List without duplicates") {
        ListNode* list = createList(5); 
        removeDuplicate(list);
        std::vector<int> expected = {1,2,3,4,5};
        REQUIRE(listToVector(list) == expected);
        deleteList(list);
    }
    
    SECTION("Empty list") {
        ListNode* list = nullptr;
        removeDuplicate(list); 
        REQUIRE(list == nullptr);
    }
    
    SECTION("Single element list") {
        ListNode* list = createList(1);
        removeDuplicate(list);
        std::vector<int> expected = {1};
        REQUIRE(listToVector(list) == expected);
        deleteList(list);
    }
    SECTION("All elements same") {
        ListNode* list = createListFromVector({1,1,1,1,1});
        removeDuplicate(list);
        std::vector<int> expected = {1};
        REQUIRE(listToVector(list) == expected);
        deleteList(list);
    }
}

TEST_CASE("Merge two sorted lists", "[task8]") {
    SECTION("Both lists non-empty") {
        ListNode* list1 = createList(3); 
        ListNode* list2 = createListFromVector({4,5,6});
        
        ListNode* merged = mergeLists(list1, list2);
        std::vector<int> expected = {1,2,3,4,5,6};
        REQUIRE(listToVector(merged) == expected);
        deleteList(merged);
    }
    
    SECTION("First list empty") {
        ListNode* list1 = nullptr;
        ListNode* list2 = createList(3); 
        
        ListNode* merged = mergeLists(list1, list2);
        std::vector<int> expected = {1,2,3};
        REQUIRE(listToVector(merged) == expected);
        deleteList(merged);
    }
    
    SECTION("Second list empty") {
        ListNode* list1 = createList(3); 
        ListNode* list2 = nullptr;
        
        ListNode* merged = mergeLists(list1, list2);
        std::vector<int> expected = {1,2,3};
        REQUIRE(listToVector(merged) == expected);
        deleteList(merged);
    }
    
    SECTION("Both lists empty") {
        ListNode* list1 = nullptr;
        ListNode* list2 = nullptr;
        
        ListNode* merged = mergeLists(list1, list2);
        REQUIRE(merged == nullptr);
    }
    
    SECTION("Interleaved lists") {
        ListNode* list1 = createListFromVector({1,3,5});
        ListNode* list2 = createListFromVector({2,4,6}); 
        
        ListNode* merged = mergeLists(list1, list2);
        std::vector<int> expected = {1,2,3,4,5,6};
        REQUIRE(listToVector(merged) == expected);
        deleteList(merged);
    }
    
    SECTION("Lists with different lengths") {
        ListNode* list1 = createListFromVector({1,3,5,7,9});
        ListNode* list2 = createListFromVector({2,4,6});

        ListNode* merged = mergeLists(list1, list2);
        std::vector<int> expected = {1,2,3,4,5,6,7,9};
        REQUIRE(listToVector(merged) == expected);
        deleteList(merged);
    }
}
