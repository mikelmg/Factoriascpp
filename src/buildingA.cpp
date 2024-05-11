#include "headers/buildingA.h"

BuildingA::BuildingA(){

    position.x = 20;
    position.y = 20;

    this->level = 1;
    this->color = LVLCOLORS[level];
}

BuildingA::BuildingA(int x, int y, int level){

    position.x = x;
    position.y = y;
    selected = false;

    this->level = level;
    this->color = LVLCOLORS[level];
}


void BuildingA::Draw()
{
    DrawRectangleGradientH(position.x, position.y, BUILDING_SIZE, BUILDING_SIZE, this->color, GOLD);
}
