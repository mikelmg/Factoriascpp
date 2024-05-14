#include "headers/backgroundMesh.h"


// #include "../main.cpp"

#define MESHCOLOR  CLITERAL(Color){ 200, 200, 200, 10}   // Light Gray Transparent

const int MESH_TRANSPARENCY = 20;

const int MESH_SIZE_WIDTH = 10000;
const int MESH_SIZE_HEIGHT = 10000;


void BackgroundMesh::Draw(Camera2D camera){
    for (int x = -MESH_SIZE_WIDTH/2; x < MESH_SIZE_WIDTH/2; x += MESH_DISTANCE){
        //Needs static cast to unsigned char for some reason
        DrawLine(x, -MESH_SIZE_HEIGHT/2, x, MESH_SIZE_HEIGHT/2, Color{MESHCOLOR.r, MESHCOLOR.g, MESHCOLOR.b, static_cast<unsigned char>(MESH_TRANSPARENCY + (camera.zoom*100))});
    }

    for (int y = -MESH_SIZE_HEIGHT/2; y < MESH_SIZE_HEIGHT/2; y += MESH_DISTANCE){
        DrawLine(-MESH_SIZE_WIDTH/2, y, MESH_SIZE_HEIGHT/2, y, MESHCOLOR);
    }   
}
