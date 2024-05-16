#include "headers/worldMap.h"
#include "headers/building.h"
#include <raymath.h>


WorldMap::WorldMap()
{
    world.push_back (new Building(100, 100, 5));
    world.push_back (new Building(200, 200, 3));
}

void WorldMap::Update()
{
    DrawLineBezier(world[0]->GetCenter(), world[1]->GetCenter(), 5, BLUE);
}

void WorldMap::Draw()
{
    for(Selectable* building: world) {
        building->Draw();
    }

}

void WorldMap::Drag(Camera2D camera)
{
    for(Selectable* building: world) {

        //Detecto si pincho edificio y actualizo su posición
        if( building->GetSelected() || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
            CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), 
                Rectangle{building->GetPosition().x, building->GetPosition().y, BUILDING_SIZE, BUILDING_SIZE})) )
        {
            building->Selected();
            //Mouse pos needs corrections
            building->SetPosition(Vector2SubtractValue(GetScreenToWorld2D(GetMousePosition(), camera), BUILDING_SIZE/2));
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            building->NSelected();
    }

}
