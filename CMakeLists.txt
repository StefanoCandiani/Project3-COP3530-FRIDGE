cmake_minimum_required(VERSION 3.28)
project(Project3-COP3530-FRIDGE)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project3-COP3530-FRIDGE main.cpp
        "Linked List/LinkedList.h"
        "Linked List/LinkedList.cpp"
        "AVL Tree/AVLTree.h"
        "AVL Tree/AVLTree.cpp"
        "HashMap/HashMap.h"
        "HashMap/HashMap.cpp"
        "IOManager/IOManager.h"
        "Recipe/Recipe.h"
        "Recipe/Recipe.cpp")
