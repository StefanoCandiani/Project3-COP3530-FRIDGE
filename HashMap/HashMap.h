//
// Created by Stefano Candiani on 7/27/24.
//

#ifndef PROJECT3_COP3530_FRIDGE_HASHMAP_H
#define PROJECT3_COP3530_FRIDGE_HASHMAP_H

#include <iostream>
#include <vector>
#include "../AVL Tree/AVLTree.h"
#include "../Linked List/LinkedList.h"
#include <chrono>
#include <tuple>
#include <queue>
#define CAPACITY 15

class HashMap {
    private:
        LinkedList* LLHashMap[CAPACITY] = {new LinkedList, new LinkedList, new LinkedList, new LinkedList, new LinkedList, new LinkedList, new LinkedList, new LinkedList, new LinkedList, new LinkedList, new LinkedList, new LinkedList, new LinkedList, new LinkedList, new LinkedList};
        AVLTree* AVLHashMap[CAPACITY] = {new AVLTree, new AVLTree, new AVLTree, new AVLTree, new AVLTree, new AVLTree, new AVLTree, new AVLTree, new AVLTree, new AVLTree, new AVLTree, new AVLTree, new AVLTree, new AVLTree, new AVLTree};
        bool implementation;                            // false Linked List | true AVL Tree

        int hashFunction(int numIngredients);

    public:

        HashMap();
        ~HashMap();
        std::pair<LinkedList*, AVLTree*> operator[](int numIngredients);            // Returns the Linked List head or the AVL root node
        void insert(const std::string& recipeName, int recipeID, std::vector<std::string>& ingredients, int numIngredients);
        void changeImplementation();
        std::tuple<LinkedList::LLNode*, AVLTree::TreeNode*, std::chrono::duration<double>> search(const std::vector<std::string>& userIngredients);
        std::pair<std::pair<std::priority_queue<std::pair<float, AVLTree::TreeNode*>>, std::chrono::duration<double>>, std::pair<std::priority_queue<std::pair<float, LinkedList::LLNode*>>, std::chrono::duration<double>>> bestMatchSearch(const std::vector<std::string>& userIngredients);
        bool getImplementation();

};


#endif //PROJECT3_COP3530_FRIDGE_HASHMAP_H
