//
// Created by nicol on 7/16/2024.
//
#include <string>
#include <vector>

#ifndef UNTITLED3_RECIPE_H
#define UNTITLED3_RECIPE_H

using namespace std;

class Recipe{
public:
    string name;
    int recipe_id;
    vector<string> ingredients;
    int ingredient_num;

    Recipe(string name, int recipe_id, int unknown_number){
        this->name = name;
        this->recipe_id = recipe_id;
        this->ingredient_num = unknown_number;
    }

    void AddIngredient(string ingredient);
};
#endif //UNTITLED3_RECIPE_H
