//
// Created by Administrator on 6/13/2024.
//

#ifndef AVLPROJECT_TREENODE_H
#define AVLPROJECT_TREENODE_H

#include <string>
#include <vector>

class TreeNode{

public:
    std::string name;
    std::vector<std::string> ingredients;
    int num_ingredients;
    int id;
    TreeNode* right;
    TreeNode* left;
    int height;
    int balance;

    TreeNode(std::string name, int id, std::vector<std::string> ingredients, int ingredientsNum){
        this->name = name;
        this->id = id;
        this->ingredients = ingredients;
        this->num_ingredients = ingredientsNum;
        right = nullptr;
        left = nullptr;
    }

    int NumOfChildren();

    bool IsImbalancedRight();
    bool IsImbalancedLeft();
    void UpdateBalance();

    bool IsLeftHeavy();
    bool IsRightHeavy();

    void UpdateHeight();
    void PrintDetails();

    TreeNode* GetInOrderSuccessor();

private:
    TreeNode* GetInOrderSuccessorRecursive(TreeNode* node);
    int GetBalanceRecursive (TreeNode* node);
    int GetHeightRecursive(TreeNode* node);

};
#endif //AVLPROJECT_TREENODE_H
