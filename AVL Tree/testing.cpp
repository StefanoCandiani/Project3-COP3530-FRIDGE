#include <chrono>
#include "IOManager/IOManager.h"
#include "AVL TREE/AVLTree.h"

using namespace std;
/*
 * TO DO:
 *  Sort by Ingredient Number
 *  Pointer Cleanup
 *  Implement Similar Ingredient Amount Scenario
 */

int main() {
    vector<Recipe*> recipes = IOManager::ReadIngredients("squeaky_clean_ingredients.csv");
    AVLTree avlTree;

    cout << "AVL Tree Start" << endl;
    auto pastTime = std::chrono::system_clock::now();

    for(auto& i : recipes)
        if(i->recipe_id < 10000)    //Acts as slot range in map.
            avlTree.Insert(i->name, i->recipe_id, i->ingredients, i->ingredient_num);


    auto now = std::chrono::system_clock::now();
    std::chrono::duration<double> elaspedTime = now-pastTime;
    cout << "AVL Tree Fin" << endl;
    std::cout << "AVL Tree Insertion Time: " << elaspedTime.count() << std::endl;

    return 0;
}
