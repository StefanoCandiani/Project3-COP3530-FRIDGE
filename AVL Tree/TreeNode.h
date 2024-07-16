//
// Created by Administrator on 6/13/2024.
//

#ifndef AVLPROJECT_TREENODE_H
#define AVLPROJECT_TREENODE_H

#include <string>

using namespace std;
class TreeNode{

public:
    string name;
    int id;
    TreeNode* right;
    TreeNode* left;
    int height;
    int balance;

    TreeNode(string name, int id):name(name), id(id), right(nullptr), left(nullptr), height(1), balance(0){}

    int NumOfChildren(){
       int sum = 0;
       if(right != nullptr) sum++;
       if(left != nullptr) sum++;
       return sum;
    }


    bool IsImbalancedRight(){
        return balance < -1;
    }
    bool IsImbalancedLeft(){
        return balance > 1;
    }
    void UpdateBalance(){
        this->balance = GetBalanceRecursive(this);
    }


    bool IsLeftHeavy(){
        return balance > 0;
    }
    bool IsRightHeavy(){
        return balance < 0;
    }


    void UpdateHeight(){
        this->height = GetHeightRecursive(this);
    }

    void PrintDetails(){
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Height: " << height << endl;
        cout << "Balance: " << balance << endl << endl;
    }

    TreeNode* GetInOrderSuccessor(){
        return GetInOrderSuccessorRecursive(this->right);
    }


private:
    TreeNode* GetInOrderSuccessorRecursive(TreeNode* node){
        if(node->left == nullptr){
            return node;
        }
        else return GetInOrderSuccessorRecursive(node->left);
    }
    int GetBalanceRecursive (TreeNode* node){
        if(node == nullptr) return 0;
        int right = 1 + GetHeightRecursive(node->right);
        int left = 1 + GetHeightRecursive(node->left);
        return left - right;
    }
    int GetHeightRecursive(TreeNode* node){
        if(node == nullptr) return 0;
        int right = 1 + GetHeightRecursive(node->right);
        int left = 1 + GetHeightRecursive(node->left);
        return max(right, left);
    }

};
#endif //AVLPROJECT_TREENODE_H
