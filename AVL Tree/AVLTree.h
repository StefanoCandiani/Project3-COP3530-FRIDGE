//
// Created by Tavienne Millner on 7/20/24.
//

#ifndef PROJECT3_COP3530_FRIDGE_AVLTREE_H
#define PROJECT3_COP3530_FRIDGE_AVLTREE_H

#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <queue>

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
    AVLTree::TreeNode* search(const std::vector<std::string>& userIngredients);
    std::pair<std::priority_queue<std::pair<float, AVLTree::TreeNode*>>, std::chrono::duration<double>> bestSearch(const std::vector<std::string>& userIngredients);
    void traverse();
    int getSize();

private:
    TreeNode* root;
    int size;

    AVLTree::TreeNode* helperInsert(AVLTree::TreeNode* helpRoot, const std::string& recipeName, int recipeID, const std::vector<std::string>& ingredients, int numIngredients);
    AVLTree::TreeNode* helperSearch(AVLTree::TreeNode* helpRoot, const std::vector<std::string>& userIngredients);
    void helperBestSearch(AVLTree::TreeNode* helpRoot, const std::vector<std::string>& userIngredients,
                                                                                        std::priority_queue<std::pair<float, AVLTree::TreeNode*>>& pq);
    void helperTraverse(AVLTree::TreeNode* helpRoot);

    // Utilities needed by insert
    AVLTree::TreeNode* rotateLeft(AVLTree::TreeNode* node);
    AVLTree::TreeNode* rotateRight(AVLTree::TreeNode* node);
    AVLTree::TreeNode* rotateLeftRight(AVLTree::TreeNode* node);
    AVLTree::TreeNode* rotateRightLeft(AVLTree::TreeNode* node);
    int balance(TreeNode* helpRoot);

    // Needed to delete tree
    AVLTree::TreeNode* deleteTree(AVLTree::TreeNode* helpRoot);

};

#endif //PROJECT3_COP3530_FRIDGE_AVLTREE_H
