//
// Created by Tavienne Millner on 7/17/24.
//

#include <queue>
#include "LinkedList.h"

void LinkedList::insert(const std::string &recipeName, int recipeID, const std::vector<std::string> &ingredients, int numIngredients) {
    if (head == nullptr) { // empty linked list
        LinkedList::LLNode* newNode = new LinkedList::LLNode(recipeName, recipeID, ingredients, numIngredients, nullptr);
        head = newNode;
    }
    else { // adding a new node to the front of the linked list
        LinkedList::LLNode* newNode = new LinkedList::LLNode(recipeName, recipeID, ingredients, numIngredients, head);
        head = newNode;
    }
    size++;
}
std::priority_queue<std::pair<float, LinkedList::LLNode*>> LinkedList::bestSearch(const std::vector<std::string>& userIngredients) {
    LinkedList::LLNode* currNode = head;
    std::set<std::string> recipeIngredients;
    std::priority_queue<std::pair<float, LinkedList::LLNode*>> pq;

    while (currNode != nullptr) {

        float percentageMatch = 0.0f;
        float increment = 1.0f/ (float) currNode->ingredients.size();

        for (int i = 0; i < currNode->ingredients.size(); i++)
            recipeIngredients.insert(currNode->ingredients[i]);

        for (int i = 0; i < recipeIngredients.size(); i++)
            if (recipeIngredients.find(userIngredients[i]) != recipeIngredients.end())
                percentageMatch += increment;

        pq.push(std::make_pair(percentageMatch, currNode));
        currNode = currNode->next;
        recipeIngredients.clear();
    }

    return pq;
}
LinkedList::LLNode* LinkedList::search(const std::vector<std::string>& userIngredients) {
    LinkedList::LLNode* currNode = head;
    std::set<std::string> recipeIngredients;

    while (currNode != nullptr) {
        bool match = true;
        for (int i = 0; i < currNode->ingredients.size(); i++) { // Fills a set with the recipe's ingredients
            recipeIngredients.insert(currNode->ingredients[i]);
        }

        for (int i = 0; i < recipeIngredients.size(); i++) { // Iterates through the set and checks if each ingredient the user has is in the recipe's ingredients
            if (recipeIngredients.find(userIngredients[i]) == recipeIngredients.end()) {
                match = false;
                break;
            }
        }

        if (!match) { // match is false so go to next node and clear the set
            currNode = currNode->next;
            recipeIngredients.clear();
        }
        else { // match is true so return the current node
            return currNode;
        }
    }

    // If the while loop goes through the whole list, there was no exact match
    return nullptr;
}

void LinkedList::traverse() {
    LinkedList::LLNode* currNode = head;
    while (currNode!=nullptr) {
        std::cout << currNode->recipeName << std::endl;
        currNode = currNode->next;
    }
}

int LinkedList::getSize() {
    return size;
}