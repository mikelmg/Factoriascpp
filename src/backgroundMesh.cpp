#include "headers/backgroundMesh.h"
#include <cmath>


// #include "../main.cpp"




void BackgroundMesh::Draw(Camera2D camera){
    for (int x = -MESH_SIZE_WIDTH/2; x < MESH_SIZE_WIDTH/2; x += MESH_DISTANCE){
        //Needs static cast to unsigned char for some reason
        DrawLine(x, -MESH_SIZE_HEIGHT/2, x, MESH_SIZE_HEIGHT/2, Color{MESHCOLOR.r, MESHCOLOR.g, MESHCOLOR.b, pow(MESH_TRANSPARENCY ,camera.zoom)});
    }

    for (int y = -MESH_SIZE_HEIGHT/2; y < MESH_SIZE_HEIGHT/2; y += MESH_DISTANCE){
        DrawLine(-MESH_SIZE_WIDTH/2, y, MESH_SIZE_HEIGHT/2, y, MESHCOLOR);
    }   
}
