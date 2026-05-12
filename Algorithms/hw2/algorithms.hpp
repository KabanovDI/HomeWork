#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <vector>
#include <string>

class ListNode {
    public:
        int val; 
        ListNode* next;
        ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* reverseList(ListNode* head);
ListNode* createList(int n);
void deleteList(ListNode* head);
std::vector<int> listToVector(ListNode* head);
ListNode* createListFromVector(const std::vector<int>& values);
ListNode* findMiddle(ListNode* head);
ListNode* deleteNode(ListNode* head, int goal);
bool compareStrings(std::string a, std::string b);
bool findMatch(std::vector<int>& arr, int target);
bool isPalindrome(std::string& str);
void removeDuplicate(ListNode* head);
ListNode* mergeLists(ListNode* a, ListNode* b);

#endif