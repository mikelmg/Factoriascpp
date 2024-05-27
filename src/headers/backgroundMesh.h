#pragma once
#include "globalParam.h"
#include <raylib.h>

#define MESHCOLOR  CLITERAL(Color){ 200, 200, 200, 10}   // Light Gray Transparent


const int MESH_TRANSPARENCY = 60;

const int MESH_DISTANCE = 20;
const int MESH_SIZE_WIDTH = 10000;
const int MESH_SIZE_HEIGHT = 10000;

class BackgroundMesh //Declaration forward
{
public:
    static void Draw(Camera2D camera);
private:

};