//
// Created on 7/14/24.
//
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <chrono> // used for comparing time for search
using namespace std;

/// Welcome message (Printed 1 time)
void printWelcomeMessage() {
    cout << right << setfill('-') << "+" << setw(90) << "+" << endl;
    cout << "|      Welcome to Food and Recipes Indexing Database Generating Environment (FRIDGE)      |" << endl;
    cout << right << setfill('-') << "+" << setw(90) << "+" << endl;
    cout << "Please enter a minimum of 5 ingredients (separated by commas): " << endl;
}

/// Main menu (Printed n times, n = number of inputs not equal to 4)
void printMainMenu() {
    cout << "Main menu" << endl;
    cout << "1. Suggest a recipe" << endl;
    cout << "2. Change ingredients on hand" << endl;
    cout << "3. Toggle DSA [Initialized as Tree]" << endl;
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
    return parsedIngredients;
}

int main() {

    /// Tree Hash Map initialization
    // ...

    /// Linked List Hash Map initialization
    // ...

    /// UI Variables
    vector<string> parsedIngredients;
    string userInput, unparsedIngredients;
    bool implementation = 1;                            // 0 = linked list | 1 = AVL tree

    /// User interface printing
    // Introduction and ingredient prompting
    printWelcomeMessage();
    getline(cin, unparsedIngredients);
    parsedIngredients = parseIngredients(unparsedIngredients);

    // Ensure user provides at least 5 ingredients or at most 14 ingredients
    while(parsedIngredients.size() < 5 || parsedIngredients.size() > 14) {
        cout << "Please ensure you are providing at LEAST 5 ingredients or at MOST 14 ingredients: " << endl;
        getline(cin, unparsedIngredients);
        parsedIngredients = parseIngredients(unparsedIngredients);
    }

    cout << endl;

    // Process user input until request to leave
    while(userInput != "4") {

        printMainMenu();
        getline(cin, userInput);

        // Conditionals
        if(userInput == "1") {                          // If usrInput = 1 -> Perform search operation on currently active DSA

            // Temporary placeholder for recipe card [FIXME]
            cout << "Here's a recipe you might like:" << endl;
            cout << "+----------------------------------------------------------+-------------------------------------------------+" << endl;
            cout << "|  Company Green Beans                                     |  Ingredients:                                   |" << endl;
            cout << "|                                                          |  [Bacon, Onion, Green Beans, Whole Tomatoes]    |" << endl;
            cout << "|  https://www.food.com/recipe/company-green-beans-204270  |  You are missing 1 ingredient                   |" << endl;
            cout << "|                                                          |                                                 |" << endl;
            cout << "+----------------------------------------------------------+-------------------------------------------------+" << endl;
            cout << "Would you like another recipe suggested? (y/n)" << endl;
            getline(cin, userInput);

            if(userInput == "n") { break; }
            else if(userInput == "y") { cout << endl; continue; }


        } else if(userInput == "2") {                   // If usrInput = 2 -> Perform ingredient change operation

            changeIngredients:                          // Label - used to return to a point in the code without loops
            cout << endl;
            cout << "Please enter a minimum of 5 ingredients (separated by commas): " << endl;
            getline(cin, unparsedIngredients);
            parsedIngredients = parseIngredients(unparsedIngredients);

            if(parsedIngredients.size() < 5) { goto changeIngredients; }

            cout << endl;
            cout << "Do you confirm these are the ingredients you want? (y/n)" << endl;
            getline(cin, userInput);
            if(userInput == "y") { continue; }
            else if(userInput == "n") { goto changeIngredients; }

        } else if(userInput == "3") {                   // If usrInput = 3 -> Alternate between implementation

            cout << endl;
            if(implementation) {
                cout << "🔴 AVL Tree implementation" << endl;
                cout << "🟢 Linked List implementation" << endl;
            } else {
                cout << "🟢 AVL Tree implementation" << endl;
                cout << "🔴 Linked List implementation" << endl;
            }
            cout << endl;

            implementation = !implementation;

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
