#include "headers/worldMap.h"
#include "headers/building.h"
#include <raymath.h>
#include <math.h>
#include <iostream>
#include <algorithm>


WorldMap::WorldMap()
{
    world.push_back (new Building(100, 100, 5));
    world.push_back (new Building(200, 200, 3));

    conSelected = false;
}

WorldMap::WorldMap(Camera2D* camera)
{
    world.push_back (new Building(100, 100, 5));
    world.push_back (new Building(200, 200, 3));

    this->camera = camera;

    // AddConnection(world[0], world[1]);

    conSelected = false;
}


void WorldMap::Update(float dt)
{
    upSize = MAX_ITEM_UPSCALE* sin( clock()/ITEM_UPSCALE_CYCLE_RATE  );
    //Move buildings
    CheckNewBuildingSelected();
    CheckNewConnection();
    CheckKeyboard();

    //Update Buildings
    for (Building* sel: world)
        sel->Production(dt);

    //Update Connections
    for(Connection* con: connections)
        con->Update(dt);
}

void WorldMap::Draw()
{
    DrawText("B for new Building", 200, 80, 30, RED);
    //Draw all buildings
    for(Selectable* building: world) {
        building->Draw();
    }

    //Draw all connections
    for(Connection* con: connections){
        con->Draw(upSize);
    }

    
}

void WorldMap::CheckNewBuildingSelected()
{
    for(Building* building: world) {
        
        Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), *camera);
        //Detecto si pincho edificio y actualizo su posición
        if( building->GetSelected() || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
            CheckCollisionPointRec(mousePosition, 
                Rectangle{building->GetPosition().x, building->GetPosition().y, BUILDING_SIZE, BUILDING_SIZE})) )
        {
            building->Selected();
            //Mouse pos needs corrections
            building->UpdateConnections();
            building->SetPosition(Vector2SubtractValue(mousePosition, BUILDING_SIZE/2));
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            building->NSelected();
    }

}


void WorldMap::AddConnection(Building* BuildingO, Building* BuildingT){
    connections.push_back(new Connection(BuildingO,BuildingT));
    BuildingO->AddOutConnection(connections.back());
    BuildingT->AddInConnection(connections.back());
}

//Pos Random
void WorldMap::AddBuilding(){
    world.push_back(new Building(50* GetRandomValue(0, 10), 50* GetRandomValue(0, 10), 5));
}


void WorldMap::CheckNewConnection(){
    //If right button but not selected
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && !conSelected){
        //Coordinates of mouse
        Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), *camera);
        //Check every building for that coordinates
        for (Building* building: world){
            if (CheckCollisionPointRec(mousePosition, 
                Rectangle{building->GetPosition().x, building->GetPosition().y, BUILDING_SIZE, BUILDING_SIZE}))
            {
                conSelected = true;
                buildingConnSelected = building;
            }
        }
    }
    //If left/right button and Selected -> Create/Cancel Connection 
    else if ((IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) && conSelected){
        Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), *camera);
        //Check every building
        for (Building* building: world){
            //Building clicked -> Add/Delte conn
            if (CheckCollisionPointRec(mousePosition, 
                Rectangle{building->GetPosition().x, building->GetPosition().y, BUILDING_SIZE, BUILDING_SIZE}))
            {//Check if conn already exists
                int i = ConnectionExists(buildingConnSelected, building);
                if(i==-1){//Add new connection   
                    AddConnection(buildingConnSelected, building);
                    conSelected = false;
                    break;
                }
                else{//If a connection already exists -> delete it
                    DeleteConnection(buildingConnSelected, building, i);
                }
            }            
        }
        //Outside any building -> Cancel connection
        conSelected = false;
    }
    //No button but connection selected->Draw curve
    else if (conSelected){
        DrawLineBezier(buildingConnSelected->GetCenter(), GetScreenToWorld2D(GetMousePosition(), *camera), 4, RED );
    }
    

}

//Check if 2 buildings already have a conn
int WorldMap::ConnectionExists(Building* buildingO, Building* buildingT){

    //Exists
    for (auto it = connections.begin(); it != connections.end(); ++it){
        if((*it)->GetOrigin() == buildingO && (*it)->GetTarget() == buildingT){
            return static_cast<int>(std::distance(connections.begin(), it)); 
        }
    }
    //Element is not found
    return -1;
}

//Delete conn, handle memory
void WorldMap::DeleteConnection(Building* buildingO, Building* buildingT, int i){
    delete connections[i];

    buildingO->DeleteOutConnection(connections[i]);
    buildingT->DeleteInConnection(connections[i]);

    connections.erase(connections.begin()+i);
}

void WorldMap::CheckKeyboard(){
    if(IsKeyPressed(KEY_B)){
        AddBuilding();
    }
}