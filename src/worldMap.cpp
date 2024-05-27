#include "headers/worldMap.h"
#include "headers/building.h"
#include <raymath.h>
#include <math.h>
#include <iostream>
#include <algorithm>


WorldMap::WorldMap()
{
    world.push_back (new Building(100, 100, 5));
    world.push_back (new Building(200, 200, 3));
    world.push_back (new Building(200, 100, 2));
    world.push_back (new Building(100, 200, 1));
}

// Updates world in each frame, buildings, connections etc
void WorldMap::Update(float dt)
{
    upSize = MAX_ITEM_UPSCALE* sin( clock()/ITEM_UPSCALE_CYCLE_RATE  );

    //Update Buildings
    for (Building* sel: world)
        sel->Production(dt);

    //Update Connections
    for(Connection* con: connections)
        con->Update(dt);
}

// Calls everyones draw function
void WorldMap::Draw()
{
    DrawText("B for new Building", 200, 80, 30, RED);
    //Draw all buildings
    for(Selectable* building: world) {
        building->Draw();
    }

    //Draw all connections
    for(Connection* con: connections){
        con->Draw(upSize);
    }

    
}

// Creates a new connection between two given buildings
void WorldMap::AddConnection(Building* BuildingO, Building* BuildingT){
    connections.push_back(new Connection(BuildingO,BuildingT));
    BuildingO->AddOutConnection(connections.back());
    BuildingT->AddInConnection(connections.back());
}

// Adds a buildings to the world
void WorldMap::AddBuilding(){
    world.push_back(new Building(50* GetRandomValue(0, 10), 50* GetRandomValue(0, 10), 1));
}


// Given two buildings, returns -1 if a connection between two given buildings does not exist or the index in the list of connections to it
int WorldMap::ConnectionExists(Building* buildingO, Building* buildingT){

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
void WorldMap::DeleteConnection(Building* buildingO, Building* buildingT, int i){
    delete connections[i];

    buildingO->DeleteOutConnection(connections[i]);
    buildingT->DeleteInConnection(connections[i]);

    connections.erase(connections.begin()+i);
}

// Get list of buildings
vector<Building*> WorldMap::GetBuildings(){
    return world;
}
