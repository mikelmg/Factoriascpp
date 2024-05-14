#include "headers/worldMap.h"
#include "headers/buildingA.h"
#include <raymath.h>


WorldMap::WorldMap()
{
    world[{0,1}] = BuildingA(100, 100, 5);
    world[{1,1}] = BuildingA(200, 200, 3);
}

void WorldMap::update()
{

    
}

void WorldMap::draw()
{
    for (map<pair<int,int>, BuildingA>::iterator itr = world.begin(); itr != world.end(); itr++){
        itr->second.Draw();
    }

}

void WorldMap::drag(Camera2D camera)
{
    for (map<pair<int,int>, BuildingA>::iterator itr = world.begin(); itr != world.end(); itr++){

        //Detecto si pincho edificio y actualizo su posición
        if( itr->second.GetSelected() || (IsMouseButtonDown(MOUSE_LEFT_BUTTON) &&
            CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), 
                Rectangle{itr->second.GetPosition().x, itr->second.GetPosition().y, BUILDING_SIZE, BUILDING_SIZE})) )
        {
            if (!itr->second.GetSelected())
                itr->second.Selected();
            //Mouse pos needs corrections
            itr->second.SetPosition(Vector2SubtractValue(GetScreenToWorld2D(GetMousePosition(), camera), BUILDING_SIZE/2));
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            itr->second.NSelected();
    }

}
