#include "headers/selectable.h"
#include "headers/backgroundMesh.h"
#include <cmath> // Include this header for fmod

Vector2 Selectable::GetPosition(){
    return position;
}

void Selectable::SetPosition(Vector2 position){
    this->position.x = position.x;
    this->position.y = position.y;
}

void Selectable::Selected(){
    selected = true;
}

void Selectable::NSelected(){
    selected = false;
}

bool Selectable::GetSelected(){
    return selected; 
}

void Selectable::CenterPosition(){
    position.x = std::round(position.x / MESH_DISTANCE) * MESH_DISTANCE;
    position.y = std::round(position.y / MESH_DISTANCE) * MESH_DISTANCE;
}