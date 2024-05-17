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

    addConnection();

}


void WorldMap::Update(float dt)
{
    upSize = 6* sin( clock()/150.0f  );
    //Move buildings
    Drag();

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

void WorldMap::Drag()
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

void WorldMap::addConnection(){
    //TODO PLACEHOLDER, addconections to a given building, conn
    connections.push_back(new Connection(world[0], world[1]));
    world[0]->AddConnection(connections[0]);
    world[1]->AddConnection(connections[0]);
}
