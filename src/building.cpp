#include "headers/building.h"
#include <raymath.h>
#include <algorithm>

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
}

void Building::Production(const float &dt){

    //TODO Implement Recipes
        
    spawnTimer += dt;
    int amountProduced = spawnTimer / OUTPUT_FREQUENCY;

    if(spawnTimer >= OUTPUT_FREQUENCY){
        for(Connection* con: outConnections){//Every Conn
            for(int i = 1; i <= amountProduced; i++)//In case of lag
                con->AddItem(spawnTimer-OUTPUT_FREQUENCY*i);//Is this order right?
        }
        spawnTimer=0;
    }

}


void Building::Draw()
{
    DrawRectangleGradientH(position.x, position.y, BUILDING_SIZE, BUILDING_SIZE, this->color, GOLD);
}

Vector2 Building::GetCenter()
{
    return Vector2(Vector2AddValue(position, BUILDING_SIZE/2) );
}

void Building::UpdateConnections()
{
    for(Connection* con: inConnections){
        con->UpdateControl();
        con->UpdateBezierLength();
    }

    for(Connection* con: outConnections){
        con->UpdateControl();
        con->UpdateBezierLength();
    }
}

void Building::AddInConnection(Connection* con){
    inConnections.push_back(con);
}

void Building::AddOutConnection(Connection* con){
    outConnections.push_back(con);
}

void Building::DeleteInConnection(Connection* con){
    // Find the element in the vector
    std::vector<Connection*>::iterator it = std::find(inConnections.begin(), inConnections.end(), con);

    // If the element is found, erase it from the vector
    if (it != inConnections.end()) {
        inConnections.erase(it);
    }
}

void Building::DeleteOutConnection(Connection* con){
    // Find the element in the vector
    std::vector<Connection*>::iterator it = std::find(outConnections.begin(), outConnections.end(), con);

    // If the element is found, erase it from the vector
    if (it != outConnections.end()) {
        outConnections.erase(it);
    }

    // inventary.inventary[0];
}


void Building::AddItemsToConnection(Connection* con, float position){
    con->AddItem(position);
}

void Building::AddItemsToInventary(ItemsType type, int amount){
    inventary[type]+=amount;
}

