#pragma once
#include <raylib.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include "selectable.h"
#include "connection.h"
#include "recipe.hpp"


#define PRODUCTION_LEVELS_FILE "src/Resources/facts - Import.csv"
#define MAX_ITEM_UPSCALE 5
#define ITEM_UPSCALE_CYCLE_RATE 150.0F

struct ProductionLevels{
    int stack;
    float production;

    static std::vector<ProductionLevels> ReadLvlFile(const std::string& filename) {
        std::ifstream file(filename);

        std::vector<ProductionLevels> productionLevels;

        if (!file.is_open()) {
            std::cout << "ERROR al abrir el csv" << std::endl;
        } else {
            std::string line;
            while (getline(file, line, ',')) {
                ProductionLevels level;

                level.production = std::stof(line);

                getline(file, line);
                level.stack = std::stoi(line);

                productionLevels.push_back(level);
            }
        }

        file.close();

        for (const auto& aux : productionLevels) {
            std::cout << "Float Level: " << aux.production << ", Integer Level: " << aux.stack << std::endl;
        }
        return productionLevels;
    }
} ;
static const std::vector<ProductionLevels> PRODUCTION_LVLS = ProductionLevels::ReadLvlFile(PRODUCTION_LEVELS_FILE);

static const std::vector<Color> LVLCOLORS = {
    BEIGE,
    WHITE,
    BROWN,
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    LIME,
    BLUE,
    SKYBLUE,
    PURPLE,
    VIOLET,
    DARKPURPLE,
    MAROON,
    DARKGREEN,
    DARKBLUE,
    DARKBROWN,
    DARKGRAY,
    LIGHTGRAY
};

static const int BUILDING_SIZE = 40;


class Building: public Selectable //Declaration forward
{
public:
    Building();
    Building(int x, int y, int level);
    // ~Building() override;

    void Draw();
    void DrawSelection();
    Vector2 GetCenter();
    int GetSize() override; 
    SelectableTypes GetSelectableType() override;

    void Production(const float &dt);

    Rectangle GetRectangle() override;
    //TODO Make Buildings create Items at speed proportinal to their lvl

private:
    int level;
    Color color;
    float spawnTimer;

    Recipe* recipe;
};


