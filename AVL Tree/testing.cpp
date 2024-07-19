#include <chrono>
#include "IOManager/IOManager.h"
#include "AVL TREE/AVLTree.h"

using namespace std;
/*
 * TO DO:
 *  Pointer Cleanup
 *  Authentication
 *
 *  Max Insertion Time (25,000 recipes): 15.5646
 */

int main() {
    vector<Recipe*> recipes = IOManager::ReadIngredients("squeaky_clean_ingredients.csv");
    AVLTree avlTree;

    cout << "AVL Tree Start" << endl;
    auto pastTime = std::chrono::system_clock::now();

    vector<Recipe*> toInsert;

    for(int i = 0; i < 25000; i++)
        toInsert.push_back(recipes[i]);

    for(auto& i : toInsert)
            avlTree.Insert(i->name, i->recipe_id, i->ingredients, i->ingredient_num);


    auto now = std::chrono::system_clock::now();
    chrono::duration<double> elaspedTime = now-pastTime;
    cout << "AVL Tree Fin" << endl;
    cout << "AVL Tree Insertion Time: " << elaspedTime.count() << std::endl;

    return 0;
}
