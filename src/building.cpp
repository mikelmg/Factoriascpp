#include "headers/building.h"
#include <raymath.h>
#include <algorithm>
#include <string>
#include "headers/item.h"

//FIXME change to recipe
#define OUTPUT_FREQUENCY 0.4

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

    spawnTimer = 0;
    selected = false;
}

Building::~Building() {
    //Delete all connections from this building
    for (Connection* con: inConnections) {
        con->GetOrigin()->DeleteOutConnection(con);
        delete con;
    }
    inConnections.clear();

    for (Connection* con: outConnections) {
        con->GetTarget()->DeleteInConnection(con);
        delete con;
    }
    outConnections.clear();

    inventary.clear();

}

void Building::Production(const float &dt){

    //TODO Add class Recipes
        
    spawnTimer += dt;
    int amountProduced = spawnTimer / OUTPUT_FREQUENCY;

    if(spawnTimer >= OUTPUT_FREQUENCY){
        for(Connection* con: outConnections){//Every Conn
            for(int i = 1; i <= amountProduced; i++)//In case of lag
                AddItemsToConnection(con, spawnTimer-OUTPUT_FREQUENCY*i);//Is this order right?
        }
        spawnTimer=0;
    }

}


void Building::Draw()
{
    
    for (auto const& [key, val] : inventary){
        std::string text = Item::toString(key);
        
        text.append(": ");
        text.append(std::to_string(val));

        DrawText(text.data(), position.x, position.y -20, 20, GREEN);
    }

    Color color = this->color;
    if (selected){
        DrawSelection();
        color = ApplyBlueFilter(this->color);
    }
    DrawRectangle(position.x, position.y, BUILDING_SIZE, BUILDING_SIZE, color);
}

Vector2 Building::GetCenter()
{
    return Vector2(Vector2AddValue(position, BUILDING_SIZE/2) );
}

void Building::DrawSelection(){
    #define rectangle Rectangle{position.x-2, position.y-2, BUILDING_SIZE+2, BUILDING_SIZE+2}
    DrawRectangleRoundedLines(rectangle, 0.5, 4, 1, RED);
}


Rectangle Building::GetRectangle(){
    return Rectangle{position.x, position.y, BUILDING_SIZE, BUILDING_SIZE};
}

int Building::GetSize() {
    return BUILDING_SIZE;
}

SelectableTypes Building::GetSelectableType() {
    return BUILDING;
}


