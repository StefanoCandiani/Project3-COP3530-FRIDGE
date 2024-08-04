//
// Created by Tavienne Millner on 7/17/24.
//

#ifndef PROJECT3_COP3530_FRIDGE_LINKEDLIST_H
#define PROJECT3_COP3530_FRIDGE_LINKEDLIST_H

#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <chrono>
#include <queue>

class LinkedList {
public:
    struct LLNode {
        // Data
        std::string recipeName;
        int recipeID;
        std::vector<std::string> ingredients;
        int numIngredients;

        LLNode* next = nullptr;

        // Parametrized constructor
        LLNode(const std::string& recipeName, int recipeID, const std::vector<std::string>& ingredients, int numIngredients, LLNode* next) : recipeName(recipeName), recipeID(recipeID), ingredients(ingredients), numIngredients(numIngredients), next(next) {}
    };

    LinkedList() {
        head = nullptr;
        size = 0;
    }

    ~LinkedList() {
        while (head != nullptr) {
            LinkedList::LLNode* nodeToDelete = head;
            head = head->next;
            delete nodeToDelete;
            nodeToDelete = nullptr;
        }
    }

    void insert(const std::string& recipeName, int recipeID, const std::vector<std::string>& ingredients, int numIngredients);
    std::pair<std::priority_queue<std::pair<float, LinkedList::LLNode*>>, std::chrono::duration<double>> bestSearch(const std::vector<std::string>& userIngredients);
    LinkedList::LLNode* search(const std::vector<std::string>& userIngredients);
    void traverse();
    int getSize();

private:
    int size;

    // Head pointer, not accessible to client
    LLNode* head;
};


#endif //PROJECT3_COP3530_FRIDGE_LINKEDLIST_H
