//
// Created on 7/14/24.
//


#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <chrono> // used for comparing time for search
#include "HashMap/HashMap.h"
#include "IOManager/IOManager.h"
#include "Recipe/Recipe.h"
using namespace std;



/// Welcome message (Printed 1 time)
void printWelcomeMessage() {
    cout << right << setfill('-') << "+" << setw(90) << "+" << endl;
    cout << "|      Welcome to Food and Recipes Indexing Database Generating Environment (FRIDGE)      |" << endl;
    cout << right << setfill('-') << "+" << setw(90) << "+" << endl;
    cout << "Please enter a minimum of 4 ingredients (separated by commas): " << endl;
}

/// Main menu (Printed n times, n = number of inputs not equal to 4)
void printMainMenu(bool implementation) {
    cout << "Main menu" << endl;
    cout << "1. Suggest a recipe" << endl;
    cout << "2. Change ingredients on hand" << endl;
    if (implementation)
        cout << "3. Toggle DSA [AVL Tree]" << endl;
    else
        cout << "3. Toggle DSA [Linked List]" << endl;
    cout << "4. Exit" << endl;
    cout << endl;
    cout << "Please make a selection (1-4): ";
}

/// Parses the ingredient string into an array for later use
vector<string> parseIngredients(string unparsedIngredients) {

    /* Explanation: Run parsing operation until unparsed string is of size less than 0. Start by parsing string from
     * start to comma, transforming the ingredient so that all characters are in lowercase, and then pushing back the
     * ingredient to parsedIngredients. Lastly, the current ingredient is removed from the unparsedIngredients and the
     * process is repeated. Conclude parsing by returning parsedIngredients.
     * */

    vector<string> parsedIngredients;
    string ingredient;
    while(!unparsedIngredients.empty()) {
        ingredient = unparsedIngredients.substr(0, unparsedIngredients.find(","));
        transform(ingredient.begin(), ingredient.end(), ingredient.begin(), ::tolower);
        parsedIngredients.push_back(ingredient);
        unparsedIngredients = unparsedIngredients.substr(unparsedIngredients.find(",") + 2,
                                                         unparsedIngredients.size() - ingredient.size());
    }
    sort(parsedIngredients.begin(), parsedIngredients.end());
    return parsedIngredients;
}

int main() {
    cout << "Please give program time to load database" << endl;
    cout << "\n\n\n" << endl;

    // Fill a vector with recipes
    vector<Recipe*> recipes = IOManager::ReadIngredients("immaculate_ingredients.csv");

    /// Hash Map initialization
    // Initializes AVLTree version and LinkedList
    HashMap hashMap;


    // Fill HashMap
    for (int i = 0; i < recipes.size(); i++) {
        hashMap.insert(recipes[i]->name, recipes[i]->recipe_id, recipes[i]->ingredients, recipes[i]->ingredient_num);
    }

    /// UI Variables
    vector<string> parsedIngredients;
    string userInput, unparsedIngredients;                           // 0 = linked list | 1 = AVL tree

    /// User interface printing
    // Introduction and ingredient prompting
    printWelcomeMessage();
    getline(cin, unparsedIngredients);
    parsedIngredients = parseIngredients(unparsedIngredients);

    // Ensure user provides at least 4 ingredients or at most 18 ingredients
    while(parsedIngredients.size() < 4 || parsedIngredients.size() > 18) {
        cout << "Please ensure you are providing at LEAST 4 ingredients or at MOST 18 ingredients: " << endl;
        getline(cin, unparsedIngredients);
        parsedIngredients = parseIngredients(unparsedIngredients);
    }

    cout << endl;

    // Process user input until request to leave
    while(userInput != "4") {

        printMainMenu(hashMap.getImplementation());
        getline(cin, userInput);

        // Conditionals
        if(userInput == "1") {                          // If usrInput = 1 -> Perform search operation on currently active DSA

            search:
            auto find = hashMap.search(parsedIngredients);

            if (get<0>(find) == nullptr && get<1>(find) == nullptr) {
                cout << "no recipe found with your ingredients" << endl;
            }
            else {
                cout << fixed;
                cout << "Here's a recipe you may like:" << endl;
                if (get<0>(find) != nullptr) {
                    cout << get<0>(find)->recipeName << endl;
                    cout << "search executed in " << get<2>(find).count() << " seconds." << endl;
                    cout << endl;
                }
                else {
                    cout << get<1>(find)->recipeName << endl;
                    cout << "search executed in " << get<2>(find).count() << " seconds." << endl;
                    cout << endl;
                }
            }

            // Temporary placeholder for recipe card [FIXME]
//            cout << "Here's a recipe you might like:" << endl;
//            cout << "+----------------------------------------------------------+-------------------------------------------------+" << endl;
//            cout << "|  Company Green Beans                                     |  Ingredients:                                   |" << endl;
//            cout << "|                                                          |  [Bacon, Onion, Green Beans, Whole Tomatoes]    |" << endl;
//            cout << "|  https://www.food.com/recipe/company-green-beans-204270  |  You are missing 1 ingredient                   |" << endl;
//            cout << "|                                                          |                                                 |" << endl;
//            cout << "+----------------------------------------------------------+-------------------------------------------------+" << endl;


            // if another recipe is suggested, use the closest match search
            cout << "Would you like another recipe suggested? (y/n)" << endl;
            getline(cin, userInput);

            if(userInput == "n") { cout << endl; continue; }
            else if(userInput == "y") { goto search; }


        } else if(userInput == "2") {                   // If usrInput = 2 -> Perform ingredient change operation

            changeIngredients:                          // Label - used to return to a point in the code without loops
            cout << endl;
            cout << "Please enter a minimum of 4 ingredients (separated by commas): " << endl;
            getline(cin, unparsedIngredients);
            parsedIngredients = parseIngredients(unparsedIngredients);

            if(parsedIngredients.size() < 4) { goto changeIngredients; }

            cout << endl;
            cout << "Do you confirm these are the ingredients you want? (y/n)" << endl;
            getline(cin, userInput);
            if(userInput == "y") { continue; }
            else if(userInput == "n") { goto changeIngredients; }

        } else if(userInput == "3") {                   // If usrInput = 3 -> Alternate between implementation
            hashMap.changeImplementation();
            cout << endl;

        } else {
            if(userInput != "4") {
                cout << endl;
                cout << "Please provide a proper answer" << endl;
                cout << endl;
            }

        }

    }

    cout << endl;
    cout << "Thank you for using FRIDGE! Please come back again!" << endl;

    return 0;
}


/*int main() {
    HashMap hashMap;

    vector<Recipe*> recipes = IOManager::ReadIngredients("immaculate_ingredients.csv");
    cout << recipes.size() << endl;

    for (int i = 0; i < recipes.size(); i++) {
        hashMap.insert(recipes[i]->name, recipes[i]->recipe_id, recipes[i]->ingredients, recipes[i]->ingredient_num);
    }

//    std::cout << std::fixed;
//
//    std::chrono::time_point<std::chrono::system_clock> start, end;
//
//    start = std::chrono::system_clock::now();
//
//    LinkedList::LLNode* LLfound = hashMap[0].first->search({"frozen peaches", "honey", "orange juice", "vanilla yogurt"});
//    std::cout << LLfound->recipeName << std::endl;
//
//    end = std::chrono::system_clock::now();
//    std::chrono::duration<double> elaspedTime = end-start;
//
//    std::cout << elaspedTime.count() << " seconds" << std::endl;
//
//
//    start = std::chrono::system_clock::now();
//    AVLTree::TreeNode* TreeNodeFound = hashMap[0].second->search({"frozen peaches", "honey", "orange juice", "vanilla yogurt"});
//    std::cout << TreeNodeFound->recipeName << std::endl;
//
//    end = std::chrono::system_clock::now();
//    elaspedTime = end-start;
//
//    std::cout << elaspedTime.count() << " seconds" << std::endl;

    hashMap.changeImplementation();

    auto find = hashMap.search({"frozen peaches", "honey", "orange juice", "vanilla yogurt"});

    if (find.first!=nullptr)
        std::cout << find.first->recipeName << std::endl;
    else
        std::cout << find.second->recipeName << std::endl;

    return 0;
}*/