//
// Created by Stefano Candiani on 7/27/24.
//

#ifndef PROJECT3_COP3530_FRIDGE_HASHMAP_H
#define PROJECT3_COP3530_FRIDGE_HASHMAP_H

#include <iostream>
#include <vector>
#include "../AVL Tree/AVLTree.h"
#include "../Linked List/LinkedList.h"
#define CAPACITY 14

class HashMap {

    private:
        LinkedList* LLHashMap[CAPACITY];
        AVLTree* AVLHashMap[CAPACITY];
        bool implementation;                            // 0 Linked List | 1 AVL Tree

        int hashFunction(int numIngredients);

    public:

        HashMap();
        ~HashMap();
        template <typename T>
        T operator[](int numIngredients);            // Returns the Linked List head or the AVL root node
        void insert(const std::string& recipeName, int recipeID, std::vector<std::string>& ingredients, int numIngredients);
        void changeImplementation();

};


#endif //PROJECT3_COP3530_FRIDGE_HASHMAP_H
