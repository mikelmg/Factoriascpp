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

Vector2 BuildingA::GetPosition(){
    return position;
}

void BuildingA::SetPosition(Vector2 position){
    this->position.x = position.x;
    this->position.y = position.y;
}

void BuildingA::Selected(){
    selected = true;
}

void BuildingA::NSelected(){
    selected = false;
}

bool BuildingA::GetSelected(){
    return selected; 
}