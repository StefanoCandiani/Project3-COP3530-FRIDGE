//
// Created by Tavienne Millner on 7/20/24.
//

#ifndef INPUT_TESTING_AVLTREE_H
#define INPUT_TESTING_AVLTREE_H

#include <string>
#include <vector>

class AVLTree {
public:
    struct TreeNode {
        // Data
        std::string recipeName;
        int recipeID;
        std::vector<std::string> ingredients;
        int numIngredients;
        int height;

        TreeNode* left = nullptr;
        TreeNode* right = nullptr;

        // Parametrized constructor
        TreeNode(const std::string& recipeName, int recipeID, const std::vector<std::string>& ingredients, int numIngredients) : recipeName(recipeName), recipeID(recipeID), ingredients(ingredients), numIngredients(numIngredients) {}
    };

    AVLTree() {
        size = 0;
        root = nullptr;
    }

    ~AVLTree() {
        root = deleteTree(root);
    }

    void insert(const std::string& recipeName, int recipeID, const std::vector<std::string>& ingredients, int numIngredients);
    AVLTree::TreeNode* search(std::vector<std::string>& userIngredients);
    int getSize();

private:
    TreeNode* root;
    int size;

    AVLTree::TreeNode* helperInsert(AVLTree::TreeNode* helpRoot, const std::string& recipeName, int recipeID, const std::vector<std::string>& ingredients, int numIngredients);
    AVLTree::TreeNode* helperSearch(AVLTree::TreeNode* helpRoot, std::vector<std::string>& userIngredients);

    // Utilities needed by insert
    AVLTree::TreeNode* rotateLeft(AVLTree::TreeNode* node);
    AVLTree::TreeNode* rotateRight(AVLTree::TreeNode* node);
    AVLTree::TreeNode* rotateLeftRight(AVLTree::TreeNode* node);
    AVLTree::TreeNode* rotateRightLeft(AVLTree::TreeNode* node);
    int balance(TreeNode* helpRoot);

    // Needed to delete tree
    AVLTree::TreeNode* deleteTree(AVLTree::TreeNode* helpRoot);

};


#endif //INPUT_TESTING_AVLTREE_H
