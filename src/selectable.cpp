#include "headers/selectable.h"
#include "headers/backgroundMesh.h"
#include <cmath> // Include this header for fmod
#include <algorithm>

// Rounds position of the object to snap to grid
void Selectable::CenterPosition(){
    position.x = std::round(position.x / MESH_DISTANCE) * MESH_DISTANCE;
    position.y = std::round(position.y / MESH_DISTANCE) * MESH_DISTANCE;
}

// Given a color, returns it with a blue filter
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

// Sets selectedPosition to position
void Selectable::StoreInitialPosition(){
    selectedPosition = position;
}

// Get Original position when dragged
Vector2 Selectable::GetSelectedPosition(){
    return selectedPosition;
}

// Get Coordinates in the world (top left corner of the object)
Vector2 Selectable::GetPosition(){
    return position;
}

// Set position to a given Vector2
void Selectable::SetPosition(Vector2 position){
    this->position.x = position.x;
    this->position.y = position.y;
}

// Set selected to true
void Selectable::Selected(){
    selected = true;
}

// Set selected to false
void Selectable::NSelected(){
    selected = false;
}

// Get if it is currently been selected (to move, act, etc)
bool Selectable::GetSelected(){
    return selected; 
}

void Selectable::AddItemsToConnection(Connection* con, float position){
    con->AddItem(position);
    inventary[COBALT]--;
}

void Selectable::AddItemsToInventary(ItemsType type, int amount){
    inventary[type]+=amount;
}

void Selectable::UpdateConnections()
{
    for(Connection* con: inConnections){
        con->UpdateControl();
        con->UpdateBezierLength();
    }

    for(Connection* con: outConnections){
        con->UpdateControl();
        con->UpdateBezierLength();
    }
}

void Selectable::AddInConnection(Connection* con){
    inConnections.push_back(con);
}

void Selectable::AddOutConnection(Connection* con){
    outConnections.push_back(con);
}

void Selectable::DeleteInConnection(Connection* con){
    // Find the element in the vector
    std::vector<Connection*>::iterator it = std::find(inConnections.begin(), inConnections.end(), con);

    // If the element is found, erase it from the vector
    if (it != inConnections.end()) {
        inConnections.erase(it);
    }
}

void Selectable::DeleteOutConnection(Connection* con){
    // Find the element in the vector
    std::vector<Connection*>::iterator it = std::find(outConnections.begin(), outConnections.end(), con);

    // If the element is found, erase it from the vector
    if (it != outConnections.end()) {
        outConnections.erase(it);
    }

    // inventary.inventary[0];
}

Rectangle Selectable::GetRectangle(){
    return Rectangle{position.x, position.y, 40, 40};
}


