#include "algorithms.hpp"
#include <vector>
#include <queue>
#include <optional>


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

namespace {
    bool isMirror(TreeNode* left, TreeNode* right) {
        if (!left && !right) return true;
    
        if (!left || !right) return false;
    
        return (left->val == right->val) &&
            isMirror(left->left, right->right) &&
            isMirror(left->right, right->left);
    }

    bool isSameNodes(TreeNode* p, TreeNode* q) {
        if (!p && !q) return true;

        if (!p || !q) return false;
        return (p->val == q->val) &&
            isSameNodes(p->left, q->left) &&
            isSameNodes(p->right, q->right);
    }
}

bool BinaryTree::isSymmetric() const{
    if (!root) return true;
    
    return isMirror(root->left, root->right);
}

int BinaryTree::minDepth() const{
    if (!root) return 0;
    
    std::queue<std::pair<TreeNode*, int>> q;
    q.push({root, 1});
    
    while (!q.empty()) {
        auto [node, depth] = q.front();
        q.pop();
        
        if (!node->left && !node->right) {
            return depth;
        }
        if (node->left) {
            q.push({node->left, depth + 1});
        }
        if (node->right) {
            q.push({node->right, depth + 1});
        }
    }
    
    return 0;
}

int BinarySearchTree::findMin() const{
    if (!getRoot()) throw "Empty tree";
    
    TreeNode* current = getRoot();
    while (current->left) {
        current = current->left;
    }
    return current->val;
}

int BinarySearchTree::findMax() const{
    if (!getRoot()) throw "Empty tree";
    
    TreeNode* current = getRoot();
    while (current->right) {
        current = current->right;
    }
    return current->val;
}

bool isSameTree(const BinaryTree& p, const BinaryTree& q) {
    return isSameNodes(p.getRoot(), q.getRoot());
}
