# FRIDGE (Food and Recipes Indexing Database Generating Environment)
## Project 3, COP 3530
Nicolas Calafiore, Stefano Candiani, Tavienne Millner

## Motivation

  When it comes to home-cooking, recipe website users will generally spend a large amount of time looking for a recipe that matches the ingredients that one has at home. By prompting a user to identify the ingredients within their fridge, our project seeks to facilitate user accessibility to various recipes hosted by Food.com, highlighting those that have the closest match to the user specifications. 

  The overarching goal of this project is to conduct a comparison in the search algorithm of two implementatiosn of a hash map data structure our team would develop. These two implementations would differ in the collision management system where one would append data in a linked list system while the other in a self-balancing AVL tree system. The comparison would be conducted in terms of which system can find the first exact match the fastest.

## How to Run Our Code

  After cloning the repository and the various components of our code, the user needs to run main.cpp to begin the system. After they run main.cpp the program will need a few seconds to extract the data from our dataset and populate the HashMap. After that is completed, the user needs to simply input a list of the ingredients that they would like to look up a recipe for and press enter (please ensure that the ingredients do not contain any apostrophes and are separated by a comma and a space). At that moment, the user will be prompted to make a selection out of the 4 possible selections of 1. Suggest a recipe, 2. Change ingredients, 3. Change implementation, and 4. Exit. If the user selects 1, a perfect match will first be sought and printed. If that doesn't work, then the next best match is provided. In either case the user is repeatedly prompted with a (y/n) question if they would like to receive another recipe. Different recipes are provided until no more similar matches can be found. Returning to the main menu, the user can also change their ingredients by pressing 2 at which point they're once again prompted to write their ingredient list and they are prompted to confirm if those are the ingridients they desire to use. Lastly, the user can also change the HashMap implementation from Linked List to AVL Tree implementations and vice versa by selecting option 3 in the main menu. This will allow for comparisons of search times in either HashMap implementation. When the user is done with using the program they can select option 4 in the main menu which exits out of the program and provides a goodbye message. The code can then be run again by the user as many times as they desire.

## Build Status

This project is currently under development starting from around July 3th, 2024. Any major developments will be recorded below:
* July 3rd, 2024 - Project development initialized.
* July 16th, 2024 - AVL tree implementation initial commit.
* July 18th, 2024 - Linked List implementation initial commit.
* July 20th, 2024 - Performing stress testing of initial AVL and Linked List implementations (Results satisfactory).
* July 21st, 2024 - User Interface implementation commit.
* July 28th, 2024 - Hash Map implementation commit.
* July 29th, 2024 - Merged all branches. Working on reorganizing components coherently.
* August 3rd, 2024 - All project components are complete. Finished stylizing main.cpp menu prompting. 

## Dataset

The dataset used for this project is a more organized and less skewed version of the following dataset acquired at Kaggle.com 
<a href="https://www.kaggle.com/datasets/shuyangli94/food-com-recipes-and-user-interactions?select=RAW_recipes.csv">Food.com Recipes and Interactions</a>
