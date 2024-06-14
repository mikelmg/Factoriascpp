#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include "json.hpp"
#include "item.h"

using json = nlohmann::json;

void readRecipesFile();
void printRecipes();
void GetRecipeNames();

struct Recipe {
    std::string name;

    std::vector<ItemsType> outputType;
    std::vector<int> outputAmmountPerSecond;

    std::vector<ItemsType> inputType;
    std::vector<int> inputAmmountPerSecond;
};

inline std::vector<Recipe> recipes;
inline const char* recipeNames; 

inline void readRecipesFile() {
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

        std::string name;

        name.append("Recipe: ");
        for (int i = 0; i < recipe.inputAmmountPerSecond.size(); i++) {
            name.append(Item::toString(recipe.inputType[i]));
            name.append("_");
            name.append(std::to_string(recipe.inputAmmountPerSecond[i]));
            name.append(" ");
        }
        name += "-> ";
        for (int i = 0; i < recipe.outputAmmountPerSecond.size(); i++) {
            name.append(Item::toString(recipe.outputType[i]));
            name.append("_");
            name.append(std::to_string(recipe.outputAmmountPerSecond[i]));
            name.append(" ");
        }
        if (name == "Recipe: -> ")
            recipe.name = "No Recipe";
        else
            recipe.name = name;

        recipes.push_back(recipe);
    }

    GetRecipeNames();
}

inline void GetRecipeNames(){
    std::string result;
    for (int i = 0; i < recipes.size(); i++){
        result += recipes[i].name + ";";
    }
    result.pop_back();
    static std::string result_str = result;
    recipeNames = result_str.c_str();
} 

inline void printRecipes(){

    for(auto it = recipes.begin(); it != recipes.end(); ++it){

        std::cout << "Recipe: " << (*it).name << std::endl;

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
