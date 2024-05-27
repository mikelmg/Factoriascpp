#include "headers/backgroundMesh.h"
#include <cmath>


// #include "../main.cpp"



//TODO max transparency
void BackgroundMesh::Draw(Camera2D camera){
    //FIXME Uses unsigned_cast
    unsigned char alpha = static_cast<unsigned char>(pow(MESH_TRANSPARENCY, camera.zoom));

    for (int x = -MESH_SIZE_WIDTH/2; x < MESH_SIZE_WIDTH/2; x += MESH_DISTANCE){
        //Needs static cast to unsigned char for some reason
        DrawLine(x, -MESH_SIZE_HEIGHT/2, x, MESH_SIZE_HEIGHT/2, Color{MESHCOLOR.r, MESHCOLOR.g, MESHCOLOR.b, alpha});
    }

    for (int y = -MESH_SIZE_HEIGHT/2; y < MESH_SIZE_HEIGHT/2; y += MESH_DISTANCE){
        DrawLine(-MESH_SIZE_WIDTH/2, y, MESH_SIZE_HEIGHT/2, y, Color{MESHCOLOR.r, MESHCOLOR.g, MESHCOLOR.b, alpha });
    }   
}
