//
// Created by Tavienne Millner on 7/17/24.
//

#ifndef PROJECT3_COP3530_FRIDGE_LINKEDLIST_H
#define PROJECT3_COP3530_FRIDGE_LINKEDLIST_H

#include <string>
#include <vector>
#include <set>

class LinkedList {
public:
    struct LLNode {
        // Data
        std::string recipeName;
        int recipeID;
        std::vector<std::string> ingredients;
        int ingredientNum;

        LLNode* next = nullptr;

        // Parametrized constructor
        LLNode(std::string& recipeName, int recipeID, std::vector<std::string>& ingredients, int ingredientNum, LLNode* next) : recipeName(recipeName), recipeID(recipeID), ingredients(ingredients), ingredientNum(ingredientNum), next(next) {}
    };

    LinkedList() {
        head = nullptr;
    }

    ~LinkedList() {
        while (head != nullptr) {
            LinkedList::LLNode* nodeToDelete = head;
            head = head->next;
            delete nodeToDelete;
            nodeToDelete = nullptr;
        }
    }

    void insert(std::string& recipeName, int recipeID, std::vector<std::string>& ingredients, int ingredientNum);
    LinkedList::LLNode* search(std::vector<std::string>& userIngredients);

private:
    // Head pointer, not accessible to client
    LLNode* head;
};


#endif //PROJECT3_COP3530_FRIDGE_LINKEDLIST_H
