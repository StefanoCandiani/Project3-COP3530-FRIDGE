#ifndef AVLPROJECT_AVLTREE_H
#define AVLPROJECT_AVLTREE_H

#include "TreeNode.h"
#include "MyParser.h"
#include <string>
#include <iostream>
#include <vector>


class AVLTree {
public:
    TreeNode* root;

    AVLTree() : root(nullptr) {}                        //Constructor

    bool Insert(string name, int id, vector<string>& ingredients, int ingredientNum);

    bool Search(string target);
    bool SearchID(int id) ;
    bool SearchName(const std::string& name) ;


private:

    void PrintNames(vector<string>& names);
    void InOrderNames(TreeNode* node, vector<string>& names);

    bool SearchForNameRecursive(const std::string& name, TreeNode* node, bool shouldDisplay = true);
    bool SearchForIDRecursive(int id, TreeNode* node, bool shouldDisplay = true);
    
    TreeNode* InsertRecursive(string& name, int ID, TreeNode* node, vector<string>& ingredients, int ingredientNum);
    
    TreeNode* Rebalance(TreeNode* node);
    TreeNode* RotateLeft(TreeNode* node);
    TreeNode* RotateRight(TreeNode* node);
    
    void UpdateHeightAndBalance(TreeNode* node);

};

#endif //AVLPROJECT_AVLTREE_H
