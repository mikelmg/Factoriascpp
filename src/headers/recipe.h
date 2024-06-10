#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include "json.hpp"
#include "item.h"

using json = nlohmann::json;

struct Recipe {

    std::vector<ItemsType> outputType;
    std::vector<int> outputAmmountPerSecond;

    std::vector<ItemsType> inputType;
    std::vector<int> inputAmmountPerSecond;
};

std::vector<Recipe> recipes;

void readRecipesFile() {
    std::ifstream i("src/Resources/recipes.json");
    if (!i.is_open()) {
        std::cerr << "Failed to open recipes.json\n";
        return;
    }
    json j;
    try {
        i >> j;
    } catch (const json::parse_error& e) {
        std::cerr << "Failed to parse recipes.json\n";
        return;
    }

    const json& recipesJson = j["recipes"];
    for (const auto& recipeJ : recipesJson) {
        Recipe recipe;

        recipe.outputType = Item::toItemsTypeV(recipeJ["outputType"]);
        recipeJ.at("outputAmmountPerSecond").get_to(recipe.outputAmmountPerSecond);
        recipe.inputType = Item::toItemsTypeV(recipeJ["inputType"]);
        recipeJ.at("inputAmmountPerSecond").get_to(recipe.inputAmmountPerSecond);

        recipes.push_back(recipe);
    }
}

void printRecipes(){

    for(auto it = recipes.begin(); it != recipes.end(); ++it){

        std::cout << "Output Type: ";
        for(auto it2 = (*it).outputType.begin(); it2 != (*it).outputType.end(); ++it2){
            std::cout << *it2 << " ";
        }
        std::cout << "\nOutput Amount Per Second: ";
        for(auto it2 = (*it).outputAmmountPerSecond.begin(); it2 != (*it).outputAmmountPerSecond.end(); ++it2){
            std::cout << *it2 << " ";
        }
        std::cout << "\nInput Type: ";
        for(auto it2 = (*it).inputType.begin(); it2 != (*it).inputType.end(); ++it2){
            std::cout << *it2 << " ";
        }
        std::cout << "\nInput Amount Per Second: ";
        for(auto it2 = (*it).inputAmmountPerSecond.begin(); it2 != (*it).inputAmmountPerSecond.end(); ++it2){
            std::cout << *it2 << " ";
        }
        std::cout << std::endl << std::endl;
    }
}
