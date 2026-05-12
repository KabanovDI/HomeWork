#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "algorithms.hpp"
#include <vector>
#include <optional>


using namespace std;

TEST_CASE("BinaryTree::isComplete()", "[task1]") {
    SECTION("Empty tree is complete") {
        vector<optional<int>> arr = {};
        BinaryTree tree(arr);
        REQUIRE(tree.isComplete() == true);
    }
    
    SECTION("Single node is complete") {
        vector<optional<int>> arr = {1};
        BinaryTree tree(arr);
        REQUIRE(tree.isComplete() == true);
    }
    
    SECTION("Perfect binary tree is complete") {
        vector<optional<int>> arr = {1, 2, 3, 4, 5, 6, 7};
        BinaryTree tree(arr);
        REQUIRE(tree.isComplete() == true);
    }
    
    SECTION("Complete but not perfect tree") {
        vector<optional<int>> arr = {1, 2, 3, 4, 5, 6};
        BinaryTree tree(arr);
        REQUIRE(tree.isComplete() == true);
    }
    
    SECTION("Incomplete tree - missing left child") {
        vector<optional<int>> arr = {1, nullopt, 3, nullopt, nullopt, nullopt, 7};
        BinaryTree tree(arr);
        REQUIRE(tree.isComplete() == false);
    }
    
    SECTION("Incomplete tree - gap in last level") {
        vector<optional<int>> arr = {1, 2, 3, 4, nullopt, 6, 7};
        BinaryTree tree(arr);
        REQUIRE(tree.isComplete() == false);
    }
    
    SECTION("Incomplete tree - extra level after gap") {
        vector<optional<int>> arr = {1, 2, 3, 4, 5, 6, nullopt, 7};
        BinaryTree tree(arr);
        REQUIRE(tree.isComplete() == false);
    }
}

TEST_CASE("BinaryTree::mirror()", "[task6]") {
    SECTION("Mirror empty tree") {
        vector<optional<int>> arr = {};
        BinaryTree tree(arr);
        tree.mirror();
        REQUIRE(tree.getRoot() == nullptr);
    }
    
    SECTION("Mirror single node") {
        vector<optional<int>> arr = {1};
        BinaryTree tree(arr);
        tree.mirror();
        REQUIRE(tree.getRoot()->val == 1);
        REQUIRE(tree.getRoot()->left == nullptr);
        REQUIRE(tree.getRoot()->right == nullptr);
    }
    
    SECTION("Mirror perfect tree") {
        // Original:   1         Mirror:    1
        //            / \                  / \
        //           2   3                3   2
        //          / \ / \              / \ / \
        //         4  5 6  7            7  6 5  4
        vector<optional<int>> arr = {1, 2, 3, 4, 5, 6, 7};
        BinaryTree tree(arr);
        tree.mirror();
        
        TreeNode* root = tree.getRoot();
        REQUIRE(root->val == 1);
        REQUIRE(root->left->val == 3);
        REQUIRE(root->right->val == 2);
        REQUIRE(root->left->left->val == 7);
        REQUIRE(root->left->right->val == 6);
        REQUIRE(root->right->left->val == 5);
        REQUIRE(root->right->right->val == 4);
    }
    
    SECTION("Double mirror returns original") {
        vector<optional<int>> arr = {1, 2, 3, 4, 5, 6, 7};
        BinaryTree tree1(arr);
        BinaryTree tree2(arr);
        
        tree1.mirror();
        tree1.mirror();
        
        REQUIRE(compareTrees(tree1, tree2) == true);
    }
    
    SECTION("Mirror asymmetric tree") {
        vector<optional<int>> arr = {1, 2, 3, 4, nullopt, nullopt, 7};
        BinaryTree tree(arr);
        tree.mirror();
        
        TreeNode* root = tree.getRoot();
        REQUIRE(root->val == 1);
        REQUIRE(root->left->val == 3);
        REQUIRE(root->right->val == 2);
        REQUIRE(root->left->left->val == 7);
        REQUIRE(root->right->right->val == 4);
    }
}

TEST_CASE("mergeKSortedArrays", "[task2]") {
    SECTION("Empty input") {
        vector<vector<int>> arrays = {};
        vector<int> result = mergeKSortedArrays(arrays);
        REQUIRE(result.empty());
    }
    
    SECTION("Single array") {
        vector<vector<int>> arrays = {{1, 2, 3, 4, 5}};
        vector<int> expected = {1, 2, 3, 4, 5};
        vector<int> result = mergeKSortedArrays(arrays);
        REQUIRE(result == expected);
    }
    
    SECTION("Multiple arrays same size") {
        vector<vector<int>> arrays = {
            {1, 4, 7},
            {2, 5, 8},
            {3, 6, 9}
        };
        vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        vector<int> result = mergeKSortedArrays(arrays);
        REQUIRE(result == expected);
    }
    
    SECTION("Arrays of different sizes") {
        vector<vector<int>> arrays = {
            {1, 10},
            {2, 3, 4},
            {5},
            {6, 7, 8, 9}
        };
        vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        vector<int> result = mergeKSortedArrays(arrays);
        REQUIRE(result == expected);
    }
    
    SECTION("Arrays with empty arrays") {
        vector<vector<int>> arrays = {
            {},
            {1, 2, 3},
            {},
            {4, 5, 6},
            {}
        };
        vector<int> expected = {1, 2, 3, 4, 5, 6};
        vector<int> result = mergeKSortedArrays(arrays);
        REQUIRE(result == expected);
    }
    
    SECTION("Duplicate values") {
        vector<vector<int>> arrays = {
            {1, 1, 2},
            {1, 2, 2},
            {1, 1, 1}
        };
        vector<int> expected = {1, 1, 1, 1, 1, 1, 2, 2, 2};
        vector<int> result = mergeKSortedArrays(arrays);
        REQUIRE(result == expected);
    }
    
    SECTION("Negative numbers") {
        vector<vector<int>> arrays = {
            {-5, -3, -1},
            {-4, -2, 0},
            {-6, 2, 4}
        };
        vector<int> expected = {-6, -5, -4, -3, -2, -1, 0, 2, 4};
        vector<int> result = mergeKSortedArrays(arrays);
        REQUIRE(result == expected);
    }
}

TEST_CASE("findKthElement (array))", "[task3]") {
    SECTION("K-th smallest") {
        vector<int> nums = {3, 2, 1, 5, 6, 4};
        
        REQUIRE(findKthElement(nums, 1, Mode::SMALLEST) == 1);
        REQUIRE(findKthElement(nums, 2, Mode::SMALLEST) == 2);
        REQUIRE(findKthElement(nums, 3, Mode::SMALLEST) == 3);
        REQUIRE(findKthElement(nums, 4, Mode::SMALLEST) == 4);
        REQUIRE(findKthElement(nums, 5, Mode::SMALLEST) == 5);
        REQUIRE(findKthElement(nums, 6, Mode::SMALLEST) == 6);
    }
    
    SECTION("K-th largest") {
        vector<int> nums = {3, 2, 1, 5, 6, 4};
        
        REQUIRE(findKthElement(nums, 1, Mode::LARGEST) == 6);
        REQUIRE(findKthElement(nums, 2, Mode::LARGEST) == 5);
        REQUIRE(findKthElement(nums, 3, Mode::LARGEST) == 4);
        REQUIRE(findKthElement(nums, 4, Mode::LARGEST) == 3);
        REQUIRE(findKthElement(nums, 5, Mode::LARGEST) == 2);
        REQUIRE(findKthElement(nums, 6, Mode::LARGEST) == 1);
    }
    
    SECTION("Duplicate elements") {
        vector<int> nums = {3, 3, 3, 2, 2, 1};
        
        REQUIRE(findKthElement(nums, 1, Mode::SMALLEST) == 1);
        REQUIRE(findKthElement(nums, 2, Mode::SMALLEST) == 2);
        REQUIRE(findKthElement(nums, 3, Mode::SMALLEST) == 2);
        REQUIRE(findKthElement(nums, 4, Mode::SMALLEST) == 3);
        
        REQUIRE(findKthElement(nums, 1, Mode::LARGEST) == 3);
        REQUIRE(findKthElement(nums, 2, Mode::LARGEST) == 3);
        REQUIRE(findKthElement(nums, 3, Mode::LARGEST) == 3);
        REQUIRE(findKthElement(nums, 4, Mode::LARGEST) == 2);
    }
    
    SECTION("Single element array") {
        vector<int> nums = {42};
        
        REQUIRE(findKthElement(nums, 1, Mode::SMALLEST) == 42);
        REQUIRE(findKthElement(nums, 1, Mode::LARGEST) == 42);
    }
    
    SECTION("Invalid k") {
        vector<int> nums = {1, 2, 3};
        
        REQUIRE_THROWS_AS(findKthElement(nums, 0, Mode::SMALLEST), const char*);
        REQUIRE_THROWS_AS(findKthElement(nums, 4, Mode::SMALLEST), const char*);
        REQUIRE_THROWS_AS(findKthElement(nums, -1, Mode::LARGEST), const char*);
    }
}

TEST_CASE("BinarySearchTree::findKthElement", "[task4]") {
    SECTION("K-th smallest in BST") {
        vector<optional<int>> arr = {5, 3, 7, 2, 4, 6, 8};
        BinarySearchTree bst(arr);
        
        REQUIRE(bst.findKthElement(1, Mode::SMALLEST).value() == 2);
        REQUIRE(bst.findKthElement(2, Mode::SMALLEST).value() == 3);
        REQUIRE(bst.findKthElement(3, Mode::SMALLEST).value() == 4);
        REQUIRE(bst.findKthElement(4, Mode::SMALLEST).value() == 5);
        REQUIRE(bst.findKthElement(5, Mode::SMALLEST).value() == 6);
        REQUIRE(bst.findKthElement(6, Mode::SMALLEST).value() == 7);
        REQUIRE(bst.findKthElement(7, Mode::SMALLEST).value() == 8);
    }
    
    SECTION("K-th largest in BST") {
        vector<optional<int>> arr = {5, 3, 7, 2, 4, 6, 8};
        BinarySearchTree bst(arr);
        
        REQUIRE(bst.findKthElement(1, Mode::LARGEST).value() == 8);
        REQUIRE(bst.findKthElement(2, Mode::LARGEST).value() == 7);
        REQUIRE(bst.findKthElement(3, Mode::LARGEST).value() == 6);
        REQUIRE(bst.findKthElement(4, Mode::LARGEST).value() == 5);
        REQUIRE(bst.findKthElement(5, Mode::LARGEST).value() == 4);
        REQUIRE(bst.findKthElement(6, Mode::LARGEST).value() == 3);
        REQUIRE(bst.findKthElement(7, Mode::LARGEST).value() == 2);
    }
    
    SECTION("Unbalanced BST - left skewed") {
        vector<optional<int>> arr = {5, 3, nullopt, 2, 4};
        BinarySearchTree bst(arr);
        
        REQUIRE(bst.findKthElement(1, Mode::SMALLEST).value() == 2);
        REQUIRE(bst.findKthElement(2, Mode::SMALLEST).value() == 3);
        REQUIRE(bst.findKthElement(3, Mode::SMALLEST).value() == 4);
        REQUIRE(bst.findKthElement(4, Mode::SMALLEST).value() == 5);
    }
    
    SECTION("Unbalanced BST - right skewed") {
        vector<optional<int>> arr = {5, nullopt, 7, nullopt, nullopt, 6, 8};
        BinarySearchTree bst(arr);
        
        REQUIRE(bst.findKthElement(1, Mode::LARGEST).value() == 8);
        REQUIRE(bst.findKthElement(2, Mode::LARGEST).value() == 7);
        REQUIRE(bst.findKthElement(3, Mode::LARGEST).value() == 6);
        REQUIRE(bst.findKthElement(4, Mode::LARGEST).value() == 5);
    }
    
    SECTION("Single node BST") {
        vector<optional<int>> arr = {42};
        BinarySearchTree bst(arr);
        
        REQUIRE(bst.findKthElement(1, Mode::SMALLEST).value() == 42);
        REQUIRE(bst.findKthElement(1, Mode::LARGEST).value() == 42);
    }
    
    SECTION("Invalid k") {
        vector<int> nums = {1, 2, 3};
        
        REQUIRE_THROWS_AS(findKthElement(nums, 0, Mode::SMALLEST), const char*);
        REQUIRE_THROWS_AS(findKthElement(nums, 4, Mode::SMALLEST), const char*);
        REQUIRE_THROWS_AS(findKthElement(nums, -1, Mode::LARGEST), const char*);
    }

    SECTION("Empty tree") {
        vector<optional<int>> arr = {};
        BinarySearchTree bst(arr);
        
        REQUIRE_THROWS_AS(bst.findKthElement(1, Mode::SMALLEST), const char*);
    }
}

TEST_CASE("BinarySearchTree::calculateBalanceFactors", "[task5]") {
    SECTION("Balanced tree") {
        vector<optional<int>> arr = {5, 3, 7, 2, 4, 6, 8};
        BinarySearchTree bst(arr);
        bst.calculateBalanceFactors();
        
        TreeNode* root = bst.getRoot();
        REQUIRE(root->balance_factor == 0);
        REQUIRE(root->left->balance_factor == 0);
        REQUIRE(root->right->balance_factor == 0);
    }
    
    SECTION("Left skewed tree") {
        vector<optional<int>> arr = {5, 3, nullopt, 2, 4, nullopt, nullopt, 1};
        BinarySearchTree bst(arr);
        bst.calculateBalanceFactors();
        
        TreeNode* root = bst.getRoot();
        REQUIRE(root->balance_factor == -3);  // right height - left height
        REQUIRE(root->left->balance_factor == -1);
        REQUIRE(root->left->left->balance_factor == -1);
        REQUIRE(root->left->left->left->balance_factor == 0);
    }
    
    SECTION("Right skewed tree") {
        vector<optional<int>> arr = {5, nullopt, 7, nullopt, nullopt, 8, 9,
                                    nullopt, nullopt, nullopt, nullopt, nullopt, nullopt,
                                    nullopt, 10};
        BinarySearchTree bst(arr);
        bst.calculateBalanceFactors();
        
        TreeNode* root = bst.getRoot();
        REQUIRE(root->balance_factor == 3);
        REQUIRE(root->right->balance_factor == 1);
        REQUIRE(root->right->right->balance_factor == 1);
        REQUIRE(root->right->right->right->balance_factor == 0);
    }
    
    SECTION("Mixed balance factors") {
        vector<optional<int>> arr = {5, 3, 7, 2, nullopt, nullopt, 8};
        BinarySearchTree bst(arr);
        bst.calculateBalanceFactors();
        
        TreeNode* root = bst.getRoot();
        REQUIRE(root->balance_factor == 0);
        REQUIRE(root->left->balance_factor == -1);
        REQUIRE(root->right->balance_factor == 1);
        REQUIRE(root->left->left->balance_factor == 0);
        REQUIRE(root->right->right->balance_factor == 0);
    }
    
    SECTION("Empty tree") {
        vector<optional<int>> arr = {};
        BinarySearchTree bst(arr);
        bst.calculateBalanceFactors();
        
        REQUIRE(bst.getRoot() == nullptr);
    }
    
    SECTION("Single node") {
        vector<optional<int>> arr = {42};
        BinarySearchTree bst(arr);
        bst.calculateBalanceFactors();
        
        REQUIRE(bst.getRoot()->balance_factor == 0);
    }
}