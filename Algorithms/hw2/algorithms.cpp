#include "algorithms.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;


ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;
    ListNode* next = nullptr;

    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

ListNode* createList(int n) {
    if (n <= 0) return nullptr;
    ListNode* head = new ListNode(1);
    ListNode* current = head;

    for (int i = 2; i <= n; i++) {
        current->next = new ListNode(i);
        current = current->next;
    }

    return head;
}

void deleteList(ListNode* head) {
    while (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

vector<int> listToVector(ListNode* head) {
    vector<int> result;
    ListNode* current = head;
    while (current != nullptr) {
        result.push_back(current->val);
        current = current->next;
    }
    return result;
}

ListNode* createListFromVector(const vector<int>& values) {
    if (values.empty()) return nullptr;
    
    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    
    for (size_t i = 1; i < values.size(); i++) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    
    return head;
}

ListNode* findMiddle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    if (head == nullptr) return head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

ListNode* deleteNode(ListNode* head, int goal) {
    if (head == nullptr) return head;
    if (head->val == goal) {
        ListNode* new_head = head->next;
        delete head;
        return new_head;    
    }
    ListNode* prev = head;
    ListNode* curr = head->next;
 
    while (curr != nullptr && curr->val != goal) {
        curr = curr->next;
        prev = prev->next;
    }
    if (curr != nullptr) prev->next = curr->next;

    delete curr;
    return head;
}

bool compareStrings(string a, string b) {
    if (a.empty()) return true;
    size_t j = 0;
    for (size_t i = 0; i < b.size(); i++) {
        if (j == a.size()) return true;
        if (a[j] == b[i]) j++;
    }
    return j == a.size();
}

bool findMatch(vector<int>& arr, int target) {
    int i = 0;
    int j = arr.size() - 1;

    while (i < j) {
        if (arr[i] + arr[j] < target) {
            i++;
        } else if (arr[i] + arr[j] > target) {
            j--;
        } else return true;
    }
    return false;
}

bool isPalindrome(string& str) {
    int i = 0;
    int j = str.length() - 1;

    while (i < j) {
        if (str[i] == str[j]) {
            i++;
            j--;
        } else return false;
    }
    return true;
}

void removeDuplicate(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    ListNode* temp = nullptr;

    if (head == nullptr) return;
    while (fast != nullptr) {
        while (fast != nullptr && fast->val == slow->val) {
            fast = fast->next; 
            delete temp;  
            temp = fast;                 
        }
        slow->next = fast;
        slow = fast;
        temp = nullptr;
    }
}

ListNode* mergeLists(ListNode* a, ListNode* b) {
    ListNode* head = a;

    if (a == nullptr) {
        head = b;
        return head;
    } else if (b == nullptr) {
        return head;
    }

    if (a->val > b->val) {
        head = b;
        b = b->next;
    } else a = a->next;

    ListNode* curr = head;
    while (a != nullptr && b != nullptr) {
        if (a->val > b->val) {
            curr->next = b;
            curr = b;
            b = b->next;
        } else {
            curr->next = a;
            curr = a;
            a = a->next;
        }
    }
    if (a == nullptr) {
        curr->next = b;
    } else curr->next = a;

    return head;
}