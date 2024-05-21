#pragma once
#include <raylib.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "selectable.h"
#include "connection.h"

#define PRODUCTION_LEVELS_FILE "src/Resources/facts - Import.csv"

struct ProductionLevels{
    int level;
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
                level.level = std::stoi(line);

                productionLevels.push_back(level);
            }
        }

        file.close();

        for (const auto& aux : productionLevels) {
            std::cout << "Float Level: " << aux.production << ", Integer Level: " << aux.level << std::endl;
        }
        return productionLevels;
    }
} ;
static const std::vector<ProductionLevels> PRODUCTION_LVLS = ProductionLevels::ReadLvlFile(PRODUCTION_LEVELS_FILE);



static const std::vector<Color> LVLCOLORS = {
    RAYWHITE,
    BEIGE,
    WHITE,
    BLACK,
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


    struct InventaryPerItem{
        ItemsType type;
        int amount;
    };



public:
    Building();
    Building(int x, int y, int level);
    void Update(float dt);
    void Draw();
    Vector2 GetCenter();
    void UpdateConnections();
    void AddInConnection(Connection* con);
    void AddOutConnection(Connection* con);
    void DeleteInConnection(Connection* con);
    void DeleteOutConnection(Connection* con); 
    void Production();
    void AddItemsToConnection(Connection* con, ItemsPosition itemsPositions);


    //TODO Make Buildings create Items at speed proportinal to their lvl

private:
    // Vector2 position;
    // bool selected;

    int level;
    Color color;
    std::vector<Connection*> inConnections;
    std::vector<Connection*> outConnections;
    std::vector<InventaryPerItem> inventary;
    //TODO Implement inventary
    

};


