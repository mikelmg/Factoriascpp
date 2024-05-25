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

    conSelected = false;
}

WorldMap::WorldMap(Camera2D* camera)
{
    world.push_back (new Building(100, 100, 5));
    world.push_back (new Building(200, 200, 3));

    this->camera = camera;

    // AddConnection(world[0], world[1]);

    conSelected = false;
}


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


void WorldMap::AddConnection(Building* BuildingO, Building* BuildingT){
    connections.push_back(new Connection(BuildingO,BuildingT));
    BuildingO->AddOutConnection(connections.back());
    BuildingT->AddInConnection(connections.back());
}

//Pos Random
void WorldMap::AddBuilding(){
    world.push_back(new Building(50* GetRandomValue(0, 10), 50* GetRandomValue(0, 10), 1));
}


//Check if 2 buildings already have a conn
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

//Delete conn, handle memory
void WorldMap::DeleteConnection(Building* buildingO, Building* buildingT, int i){
    delete connections[i];

    buildingO->DeleteOutConnection(connections[i]);
    buildingT->DeleteInConnection(connections[i]);

    connections.erase(connections.begin()+i);
}

WorldMap* WorldMap::GetWorldMap(){
    return this;
}

vector<Building*> WorldMap::GetBuildings(){
    return world;
}
