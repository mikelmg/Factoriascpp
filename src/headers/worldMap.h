#pragma once
#include "globalParam.h"
#include "selectable.h"
#include "item.h"
#include <raylib.h>
#include <vector>


class WorldMap //Declaration forward
{
public:
    WorldMap();
    // BackgroundMesh();
    void update();
    void draw();

private:
    //2D vector of Selectables
    std::vector<std::vector<Selectable*>> worldMap; 

    std::vector<Selectable> buildings;
    std::vector<Item> items;
};