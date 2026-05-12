#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "algorithms.hpp"
#include <vector>
#include <optional>


using namespace std;

TEST_CASE("Build binary tree from level-order array", "[task1]") {
    SECTION("Empty tree") {
        vector<optional<int>> arr = {};
        BinaryTree tree(arr);
        REQUIRE(tree.getRoot() == nullptr);
    }

    SECTION("Single node tree") {
        vector<optional<int>> arr = {1};
        BinaryTree tree(arr);
        REQUIRE(tree.getRoot() != nullptr);
        REQUIRE(tree.getRoot()->val == 1);
        REQUIRE(tree.getRoot()->left == nullptr);
        REQUIRE(tree.getRoot()->right == nullptr);
    }

    SECTION("Complete binary tree") {
        //        1
        //       / \
        //      2   3
        //     / \ / \
        //    4  5 6  7
        vector<optional<int>> arr = {1, 2, 3, 4, 5, 6, 7};
        BinaryTree tree(arr);
        
        auto root = tree.getRoot();
        REQUIRE(root->val == 1);
        REQUIRE(root->left->val == 2);
        REQUIRE(root->right->val == 3);
        REQUIRE(root->left->left->val == 4);
        REQUIRE(root->left->right->val == 5);
        REQUIRE(root->right->left->val == 6);
        REQUIRE(root->right->right->val == 7);
    }

    SECTION("Incomplete binary tree with nulls") {
        //        1
        //       / \
        //      2   3
        //       \   \
        //        5   7
        vector<optional<int>> arr = {1, 2, 3, nullopt, 5, nullopt, 7};
        BinaryTree tree(arr);
        
        auto root = tree.getRoot();
        REQUIRE(root->val == 1);
        REQUIRE(root->left->val == 2);
        REQUIRE(root->right->val == 3);
        REQUIRE(root->left->left == nullptr);
        REQUIRE(root->left->right->val == 5);
        REQUIRE(root->right->left == nullptr);
        REQUIRE(root->right->right->val == 7);
    }
}

TEST_CASE("Check if binary tree is symmetric", "[task2]") {
    SECTION("Empty tree is symmetric") {
        vector<optional<int>> arr = {};
        BinaryTree tree(arr);
        REQUIRE(tree.isSymmetric() == true);
    }

    SECTION("Single node is symmetric") {
        vector<optional<int>> arr = {1};
        BinaryTree tree(arr);
        REQUIRE(tree.isSymmetric() == true);
    }

    SECTION("Symmetric tree") {
        //        1
        //       / \
        //      2   2
        //     / \ / \
        //    3  4 4  3
        vector<optional<int>> arr = {1, 2, 2, 3, 4, 4, 3};
        BinaryTree tree(arr);
        REQUIRE(tree.isSymmetric() == true);
    }

    SECTION("Asymmetric tree - different values") {
        //        1
        //       / \
        //      2   2
        //     / \ / \
        //    3  5 4  3
        vector<optional<int>> arr = {1, 2, 2, 3, 5, 4, 3};
        BinaryTree tree(arr);
        REQUIRE(tree.isSymmetric() == false);
    }

    SECTION("Asymmetric tree - missing node") {
        //        1
        //       / \
        //      2   2
        //       \   \
        //        3   3
        vector<optional<int>> arr = {1, 2, 2, nullopt, 3, nullopt, 3};
        BinaryTree tree(arr);
        REQUIRE(tree.isSymmetric() == false);
    }

    SECTION("Asymmetric tree - structure mismatch") {
        //        1
        //       / \
        //      2   2
        //     /     \
        //    3       3
        vector<optional<int>> arr = {1, 2, 2, 3, nullopt, nullopt, 3};
        BinaryTree tree(arr);
        REQUIRE(tree.isSymmetric() == true); 
    }
}

TEST_CASE("Find minimum depth of binary tree", "[task3]") {
    SECTION("Empty tree depth = 0") {
        vector<optional<int>> arr = {};
        BinaryTree tree(arr);
        REQUIRE(tree.minDepth() == 0);
    }

    SECTION("Single node depth = 1") {
        vector<optional<int>> arr = {1};
        BinaryTree tree(arr);
        REQUIRE(tree.minDepth() == 1);
    }

    SECTION("Perfect tree of height 3, min depth = 3") {
        //        1
        //       / \
        //      2   3
        //     / \ / \
        //    4  5 6  7
        vector<optional<int>> arr = {1, 2, 3, 4, 5, 6, 7};
        BinaryTree tree(arr);
        REQUIRE(tree.minDepth() == 3);
    }

    SECTION("Skewed left tree") {
        //      1
        //     /
        //    2
        //   /
        //  3
        vector<optional<int>> arr = {1, 2, nullopt, 3};
        BinaryTree tree(arr);
        REQUIRE(tree.minDepth() == 3);
    }

    SECTION("Min depth is not the leftmost path") {
        //        1
        //       / \
        //      2   3
        //     /     \
        //    4       5
        //             \
        //              6
        vector<optional<int>> arr = {1, 2, 3, 4, nullopt, nullopt, 5, nullopt, nullopt, 
                                    nullopt, nullopt, nullopt, nullopt, nullopt, 6};
        BinaryTree tree2(arr);
        REQUIRE(tree2.minDepth() == 3);
    }
}

TEST_CASE("Find min and max in BST and their product", "[task4]") {
    SECTION("Empty tree throws exception") {
        vector<optional<int>> arr = {};
        BinarySearchTree bst(arr);
        REQUIRE_THROWS_AS(bst.findMin(), const char*);
        REQUIRE_THROWS_AS(bst.findMax(), const char*);
    }

    SECTION("Single node BST") {
        vector<optional<int>> arr = {5};
        BinarySearchTree bst(arr);
        REQUIRE(bst.findMin() == 5);
        REQUIRE(bst.findMax() == 5);
    }

    SECTION("BST with left and right children") {
        //        8
        //       / \
        //      3   10
        //     / \    \
        //    1   6    14
        vector<optional<int>> arr = {8, 3, 10, 1, 6, nullopt, 14};
        BinarySearchTree bst(arr);
        REQUIRE(bst.findMin() == 1);
        REQUIRE(bst.findMax() == 14);
    }

    SECTION("All elements to the left") {
        //      10
        //     /
        //    5
        //   /
        //  2
        vector<optional<int>> arr = {10, 5, nullopt, 2};
        BinarySearchTree bst(arr);
        REQUIRE(bst.findMin() == 2);
        REQUIRE(bst.findMax() == 10);
    }

    SECTION("All elements to the right") {
        //    1
        //     \
        //      3
        //       \
        //        7
        vector<optional<int>> arr = {1, nullopt, 3, nullopt, nullopt, nullopt, 7};
        BinarySearchTree bst(arr);
        REQUIRE(bst.findMin() == 1);
        REQUIRE(bst.findMax() == 7);
    }
}

TEST_CASE("Compare two binary trees for equality", "[task5]") {
    SECTION("Both empty") {
        vector<optional<int>> arr1 = {};
        vector<optional<int>> arr2 = {};
        BinaryTree tree1(arr1);
        BinaryTree tree2(arr2);
        REQUIRE(isSameTree(tree1, tree2) == true);
    }

    SECTION("One empty, one not") {
        vector<optional<int>> arr1 = {};
        vector<optional<int>> arr2 = {1};
        BinaryTree tree1(arr1);
        BinaryTree tree2(arr2);
        REQUIRE(isSameTree(tree1, tree2) == false);
    }

    SECTION("Identical trees") {
        vector<optional<int>> arr = {1, 2, 3, 4, 5, 6, 7};
        BinaryTree tree1(arr);
        BinaryTree tree2(arr);
        REQUIRE(isSameTree(tree1, tree2) == true);
    }

    SECTION("Different structure") {
        vector<optional<int>> arr1 = {1, 2, 3};
        vector<optional<int>> arr2 = {1, 2, nullopt, 3};
        BinaryTree tree1(arr1);
        BinaryTree tree2(arr2);
        REQUIRE(isSameTree(tree1, tree2) == false);
    }

    SECTION("Same structure, different values") {
        vector<optional<int>> arr1 = {1, 2, 3};
        vector<optional<int>> arr2 = {1, 2, 4};
        BinaryTree tree1(arr1);
        BinaryTree tree2(arr2);
        REQUIRE(isSameTree(tree1, tree2) == false);
    }

    SECTION("Complex identical trees with nulls") {
        vector<optional<int>> arr = {5, 3, 8, nullopt, 4, 7, nullopt};
        BinaryTree tree1(arr);
        BinaryTree tree2(arr);
        REQUIRE(isSameTree(tree1, tree2) == true);
    }
}