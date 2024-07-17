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

    bool Insert(string name, int id, vector<string>& ingredients, int ingredient_num) {

//        if(!MyParser::isValidEntry(name, id_str))     // Could be used for future parsing of recipe nodes
//            return false;
//        MyParser::CleanName(name);
//        int id = stoi (id_str);

        if (SearchForIDRecursive(id, root, false)) //If Node already exists
            return false;

        root = InsertRecursive(name, id, root, ingredients, ingredient_num);       //Insertion
        return true;

    }

    vector<string> GetInOrder(){
        vector<string> names;
        InOrderNames(root, names);
        return names;
    }
    vector<string> GetPostOrder(){
        vector<string> names;
        PostOrderNames(root, names);
        return names;
    }
    vector<string> GetPreOrder(){
        vector<string> names;
        PreOrderNames(root, names);
        return names;
    }


    void PrintInOrder() {
        vector<string> names;
        InOrderNames(root, names);
        PrintNames(names);
    }
    void PrintPostOrder() {
        vector<string> names;
        PostOrderNames(root, names);
        PrintNames(names);
    }
    void PrintPreOrder() {
        vector<string> names;
        PreOrderNames(root, names);
        PrintNames(names);
    }
    void PrintLevelCount() {
        if (root == nullptr)
            cout << "0" << std::endl;
        else
            cout << root->height << std::endl;
    }


    bool Search(string target){
        if(MyParser::isNumber(target))          //Authentification to avoid crash
            return SearchID(stoi(target));

        else {
            MyParser::CleanName(target);            //Removes quotations
            return SearchName(target);
        }

    }
    bool SearchID(int id) {
        if (SearchForIDRecursive(id, root))      //If found in tree
            return true;
        else
            return false;

    }
    bool SearchName(const std::string& name) {
        if (SearchForNameRecursive(name, root))        //If found in tree
            return true;
        else
            return false;
    }


    bool RemoveID(string id_str) {
        if(!MyParser::IsValidID(stoi(id_str))) return false;
        if(!SearchForIDRecursive(stoi(id_str), root, false)) return false;   //If Node is not in Tree

        bool isFound;
        root = RemoveIDRecursive(stoi(id_str), root, isFound);                       //Returns balanced tree by root

        if (isFound)
            return true;
        else
            return false;

    }
    bool removeInOrder(string target) {
        if (!MyParser::isNumber(target))
            return false;

        int count = 0;                  //Used to keep track of how many iterations have occured
        bool wasRemoved;
        root = RemoveInOrderRecursive(stoi(target), count, root, wasRemoved);   //Returns balanced tree root
        if (wasRemoved)
            return true;
        else
            return false;

    }

private:

    void PrintNames(vector<string>& names){
        for(int i = 0; i < names.size(); i++){
            if(i == names.size() - 1) cout << names[i] << endl; //If last element (no comma)

            else cout << names[i] << ", ";
        }
    }
    void InOrderNames(TreeNode* node, vector<string>& names) {
        if (node == nullptr) return;

        InOrderNames(node->left, names);
        names.push_back(node->name);
        InOrderNames(node->right, names);
    }
    void PreOrderNames(TreeNode* node, vector<string>& names) {
        if (node == nullptr) return;

        names.push_back(node->name);
        PreOrderNames(node->left, names);
        PreOrderNames(node->right, names);
    }
    void PostOrderNames(TreeNode* node, vector<string>& names) {
        if (node == nullptr) return;

        PostOrderNames(node->left, names);
        PostOrderNames(node->right, names);
        names.push_back(node->name);
    }


    TreeNode* RemoveInOrderRecursive(int target, int& count, TreeNode* node, bool& success) {
        if (node == nullptr) {  //Not Found in current path
            success = false;
            return nullptr;
        }

        node->left = RemoveInOrderRecursive(target, count, node->left, success); //Search all left possibilities

        if (success) {                                                               //If found on left subtree update and rebalance nodes
            UpdateHeightAndBalance(node);
            return Rebalance(node);
        }

        if (count == target) {                                                       //If the count of iterations matches desired index
            success = true;
            return RemoveNode(node);
        }
        else count++;

        node->right = RemoveInOrderRecursive(target, count, node->right, success);///If found on left subtree update and rebalance nodes
        if(success){
            UpdateHeightAndBalance(node);
        }
        return Rebalance(node);
    }
    TreeNode* RemoveIDRecursive(int id, TreeNode* node, bool& success) {
        if (node == nullptr) {      //If not found
            success = false;
            return nullptr;
        }

        if (node->id == id) {       //If found
            success = true;
            return RemoveNode(node);
        }

        if (node->id > id)          //If current ID is higher than desired ID go to left
            node->left = RemoveIDRecursive(id, node->left, success);
        else                        //If current ID is lower than desired ID go to right
            node->right = RemoveIDRecursive(id, node->right, success);


        UpdateHeightAndBalance(node);   //Update height and balance of all nodes at the end of each recursive call
        return Rebalance(node);

    }
    TreeNode* RemoveNode(TreeNode* node) {
        if (node->NumOfChildren() == 0) {           //Node has 0 children
            delete node;
            return nullptr;
        }
        else if (node->NumOfChildren() == 1) {      //Node has 1 children
            TreeNode* child = (node->left != nullptr) ? node->left : node->right;
            delete node;
            return child;
        }
        else {                                      //Node has 2 children
            if (node->right->left != nullptr) {     //If node has an in order successor smaller than its bigger neighbor
                TreeNode* parent = node;
                TreeNode* inOrderSuccessor = node->right;

                while (inOrderSuccessor->left != nullptr) { //Continue all the way left
                    parent = inOrderSuccessor;
                    inOrderSuccessor = inOrderSuccessor->left;
                }

                if (parent != node) {
                    parent->left = inOrderSuccessor->right;
                    inOrderSuccessor->right = node->right;
                }

                inOrderSuccessor->left = node->left;

                delete node;
                return inOrderSuccessor;
            }
            else {                                //If neighbors node does not have a smaller child
                TreeNode* newRoot = node->right;
                newRoot->left = node->left;
                delete node;
                return newRoot;
            }
        }
    }


    bool SearchForNameRecursive(const std::string& name, TreeNode* node, bool shouldDisplay = true) {
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
    bool SearchForIDRecursive(int id, TreeNode* node, bool shouldDisplay = true) {

        if (node == nullptr) return false;
        if (node->id == id){
            //if(shouldDisplay) cout << node->name << endl;
            return true;
        }
        if (node->id > id) return SearchForIDRecursive(id, node->left, shouldDisplay);

        if (node->id < id) return SearchForIDRecursive(id, node->right, shouldDisplay);

        return false;
    }
    
    TreeNode* InsertRecursive(string& name, int ID, TreeNode* node, vector<string>& ingredients, int ingredient_num) {
        if (node == nullptr) {         //New root created
            return new TreeNode(name, ID, ingredients, ingredient_num);
        }

        if (ID < node->id)
            node->left = InsertRecursive(name, ID, node->left, ingredients, ingredient_num);
         else
            node->right = InsertRecursive(name, ID, node->right, ingredients, ingredient_num);

        UpdateHeightAndBalance(node);
        return Rebalance(node);
    }
    
    TreeNode* Rebalance(TreeNode* node) {
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
    TreeNode* RotateLeft(TreeNode* node) {
        TreeNode* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;

        UpdateHeightAndBalance(node);
        UpdateHeightAndBalance(newRoot);

        return newRoot;
    }
    TreeNode* RotateRight(TreeNode* node) {
        TreeNode* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;

        UpdateHeightAndBalance(node);
        UpdateHeightAndBalance(newRoot);

        return newRoot;
    }
    
    void UpdateHeightAndBalance(TreeNode* node) {
        if (node == nullptr) return;
        node->UpdateHeight();
        node->UpdateBalance();
    }

};

#endif //AVLPROJECT_AVLTREE_H
