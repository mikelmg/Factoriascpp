#pragma once
#include "globalParam.h"
#include "selectable.h"
#include "item.h"
#include "buildingA.h"
#include <raylib.h>
#include <vector>
#include <map>

using namespace std;

class WorldMap //Declaration forward
{
public:
    WorldMap();
    // BackgroundMesh();
    void update();
    void draw();
    void drag(Camera2D camera);

private:
    //2D vector of Selectables
    map<pair<int,int>, BuildingA> world;
    // vector<Conections> Conections;
};