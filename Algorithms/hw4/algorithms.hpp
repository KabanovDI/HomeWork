#pragma once


#include <vector>
#include <queue>
#include <optional>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


class BinaryTree {
private:
    TreeNode* root;
    static TreeNode* buildTree(const std::vector<std::optional<int>>& arr, int index);
    static void destroyTree(TreeNode* node);

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
    bool isSymmetric() const;
    int minDepth() const;
};


class BinarySearchTree: public BinaryTree {
public: 
    using BinaryTree::BinaryTree;
    int findMin() const;
    int findMax() const;
};


bool isSameTree(const BinaryTree& p, const BinaryTree& q);