//
// Created by Stefano Candiani on 7/27/24.
//

#include "HashMap.h"

/// Default Constructor
HashMap::HashMap() {
    implementation = 1;
    for(int i = 0; i < CAPACITY; i++) {
        LLHashMap[i] = new LinkedList;
    }
    for(int i = 0; i < CAPACITY; i++) {
        AVLHashMap[i] = new AVLTree;
    }
}

/// Destructor
HashMap::~HashMap() {
    for(LinkedList* LL : LLHashMap) {
        delete LL;
    }
    for(AVLTree* AVL : AVLHashMap) {
        delete AVL;
    }
}

/// Hash Map
int HashMap::hashFunction(int numIngredients) {
    return numIngredients - 4;
}

/// Insert Function
void HashMap::insert(const std::string &recipeName, int recipeID, std::vector<std::string> &ingredients,
                     int numIngredients) {
    int hashCode = hashFunction(numIngredients);
    LLHashMap[hashCode] -> insert(recipeName, recipeID, ingredients, numIngredients);
    AVLHashMap[hashCode] -> insert(recipeName, recipeID, ingredients, numIngredients);
}

/// Change implementation
void HashMap::changeImplementation() {
    implementation = !implementation;
}

/// Operator [] gives AVL tree object pointer at a given hash index
template <typename T>
T HashMap::operator[] (int numIngredients) {
    int hashCode = hashFunction(numIngredients);
    // Return proper implementation at a given hash index
    if(implementation) {                // AVL Tree (Implementation = 1)
        return AVLHashMap[hashCode];
    } else {                            // Linked List (Implementation = 0)
        return LLHashMap[hashCode];
    }
}