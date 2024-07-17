#include "IOManager/IOManager.h"
#include "AVL TREE/AVLTree.h"

using namespace std;
int main() {
    vector<Recipe*> recipes = IOManager::Read("squeaky_clean_ingredients.csv");
    AVLTree avlTree;

    cout << "Start" << endl;
    for(auto& i : recipes)
        if(i->recipe_id < 10000)
        avlTree.Insert(i->name, i->recipe_id, i->ingredients, i->ingredient_num);   //TO DO: Sort by Ingredient Number


    cout << "Fin" << endl;
    return 0;
}
