#include "AVLTree.h"

void AVLTree::insert(const std::string& recipeName, int recipeID, const std::vector<std::string> &ingredients, int numIngredients) {
    this->root = helperInsert(this->root, recipeName, recipeID, ingredients, numIngredients);
    size++;
}

AVLTree::TreeNode* AVLTree::search(std::vector<std::string>& userIngredients) {
    AVLTree::TreeNode* found = helperSearch(root, userIngredients);
    return found;
}

AVLTree::TreeNode* AVLTree::helperInsert(AVLTree::TreeNode* helpRoot, const std::string &recipeName, int recipeID, const std::vector<std::string>& ingredients, int numIngredients) {
    // Standard BST insert logic
    if (helpRoot == nullptr)
        return new AVLTree::TreeNode(recipeName, recipeID, ingredients, numIngredients);
    else if (ingredients < helpRoot->ingredients)
        helpRoot->left = helperInsert(helpRoot->left, recipeName, recipeID, ingredients, numIngredients);
    else if (ingredients > helpRoot->ingredients)
        helpRoot->right = helperInsert(helpRoot->right, recipeName, recipeID, ingredients, numIngredients);

    // Update height and get the balance factor
    helpRoot->height = 1 + std::max(helpRoot->left != nullptr ? helpRoot->left->height : 0, helpRoot->right != nullptr ? helpRoot->right->height : 0);
    int balanceFactor = balance(helpRoot);

    // Logic for when to perform rotations taken from Slides (4 - Balanced Trees PDF page 28)
    if (balanceFactor < -1) {
        int balanceRight = balance(helpRoot->right);
        if (balanceRight >= 1) {
            helpRoot = rotateRightLeft(helpRoot);
            helpRoot->height = 1 + std::max(helpRoot->left != nullptr ? helpRoot->left->height : 0, helpRoot->right != nullptr ? helpRoot->right->height : 0);
        }
        else {
            helpRoot = rotateLeft(helpRoot);
            helpRoot->height = 1 + std::max(helpRoot->left != nullptr ? helpRoot->left->height : 0, helpRoot->right != nullptr ? helpRoot->right->height : 0);
        }
    }
    else if (balanceFactor > 1) {
        int balanceLeft = balance(helpRoot->left);
        if (balanceLeft <= -1) {
            helpRoot = rotateLeftRight(helpRoot);
            helpRoot->height = 1 + std::max(helpRoot->left != nullptr ? helpRoot->left->height : 0, helpRoot->right != nullptr ? helpRoot->right->height : 0);
        }
        else {
            helpRoot = rotateRight(helpRoot);
            helpRoot->height = 1 + std::max(helpRoot->left != nullptr ? helpRoot->left->height : 0, helpRoot->right != nullptr ? helpRoot->right->height : 0);
        }
    }

    return helpRoot;
}

AVLTree::TreeNode* AVLTree::helperSearch(AVLTree::TreeNode* helpRoot, std::vector<std::string>& userIngredients) {
    if (helpRoot == nullptr)
        return helpRoot;
    if (helpRoot->ingredients == userIngredients)
        return helpRoot;
    else if (userIngredients < helpRoot->ingredients)
        return helperSearch(helpRoot->left, userIngredients);
    else if (userIngredients > helpRoot->ingredients)
        return helperSearch(helpRoot->right, userIngredients);
}

// Taken from Stepik 5.1 Step 1
AVLTree::TreeNode* AVLTree::rotateLeft(AVLTree::TreeNode* node) {
    AVLTree::TreeNode* newParent = node->right;
    node->right = newParent->left;
    newParent->left = node;

    // Update heights
    newParent->height = 1 + std::max(newParent->left != nullptr ? newParent->left->height : 0, newParent->right != nullptr ? newParent->right->height : 0);
    node->height = 1 + std::max(node->left != nullptr ? node->left->height : 0, node->right != nullptr ? node->right->height : 0);

    return newParent;
}

// Taken from Stepik 5.1 Step 1
AVLTree::TreeNode* AVLTree::rotateRight(AVLTree::TreeNode* node) {
    AVLTree::TreeNode* newParent = node->left;
    node->left = newParent->right;
    newParent->right = node;

    // Update heights
    newParent->height = 1 + std::max(newParent->left != nullptr ? newParent->left->height : 0, newParent->right != nullptr ? newParent->right->height : 0);
    node->height = 1 + std::max(node->left != nullptr ? node->left->height : 0, node->right != nullptr ? node->right->height : 0);

    return newParent;
}

// Taken from Stepik 5.1 Step 1
AVLTree::TreeNode* AVLTree::rotateLeftRight(AVLTree::TreeNode* node) {
    node->left = rotateLeft(node->left);
    node = rotateRight(node);

    // Update heights
    node->height = 1 + std::max(node->left != nullptr ? node->left->height : 0, node->right != nullptr ? node->right->height : 0);

    return node;
}

// Taken from Stepik 5.1 Step 3
AVLTree::TreeNode* AVLTree::rotateRightLeft(AVLTree::TreeNode* node) {
    node->right = rotateRight(node->right);
    node = rotateLeft(node);

    // Update heights
    node->height = 1 + std::max(node->left != nullptr ? node->left->height : 0, node->right != nullptr ? node->right->height : 0);

    return node;
}

// Gets the balance factor of a node
int AVLTree::balance(AVLTree::TreeNode* helpRoot) {
    if (helpRoot == nullptr)
        return 0;
    return ((helpRoot->left == nullptr ? 0 : helpRoot->left->height) - (helpRoot->right == nullptr ? 0 : helpRoot->right->height));
}

// Deallocates the nodes allocated by insert with a postorder traversal
AVLTree::TreeNode* AVLTree::deleteTree(AVLTree::TreeNode* helpRoot) {
    if (helpRoot == nullptr)
        return helpRoot;

    helpRoot->left = deleteTree(helpRoot->left);
    helpRoot->right = deleteTree(helpRoot->right);
    delete helpRoot;
    helpRoot = nullptr;
    return helpRoot;
}

int AVLTree::getSize() {
    return size;
}
