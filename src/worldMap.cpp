#include "headers/worldMap.h"
#include "headers/building.h"
#include <raymath.h>
#include <math.h>
#include <iostream>
#include <algorithm>


WorldMap::WorldMap()
{
    buildings.push_back (new Building(100, 100, 5));
    buildings.push_back (new Building(200, 200, 3));
    buildings.push_back (new Building(200, 100, 2));
    buildings.push_back (new Building(100, 200, 1));

    mines.push_back (new Mine(Vector2{300, 0}, COBALT));

    selectables.push_back(buildings[0]);
    selectables.push_back(buildings[1]);
    selectables.push_back(buildings[2]);
    selectables.push_back(buildings[3]);

    selectables.push_back(mines[0]);
}

// Updates world in each frame, buildings, connections etc
void WorldMap::Update(float dt)
{
    upSize = MAX_ITEM_UPSCALE* sin( clock()/ITEM_UPSCALE_CYCLE_RATE  );

    for(Mine* mine: mines) {
        mine->Creation(dt);
    }

    //Update Buildings
    for (Building* sel: buildings)
        sel->Production(dt);

    //Update Connections
    for(Connection* con: connections)
        con->Update(dt);
}

// Calls everyones draw function
void WorldMap::Draw()
{
    DrawText("B for new Building", 200, 80, 30, RED);

    for(auto it = selectables.begin(); it != selectables.end(); ++it)
        (*it)->Draw();

    //Draw all connections
    for(auto it = connections.begin(); it != connections.end(); ++it)
        (*it)->Draw(upSize);
}

// Creates a new connection between two given buildings
void WorldMap::AddConnection(Selectable* BuildingO, Selectable* BuildingT){
    connections.push_back(new Connection(BuildingO,BuildingT));
    BuildingO->AddOutConnection(connections.back());
    BuildingT->AddInConnection(connections.back());
}

// Adds a buildings to the world
void WorldMap::AddBuilding(){
    buildings.push_back(new Building(50* GetRandomValue(0, 10), 50* GetRandomValue(0, 10), 1));
    selectables.push_back(buildings.back());
}


// Given two buildings, returns -1 if a connection between two given buildings does not exist or the index in the list of connections to it
int WorldMap::ConnectionExists(Selectable* buildingO, Selectable* buildingT){

    //Exists
    for (auto it = connections.begin(); it != connections.end(); ++it){
        if((*it)->GetOrigin() == buildingO && (*it)->GetTarget() == buildingT){
            return static_cast<int>(std::distance(connections.begin(), it)); 
        }
    }
    //Element is not found
    return -1;
}

// Given an index to the list of connections, delete that conn, handle memory
void WorldMap::DeleteConnection(Selectable* buildingO, Selectable* buildingT, int i){
    delete connections[i];

    buildingO->DeleteOutConnection(connections[i]);
    buildingT->DeleteInConnection(connections[i]);

    connections.erase(connections.begin()+i);
}

// Get list of buildings
vector<Building*> WorldMap::GetBuildings(){
    return buildings;
}

vector<Mine*> WorldMap::GetMines(){
    return mines;
}

vector<Selectable*> WorldMap::GetSelectables(){
    return selectables;
}
