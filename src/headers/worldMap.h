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
public:
    WorldMap();
    WorldMap(Camera2D* camera);

    void Update(float dt);
    void Draw();
    void AddConnection(Building* BuildingO, Building* BuildingT);
    void AddBuilding();
    WorldMap* GetWorldMap();
    vector<Building*> GetBuildings();
    int ConnectionExists(Building* buildingO, Building* buildingT);
    void DeleteConnection(Building* buildingO, Building* buildingT, int i);

    //TODO Select and move multiple buildings
    //TODO Copy and paste buildings
    //TODO delete buildings
    //TODO phantom building when add
private:

    //2D vector of Selectables
    vector<Connection*> connections;
    Camera2D* camera;
    float upSize;
    vector<Building*> world;
    // map<pair<int,int>, Building*> world2;
    bool conSelected;
    // vector<Connections> Connections;
};