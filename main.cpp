//
// Created on 7/14/24.
//


#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <sstream>
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
        cout << "3. Toggle DSA [Currently AVL Tree]" << endl;
    else
        cout << "3. Toggle DSA [Currently Linked List]" << endl;
    cout << "4. Exit" << endl;
    cout << endl;
    cout << "Please make a selection (1-4): ";
}

/// Print Recipe Title Card
void printRecipeCard(AVLTree::TreeNode* tNode, LinkedList::LLNode* llNode, float percentage) {
    // Card elements initialization
    string recipeName, linkName;
    string recipeIngredients = "Ingredients: ";
    string link = " https://www.food.com/recipe/";
    stringstream perSim;
    perSim << "Percent similarity: " << fixed << setprecision(0) << percentage * 100 << "% ";
    vector<string> ingredients;
    int recipeId;
    double topBarSize,bottomBarSize;

    // Check which node to take in data from (linked list node or tree node)
    if(tNode == nullptr && llNode != nullptr) {
        recipeName = llNode -> recipeName;
        ingredients = llNode -> ingredients;
        recipeId = llNode -> recipeID;
    } else if(llNode == nullptr && tNode != nullptr) {
        recipeName = tNode -> recipeName;
        ingredients = tNode -> ingredients;
        recipeId = tNode -> recipeID;
    }

    // Ensure nodes are truly existent
    if(tNode != nullptr || llNode != nullptr) {

        // Write down ingredients into a single string for printing
        for (int i = 0; i < ingredients.size(); i++) {
            recipeIngredients += ingredients[i];
            if (i < ingredients.size() - 1) { recipeIngredients += ", "; }
            else { recipeIngredients += " "; }
        }

        // Link identification
        for (char c: recipeName) {
            if (c != ' ') { linkName += c; }
            else { linkName += '-'; }
        }
        link += linkName + "-" + to_string(recipeId);

        // Dynamic size allocation based on recipe size
        double topLeftBarSize = max(recipeName.size(), link.size()) * 2.2;
        double topRightBarSize = recipeIngredients.size() * 2.2;

        // Final product printing
        cout << "+";
        cout << setw((topLeftBarSize / 2) + 1) << setfill('-');
        cout << "+";
        cout << setw((topRightBarSize / 2) + 1) << setfill('-');
        cout << "+" << endl;

        cout << "| ";
        cout << left << setw((topLeftBarSize / 2) - 1) << setfill(' ') << recipeName;
        cout << "|";
        cout << right << setw(topRightBarSize / 2) << setfill(' ');
        cout << recipeIngredients;
        cout << "|" << endl;

        cout << "|";
        cout << left << setw(topLeftBarSize / 2) << setfill(' ') << " ";
        cout << "|";
        cout << right << setw(topRightBarSize / 2) << setfill(' ') << " ";
        cout << "|" << endl;

        cout << "|";
        cout << left << setw(topLeftBarSize / 2) << setfill(' ') << link;
        cout << "|";
        cout << right << setw(topRightBarSize / 2) << setfill(' ') << perSim.str();
        cout << "|" << endl;

        cout << "+";
        cout << right << setw((topLeftBarSize / 2) + 1) << setfill('-');
        cout << "+";
        cout << setw((topRightBarSize / 2) + 1) << setfill('-');
        cout << "+" << endl;
    }
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

    // UI Variables
    vector<string> parsedIngredients;
    string userInput, unparsedIngredients;                           // false = linked list | true = AVL tree

    // User interface printing
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
        cout << endl;

        // Conditionals
        if(userInput == "1") {                          // If usrInput = 1 -> Perform search operation on currently active DSA
            bool closeSearch = false;

            auto find = hashMap.search(parsedIngredients);

            if (get<0>(find) == nullptr && get<1>(find) == nullptr) {
                search:
                cout << endl;
                cout << "Executing closest match search because no exact match found" << endl;
                auto closestMatches = hashMap.bestMatchSearch(parsedIngredients);
                if (hashMap.getImplementation()) {  //Avl Tree Best Search
                    cout << "Closest matches search executed in " << closestMatches.first.second.count() << " seconds." << endl;

                    AVLClosest:
                    if (!closestMatches.first.first.empty()) {
                        AVLTree::TreeNode* AVLmatch = closestMatches.first.first.top().second;
                        float percentage = closestMatches.first.first.top().first;
                        closestMatches.first.first.pop();

                        // call stefano's print closest match function
                        printRecipeCard(AVLmatch, nullptr, percentage);
                        cout << endl;

                        cout << "Would you like another recipe suggested? (y/n)" << endl;
                        getline(cin, userInput);
                        cout << endl;

                        if(userInput == "n") { cout << endl; continue; }
                        else if(userInput == "y" && !closestMatches.first.first.empty()) { goto AVLClosest; }
                    }
                }
                else {  //Linked List Best Search
                    cout << "Closest matches search executed in " << closestMatches.first.second.count() << " seconds." << endl;

                    LLClosest:
                    if (!closestMatches.second.first.empty()) {
                        LinkedList::LLNode *LLmatch = closestMatches.second.first.top().second;
                        float percentage = closestMatches.second.first.top().first;
                        closestMatches.second.first.pop();

                        printRecipeCard(nullptr, LLmatch, percentage);
                        cout << endl;

                        cout << "Would you like another recipe suggested? (y/n)" << endl;
                        getline(cin, userInput);
                        cout << endl;

                        if(userInput == "n") { cout << endl; continue; }
                        else if (userInput == "y" && !closestMatches.second.first.empty()) { goto LLClosest; }
                    }
                }
                closeSearch = true;
            }
            else {
                cout << fixed;
                cout << "Here's a recipe you may like:" << endl;
                if (get<0>(find) != nullptr) {
                    printRecipeCard(nullptr, get<0>(find), 1.0f);
                    cout << "Search executed in " << get<2>(find).count() << " seconds." << endl;
                    cout << endl;
                }
                else {
                    printRecipeCard(get<1>(find), nullptr, 1.0f);
                    cout << "Search executed in " << get<2>(find).count() << " seconds." << endl;
                    cout << endl;
                }
            }

            if(!closeSearch){

                cout << "Would you like another recipe suggested? (y/n)" << endl;
                getline(cin, userInput);
                if(userInput == "n") { cout << endl; continue; }
                else if(userInput == "y" && !closeSearch) { goto search; }

            } else {
                cout << "No more closest matches" << endl;
                cout << endl;
            }


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
            cout << endl;
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

