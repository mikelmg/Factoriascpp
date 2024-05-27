#pragma once
#include "globalParam.h"
#include "selectable.h"
#include "item.h"
#include "building.h"
#include "connection.h"
#include <raylib.h>
#include <vector>
#include <map>

using namespace std;

class WorldMap //Declaration forward
{
private:
    vector<Connection*> connections;                         //List of connections in the world    
    float upSize;                                            //Items draw() scale by this
    vector<Building*> world;                                 //List of Buildings in the world

public:
    WorldMap();

    void Update(float dt);                                                          // Updates world in each frame, buildings, connections etc
    void Draw();                                                                    // Calls everyones draw function

    void AddBuilding();                                                             // Adds a buildings to the world

    void AddConnection(Building* BuildingO, Building* BuildingT);                   // Creates a new connection between two given buildings
    int ConnectionExists(Building* buildingO, Building* buildingT);                 // Given two buildings, returns -1 if a connection between two given buildings does not exist or the index in the list of connections to it
    void DeleteConnection(Building* buildingO, Building* buildingT, int i);         // Given an index to the list of connections, delete that conn, handle memory

    vector<Building*> GetBuildings();                                               // Get list of buildings
    //TODO In DeleteConn buildings not needed prob
    //TODO Copy and paste buildings
    //TODO delete buildings
    //TODO phantom building when add
    //TODO hash_map of buildings
    //TODO Add splitters/mergers

};