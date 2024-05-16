#include "headers/worldMap.h"
#include "headers/building.h"
#include <raymath.h>

#include <iostream>


WorldMap::WorldMap()
{
    world.push_back (new Building(100, 100, 5));
    world.push_back (new Building(200, 200, 3));
}

WorldMap::WorldMap(Camera2D* camera)
{
    world.push_back (new Building(100, 100, 5));
    world.push_back (new Building(200, 200, 3));

    this->camera = camera;

    //PLACEHOLDER
    connections.push_back(new Connection(world[0], world[1]));
}


void WorldMap::Update(float dt)
{
    //Move buildings
    Drag();

    //Update Items
    for(Connection* con: connections){

        spawnTimer += GetFrameTime();
        if(spawnTimer >= 1){
            con->AddItem();
            spawnTimer=0;
        }
        con->Update(dt);
    }
}

void WorldMap::Draw(float upSize)
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

void WorldMap::Drag()
{
    for(Selectable* building: world) {
        
        //Detecto si pincho edificio y actualizo su posición
        if( building->GetSelected() || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
            CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), *camera), 
                Rectangle{building->GetPosition().x, building->GetPosition().y, BUILDING_SIZE, BUILDING_SIZE})) )
        {
            building->Selected();
            //Mouse pos needs corrections
            building->SetPosition(Vector2SubtractValue(GetScreenToWorld2D(GetMousePosition(), *camera), BUILDING_SIZE/2));
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            building->NSelected();
    }

}
