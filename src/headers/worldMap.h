#pragma once
#include "globalParam.h"
#include "selectable.h"
#include "item.h"
#include "building.h"
#include "connection.h"
#include "mine.h"
#include <raylib.h>
#include <vector>
#include <map>

using namespace std;

class WorldMap //Declaration forward
{
private:
    vector<Connection*> connections;                         //List of connections in the world    
    float upSize;                                            //Items draw() scale by this
    vector<Building*> buildings;                                 //List of Buildings in the world
    vector<Mine*> mines;
    vector<Selectable*> selectables;

public:
    WorldMap();

    void Update(float dt);                                                          // Updates world in each frame, buildings, connections etc
    void Draw();                                                                    // Calls everyones draw function

    void AddBuilding(Vector2 position);                                                             // Adds a buildings to the world
    void EraseBuilding(Building* building);
    void AddMine(Vector2 position);
    void EraseMine(Mine* mine);

    void AddConnection(Selectable* BuildingO, Selectable* BuildingT);                   // Creates a new connection between two given buildings
    int ConnectionExists(Selectable* buildingO, Selectable* buildingT);                 // Given two buildings, returns -1 if a connection between two given buildings does not exist or the index in the list of connections to it
    void DeleteConnection(int i);         // Given an index to the list of connections, delete that conn, handle memory
    void DeleteConnectionSelectable(Selectable* selectable);

    vector<Building*> GetBuildings();                                               // Get list of buildings
    vector<Mine*> GetMines();                                                       // Get list of buildings
    vector<Selectable*> GetSelectables();
    vector<Connection*> GetConnections();                                          // Get list of connections

    //TODO Copy and paste buildings
    //TODO delete buildings
    //TODO phantom building when add
    //TODO hash_map of buildings
    //TODO Add splitters/mergers

};