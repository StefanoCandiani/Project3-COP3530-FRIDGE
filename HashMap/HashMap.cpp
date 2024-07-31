//
// Created by Stefano Candiani on 7/27/24.
//

#include "HashMap.h"

HashMap::HashMap() {
    implementation = true;
}

HashMap::~HashMap() {
    // TODO
}

std::pair<LinkedList*, AVLTree*> HashMap::operator[](int index) {
    return {LLHashMap[index], AVLHashMap[index]};
}

void HashMap::insert(const std::string &recipeName, int recipeID, std::vector<std::string> &ingredients, int numIngredients) {
    int hashCode = hashFunction(numIngredients);
    LLHashMap[hashCode]->insert(recipeName, recipeID, ingredients, numIngredients);
    AVLHashMap[hashCode]->insert(recipeName, recipeID, ingredients, numIngredients);
}

void HashMap::changeImplementation() {
    implementation = !implementation;
}

int HashMap::hashFunction(int numIngredients) {
    return numIngredients-4;
}

std::tuple<LinkedList::LLNode*, AVLTree::TreeNode*, std::chrono::duration<double>> HashMap::search(const std::vector<std::string>& userIngredients) {
    int hashCode = hashFunction(userIngredients.size());

    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elaspedTime;

    if (implementation) {
        std::cout << "\nTREE" << std::endl;
        start = std::chrono::system_clock::now();
        AVLTree::TreeNode* found = AVLHashMap[hashCode]->search(userIngredients);
        end = std::chrono::system_clock::now();
        elaspedTime = end-start;

        return std::make_tuple(nullptr, found, elaspedTime);
    }
    else {
        std::cout << "\nLIST" << std::endl;
        start = std::chrono::system_clock::now();
        LinkedList::LLNode* found = LLHashMap[hashCode]->search(userIngredients);
        end = std::chrono::system_clock::now();
        elaspedTime = end-start;

        return std::make_tuple(found, nullptr, elaspedTime);
    }
}

bool HashMap::getImplementation() {
    return implementation;
}