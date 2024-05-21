#include "headers/building.h"
#include <raymath.h>
#include <algorithm>




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

