//
// Created by Tavienne Millner on 7/17/24.
//

#include "LinkedList.h"

void LinkedList::insert(std::string &recipeName, int recipeID, std::vector<std::string> &ingredients, int ingredientNum) {
    if (head == nullptr) { // empty linked list
        LinkedList::LLNode* newNode = new LinkedList::LLNode(recipeName, recipeID, ingredients, ingredientNum, nullptr);
        head = newNode;
    }
    else { // adding a new node to the front of the linked list
        LinkedList::LLNode* newNode = new LinkedList::LLNode(recipeName, recipeID, ingredients, ingredientNum, head);
        head = newNode;
    }
}

LinkedList::LLNode* LinkedList::search(std::vector<std::string>& userIngredients) {
    LinkedList::LLNode* currNode = head;
    std::set<std::string> recipeIngredients;
    bool match = true;

    while (currNode != nullptr) {
        for (int i = 0; i < currNode->ingredients.size(); i++) { // Fills a set with the recipe's ingredients
            recipeIngredients.insert(currNode->ingredients[i]);
        }

        for (int i = 0; i < recipeIngredients.size(); i++) { // Iterates through the set and checks if each ingredient the user has is in the recipe's ingredients
            if (recipeIngredients.find(userIngredients[i]) == recipeIngredients.end()) {
                match = false;
                break;
            }
        }

        if (!match) { // match is false so go to next node and reset match
            currNode = currNode->next;
            match = true;
        }
        else { // match is true so return the current node
            return currNode;
        }
    }

    // If the while loop goes through the whole list, there was no exact match
    return nullptr;
}