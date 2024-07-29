#include "TreeNode.h"
#include "MyParser.h"
#include <string>
#include <iostream>
#include <vector>
#include "AVLTree.h"
TreeNode* root;

bool AVLTree::Insert(string name, int id, vector<string>& ingredients, int ingredientNum) {

//        if(!MyParser::isValidEntry(name, id_str))     // Could be used for future parsing of recipe nodes
//            return false;
//        MyParser::CleanName(name);
//        int id = stoi (id_str);

    if (SearchForIDRecursive(id, root, false)) //If Node already exists
        return false;

    root = InsertRecursive(name, id, root, ingredients, ingredientNum);       //Insertion
    return true;

}

bool AVLTree::Search(string target){
    if(MyParser::isNumber(target))          //Authentification to avoid crash
        return SearchID(stoi(target));

    else {
        MyParser::CleanName(target);            //Removes quotations
        return SearchName(target);
    }

}
bool AVLTree::SearchID(int id) {
    if (SearchForIDRecursive(id, root))      //If found in tree
        return true;
    else
        return false;

}
bool AVLTree::SearchName(const std::string& name) {
    if (SearchForNameRecursive(name, root))        //If found in tree
        return true;
    else
        return false;
}




void AVLTree::PrintNames(vector<string>& names){
    for(int i = 0; i < names.size(); i++){
        if(i == names.size() - 1) cout << names[i] << endl; //If last element (no comma)

        else cout << names[i] << ", ";
    }
}
void AVLTree::InOrderNames(TreeNode* node, vector<string>& names) {
    if (node == nullptr) return;

    InOrderNames(node->left, names);
    names.push_back(node->name);
    InOrderNames(node->right, names);
}

bool AVLTree::SearchForNameRecursive(const std::string& name, TreeNode* node, bool shouldDisplay) {
    if (node == nullptr) return false;

    bool wasFound = false;      //Used to avoid returning on first match. Prints all names

    if (node->name == name) {
        if (shouldDisplay) std::cout << node->id << std::endl;
        wasFound = true;
    }

    bool leftFound = SearchForNameRecursive(name, node->left, shouldDisplay);
    bool rightFound = SearchForNameRecursive(name, node->right, shouldDisplay);

    return wasFound || leftFound || rightFound;
}
bool AVLTree::SearchForIDRecursive(int id, TreeNode* node, bool shouldDisplay) {

    if (node == nullptr) return false;
    if (node->id == id){
        //if(shouldDisplay) cout << node->name << endl;
        return true;
    }
    if (node->id > id) return SearchForIDRecursive(id, node->left, shouldDisplay);

    if (node->id < id) return SearchForIDRecursive(id, node->right, shouldDisplay);

    return false;
}

TreeNode* AVLTree::InsertRecursive(string& name, int ID, TreeNode* node, vector<string>& ingredients, int ingredientNum) {
    if (node == nullptr) {         //New root created
        return new TreeNode(name, ID, ingredients, ingredientNum);
    }

    if (ID < node->id)
        node->left = InsertRecursive(name, ID, node->left, ingredients, ingredientNum);
    else
        node->right = InsertRecursive(name, ID, node->right, ingredients, ingredientNum);

    UpdateHeightAndBalance(node);
    return Rebalance(node);
}

TreeNode* AVLTree::Rebalance(TreeNode* node) {
    if (node->IsImbalancedRight()) {
        if (node->right->IsLeftHeavy()) {

            node->right = RotateRight(node->right);
            return RotateLeft(node);

        }
        else
            return RotateLeft(node);

    }
    if (node->IsImbalancedLeft()) {
        if (node->left->IsRightHeavy()) {

            node->left = RotateLeft(node->left);
            return RotateRight(node);

        }
        else
            return RotateRight(node);

    }
    return node;
}
TreeNode* AVLTree::RotateLeft(TreeNode* node) {
    TreeNode* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;

    UpdateHeightAndBalance(node);
    UpdateHeightAndBalance(newRoot);

    return newRoot;
}
TreeNode* AVLTree::RotateRight(TreeNode* node) {
    TreeNode* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;

    UpdateHeightAndBalance(node);
    UpdateHeightAndBalance(newRoot);

    return newRoot;
}

void AVLTree::UpdateHeightAndBalance(TreeNode* node) {
    if (node == nullptr) return;
    node->UpdateHeight();
    node->UpdateBalance();
}
