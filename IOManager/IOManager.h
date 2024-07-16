#include <iostream>
#include <fstream>
#include <vector>
#include "Recipe.h"

#ifndef UNTITLED3_IOMANAGER_H
#define UNTITLED3_IOMANAGER_H
using namespace std;
class IOManager{
public:

    static vector<string> Split(string line, char delimiter) {
        vector<string> components;
        string string_builder;

        for (char i : line) {
            if(string_builder == " ") string_builder.clear();;
            if (i == delimiter) {
                if (!string_builder.empty()) {
                    components.push_back(string_builder);
                    string_builder.clear();
                }
            } else
                string_builder += i;
        }

        if (!string_builder.empty()) components.push_back(string_builder);
        return components;
    }

    static vector<string> FormatData(string line){
        vector<string> components;
        string string_builder = "";
        bool isIngredients = false;

        for(auto i : line){
            if(i == '"') continue;
            if(i == ',' && !isIngredients){
                components.push_back(string_builder);
                string_builder = "";
                continue;
            }
            if(i == ',' && isIngredients) continue;
            if(i == '['){
                isIngredients = true;
                continue;
            }
            if(i == ']'){
                isIngredients = false;
                components.push_back(string_builder);
                string_builder = "";
                continue;
            }
            if(i == '\n') continue;
            if(i != ',') string_builder += i;
        }

        // Push the remaining string_builder to components
        if (!string_builder.empty()) {
            components.push_back(string_builder);
        }

        return components;
    }

    static vector<Recipe*> Read(string file_path){
        ifstream file(".//..//" + file_path);
        vector<string> data;

        if (!file.is_open()) {
            cerr << "Error opening file: " << file_path << endl;
            exit(-1);
        }

        string line;
        vector<string> components;
        vector<Recipe*> recipes;
        while (getline(file, line)) {
            components = FormatData(line);
            string name = components[0];
            string id = components[1];
            vector<string> ingredients =Split(components[2], '\'');

            Recipe *recipe = new Recipe(name, stoi(id), ingredients.size());

            for (auto i: ingredients)
                recipe->AddIngredient(i);

            recipes.push_back(recipe);


        }
        file.close();
        return recipes;
    }
};
#endif //UNTITLED3_IOMANAGER_H
