#include "headers/worldMap.h"
#include "headers/building.h"
#include "headers/recipe.h"
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

    readRecipesFile();
    printRecipes();
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
    DrawText("Supr to Delete", 200, 120, 30, GREEN);
    DrawText("RClick for new Connection", 200, 160, 30, BLUE);
    DrawText("You can use selections to move/create connections/delete", 600, 80, 20, PINK);

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
void WorldMap::AddBuilding(Vector2 position){
    buildings.push_back(new Building(50* GetRandomValue(0, 10), 50* GetRandomValue(0, 10), 1));
    selectables.push_back(buildings.back());
}

void WorldMap::EraseSelectable(Selectable* sel){

    DeleteConnectionSelectable(sel); //Handles conn memory

    auto it = find(selectables.begin(), selectables.end(), sel);
    if(it != selectables.end()){
        selectables.erase(it);
    }
    
    if(sel->GetSelectableType() == BUILDING){
        auto it = std::find(buildings.begin(), buildings.end(), sel);
        if(it != buildings.end()){
            buildings.erase(it);
        }
    }
    else if (sel->GetSelectableType() == MINE){
        auto it = std::find(mines.begin(), mines.end(), sel);
        if(it != mines.end()){
            mines.erase(it);
        }
    }

    delete sel;
}


void WorldMap::AddMine(Vector2 position){
    position = {(float)50* GetRandomValue(0, 10), (float)50* GetRandomValue(0, 10)};
    mines.push_back(new Mine(position, COBALT));
    selectables.push_back(mines.back());
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
void WorldMap::DeleteConnection(int i){

    connections[i]->GetOrigin()->DeleteOutConnection(connections[i]);
    connections[i]->GetTarget()->DeleteInConnection(connections[i]);

    delete connections[i];
    connections.erase(connections.begin()+i);

}

void WorldMap::DeleteConnectionSelectable(Selectable* selectable) {
    for (auto connectionIterator = connections.begin(); connectionIterator != connections.end();) {
        Connection* connection = *connectionIterator;
        if (connection->GetOrigin() == selectable || connection->GetTarget() == selectable) {
            connection->GetOrigin()->DeleteOutConnection(connection);
            connection->GetTarget()->DeleteInConnection(connection);
            connectionIterator = connections.erase(connectionIterator);
            delete connection;
        } else {
            ++connectionIterator;
        }
    }
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

vector<Connection*> WorldMap::GetConnections(){
    return connections;
}
