#include "headers/building.h"

Building::Building(){

    position.x = 20;
    position.y = 20;

    this->level = 1;
    this->color = LVLCOLORS[level];
}

Building::Building(int x, int y, int level){

    position.x = x;
    position.y = y;
    selected = false;

    this->level = level;
    this->color = LVLCOLORS[level];
}


void Building::Draw()
{
    DrawRectangleGradientH(position.x, position.y, BUILDING_SIZE, BUILDING_SIZE, this->color, GOLD);
}
