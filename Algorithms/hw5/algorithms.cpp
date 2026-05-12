#include "algorithms.hpp"
#include <vector>
#include <queue>
#include <optional>
#include <functional>
#include <algorithm>


using namespace std;

TreeNode* BinaryTree::buildTree(const vector<optional<int>>& arr, int index) {
    if (index >= arr.size() || arr[index] == nullopt) {
        return nullptr;
    }
    
    auto node = new TreeNode(arr[index].value());
    node->left = buildTree(arr, 2 * index + 1);
    node->right = buildTree(arr, 2 * index + 2);

    return node;
}   

void BinaryTree::destroyTree(TreeNode* node) {
    if (node == nullptr) return; 

    destroyTree(node->left);
    destroyTree(node->right);

    delete node;
}

bool BinaryTree::isComplete() {
    if (!root) return true;
    
    queue<TreeNode*> q;
    q.push(root);
    bool encounteredNull = false;
    
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        
        if (node == nullptr) {
            encounteredNull = true;
        } else {
            if (encounteredNull) return false;
            q.push(node->left);
            q.push(node->right);
        }
    }
    
    return true;
}

void BinaryTree::mirrorRecursive(TreeNode* node) {
        if (!node) return;
        
        mirrorRecursive(node->left);
        mirrorRecursive(node->right);
        
        swap(node->left, node->right);
    }

vector<int> mergeKSortedArrays(const vector<vector<int>>& arrays) {
    vector<int> result;
    
    if (arrays.empty()) return result;
    
    size_t totalSize = 0;
    for (const auto& arr : arrays) {
        totalSize += arr.size();
    }
    result.reserve(totalSize);
    
    priority_queue<HeapNode, vector<HeapNode>, greater<HeapNode>> minHeap;
    
    for (int i = 0; i < arrays.size(); i++) {
        if (!arrays[i].empty()) {
            minHeap.push({arrays[i][0], i, 0});
        }
    }
    
    while (!minHeap.empty()) {
        HeapNode current = minHeap.top();
        minHeap.pop();
        
        result.push_back(current.value);
        
        if (current.elementIndex + 1 < arrays[current.arrayIndex].size()) {
            minHeap.push({
                arrays[current.arrayIndex][current.elementIndex + 1],
                current.arrayIndex,
                current.elementIndex + 1
            });
        }
    }
    
    return result;
}

int findKthElement(const vector<int>& nums, int k, Mode mode) {
    if (k <= 0 || k > nums.size()) {
        throw "Invalid k";
    }
    
    if (mode == Mode::SMALLEST) {
        priority_queue<int> maxHeap;
    
        for (int num : nums) {
            maxHeap.push(num);
            if (maxHeap.size() > k) maxHeap.pop(); 
        }
        return maxHeap.top();
    } else if (mode == Mode::LARGEST) {
        priority_queue<int, vector<int>, greater<int>> minHeap;
    
        for (int num : nums) {
            minHeap.push(num);
            if (minHeap.size() > k) minHeap.pop(); 
        }
        return minHeap.top();
    } else throw "Invalid mode";
}

optional<int> BinarySearchTree::inorderTraversal(TreeNode* node, int k, int& count) {
    if (!node) return nullopt;
        
    optional<int> res = inorderTraversal(node->left, k, count);
    if (res.has_value()) return res;

    count++;
    if (count == k) return node->val;

    res = inorderTraversal(node->right, k, count);
    if (res.has_value()) return res;

    return nullopt;
}

optional<int> BinarySearchTree::reverseInorderTraversal(TreeNode* node, int k, int& count) {
    if (!node) return nullopt;
        
    optional<int> res = reverseInorderTraversal(node->right, k, count);
    if (res.has_value()) return res;

    count++;
    if (count == k) return node->val;

    res = reverseInorderTraversal(node->left, k, count);
    if (res.has_value()) return res;

    return nullopt;
}

optional<int> BinarySearchTree::findKthElement(int k, Mode mode) const {
    if (k <= 0) {
        throw "Invalid k";
    }
        
    optional<int> result = nullopt;
    int count = 0;
        
    if (mode == Mode::SMALLEST) {
        result = inorderTraversal(getRoot(), k, count);
    } else if (mode == Mode::LARGEST) {
        result = reverseInorderTraversal(getRoot(), k, count);
    } else throw "Invalid mode";
        
    if (!result.has_value()) throw "k is larger than the number of nodes in the tree";
        
    return result;
}

int BinarySearchTree::computeHeightAndBalance(TreeNode* node) {
        if (!node) return -1;
        
        int leftHeight = computeHeightAndBalance(node->left);
        int rightHeight = computeHeightAndBalance(node->right);
        
        int height = max(leftHeight, rightHeight) + 1;
        
        node->balance_factor = rightHeight - leftHeight;
        
        return height;
    }

namespace {
    bool isSameNodes(TreeNode* p, TreeNode* q) {
        if (!p && !q) return true;

        if (!p || !q) return false;
        return (p->val == q->val) &&
            isSameNodes(p->left, q->left) &&
            isSameNodes(p->right, q->right);
    }
}

bool compareTrees(const BinaryTree& p, const BinaryTree& q) {
    return isSameNodes(p.getRoot(), q.getRoot());
}