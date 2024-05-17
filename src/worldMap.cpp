#include "headers/worldMap.h"
#include "headers/building.h"
#include <raymath.h>
#include <math.h>
#include <iostream>


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
    upSize = 6* sin( clock()/150.0f  );
    //Move buildings
    CheckNewBuildingSelected();
    CheckNewConnection();

    //Update Items
    for(Connection* con: connections){
        
        spawnTimer += GetFrameTime();
        if(spawnTimer >= 0.2){
            con->AddItem();
            spawnTimer=0;
        }
        con->Update(dt);
    }
}

void WorldMap::Draw()
{
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
    BuildingO->AddConnection(connections.back());
    BuildingT->AddConnection(connections.back());
}

//Pos Random
void WorldMap::AddBuilding(){
    world.push_back(new Building(100* GetRandomValue(0, 10), 100* GetRandomValue(0, 10), 5));
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
    //If left button and Selected
    else if ((IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) && conSelected){
        Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), *camera);
        //Check every building
        for (Building* building: world){
            if (CheckCollisionPointRec(mousePosition, 
                Rectangle{building->GetPosition().x, building->GetPosition().y, BUILDING_SIZE, BUILDING_SIZE}))
            {//Add new connection
                AddConnection(buildingConnSelected, building);
                conSelected = false;
            }
        }
    }
    //No button but connection selected
    else if (conSelected){
        DrawLineBezier(buildingConnSelected->GetCenter(), GetScreenToWorld2D(GetMousePosition(), *camera), 4, RED );
    }
    

}
