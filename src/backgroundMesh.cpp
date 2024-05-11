#include "headers/backgroundMesh.h"
#include <raylib.h>

// #include "../main.cpp"

#define MESHCOLOR  CLITERAL(Color){ 200, 200, 200, 50 }   // Light Gray Transparent

const int SCREENWIDTH = 800;
const int SCREENHEIGHT = 600;


void BackgroundMesh::Draw(){
    for (int x = 0; x < SCREENWIDTH; x += MESH_DISTANCE){
        DrawLine(x, 0, x, SCREENHEIGHT, MESHCOLOR);
    }

    for (int y = 0; y < SCREENHEIGHT; y += MESH_DISTANCE){
        DrawLine(0, y, SCREENWIDTH, y, MESHCOLOR);
    }   
}
