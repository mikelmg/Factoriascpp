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
    void Draw(float upSize);
    void Drag();
    //TODO add buildings
    //TODO add Connections
private:
    //2D vector of Selectables
    vector<Selectable*> world;
    vector<Connection*> connections;
    Camera2D* camera;
    float spawnTimer;
    // map<pair<int,int>, Building*> world2;

    // vector<Conections> Conections;
};