#pragma once
#include "globalParam.h"
#include "selectable.h"
#include "item.h"
#include "building.h"
#include <raylib.h>
#include <vector>
#include <map>

using namespace std;

class WorldMap //Declaration forward
{
public:
    WorldMap();
    // BackgroundMesh();
    void Update();
    void Draw();
    void Drag(Camera2D camera);

private:
    //2D vector of Selectables
    map<pair<int,int>, Building> world;
    map<pair<int,int>, Building*> world2;

    // vector<Conections> Conections;
};