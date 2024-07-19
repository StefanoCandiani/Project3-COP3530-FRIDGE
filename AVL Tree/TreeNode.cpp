//
// Created by Administrator on 6/13/2024.
//

#include <string>
#include "TreeNode.h"
#include <iostream>

    int TreeNode::NumOfChildren(){
        int sum = 0;
        if(right != nullptr) sum++;
        if(left != nullptr) sum++;
        return sum;
    }

    bool TreeNode::IsImbalancedRight(){
        return balance < -1;
    }
    bool TreeNode::IsImbalancedLeft(){
        return balance > 1;
    }
    void TreeNode::UpdateBalance(){
        this->balance = GetBalanceRecursive(this);
    }

    bool TreeNode::IsLeftHeavy(){
        return balance > 0;
    }
    bool TreeNode::IsRightHeavy(){
        return balance < 0;
    }


    void TreeNode::UpdateHeight(){
        this->height = GetHeightRecursive(this);
    }

    void TreeNode::PrintDetails(){
        std::cout << "Name: " << name << std::endl;
        std::cout << "ID: " << id << std::endl;
        std::cout << "Height: " << height << std::endl;
        std::cout << "Balance: " << balance << std::endl << std::endl;
    }

    TreeNode* TreeNode::GetInOrderSuccessor(){
        return GetInOrderSuccessorRecursive(this->right);
    }


    TreeNode* TreeNode::GetInOrderSuccessorRecursive(TreeNode* node){
        if(node->left == nullptr){
            return node;
        }
        else return GetInOrderSuccessorRecursive(node->left);
    }
    int TreeNode::GetBalanceRecursive (TreeNode* node){
        if(node == nullptr) return 0;
        int right = 1 + GetHeightRecursive(node->right);
        int left = 1 + GetHeightRecursive(node->left);
        return left - right;
    }
    int TreeNode::GetHeightRecursive(TreeNode* node){
        if(node == nullptr) return 0;
        int right = 1 + GetHeightRecursive(node->right);
        int left = 1 + GetHeightRecursive(node->left);
        return std::max(right, left);
    }
