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


Color Selectable::ApplyBlueFilter(Color originalColor){
    Color blueFilteredColor;
    blueFilteredColor.r = originalColor.r * 0.5;  
    blueFilteredColor.g = originalColor.g * 0.5;  
    blueFilteredColor.b = originalColor.b * 3.0;  
    
    if (blueFilteredColor.r > 255) blueFilteredColor.r = 255;
    if (blueFilteredColor.g > 255) blueFilteredColor.g = 255;
    if (blueFilteredColor.b > 255) blueFilteredColor.b = 255;
    
    blueFilteredColor.a = originalColor.a;  
    
    return blueFilteredColor;
}


