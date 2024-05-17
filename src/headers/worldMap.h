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

    // BackgroundMesh();
    void Update(float dt);
    void Draw();
    void CheckNewBuildingSelected();
    void AddConnection(Building* BuildingO, Building* BuildingT);
    void AddBuilding();
    void CheckNewConnection();
    //TODO add/delete buildings
    //TODO delete Connections
    //TODO Snap buildings to grid
private:

    void addConnection();
    //2D vector of Selectables
    vector<Building*> world;
    vector<Connection*> connections;
    Camera2D* camera;
    float spawnTimer;
    float upSize;

    // map<pair<int,int>, Building*> world2;
    Building* buildingConnSelected;
    bool conSelected;
    // vector<Conections> Conections;
};