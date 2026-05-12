#pragma once


#include <vector>
#include <queue>
#include <optional>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    int balance_factor;
    
    TreeNode(int x) : val(x), left(nullptr), right(nullptr), balance_factor(0){}
};


class BinaryTree {
private:
    TreeNode* root;
    static TreeNode* buildTree(const std::vector<std::optional<int>>& arr, int index);
    static void destroyTree(TreeNode* node);
    static void mirrorRecursive(TreeNode* node);
    static int countNodes(TreeNode* node) {
        if (!node) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

public:
    BinaryTree(const std::vector<std::optional<int>>& arr) {
        root = buildTree(arr, 0);
    }  
    virtual ~BinaryTree() {
        destroyTree(root);
    }
    TreeNode* getRoot() const {
        return root;
    }
    bool isComplete();
    void mirror() {
        mirrorRecursive(root);
    }
    int size() const{
     return countNodes(root);
    }
};


enum class Mode {
    SMALLEST,
    LARGEST
};

class BinarySearchTree: public BinaryTree {
private:
    static std::optional<int> inorderTraversal(TreeNode* node, int k, int& count);
    static std::optional<int> reverseInorderTraversal(TreeNode* node, int k, int& count);
    static int computeHeightAndBalance(TreeNode* node);

public: 
    using BinaryTree::BinaryTree;
    std::optional<int> findKthElement(int k, Mode mode) const;
    void calculateBalanceFactors() {
        computeHeightAndBalance(getRoot());
    }
};

struct HeapNode {
    int value;
    int arrayIndex;  
    int elementIndex; 
    
    bool operator >(const HeapNode& other) const {
        return value > other.value;
    }
};


std::vector<int> mergeKSortedArrays(const std::vector<std::vector<int>>& arrays);

int findKthElement(const std::vector<int>& nums, int k, Mode mode);

bool compareTrees(const BinaryTree& p, const BinaryTree& q);