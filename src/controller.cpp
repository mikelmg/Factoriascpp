#include "headers/controller.h"
#include <raymath.h>

void DrawSelectionRectangle(Rectangle rectangle, Color color);

Controller::Controller(Camera2D* camera){
    this->camera = camera;
    conSelected = false;
    buildingSelected = false;
    areaSelected = false;
}

void Controller::UpdateMousePosition(){
    mousePosition = GetScreenToWorld2D(GetMousePosition(), *camera);
}

void Controller::Update(WorldMap* &worldMap){
    UpdateMousePosition();
    CheckNewBuildingSelected(worldMap);
    CheckKeyboard(worldMap);
    CheckNewConnection(worldMap);
}

void Controller::CheckNewBuildingSelected(WorldMap* &worldMap)
{
    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) ){
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            for(Building* building: worldMap->GetBuildings()) {
                
                if( CheckCollisionPointRec(mousePosition, Rectangle{building->GetPosition().x, building->GetPosition().y, BUILDING_SIZE, BUILDING_SIZE})){
                    building->Selected();
                    selectedBuilding = building;
                    buildingSelected = true;
                }
            }

            if (!buildingSelected){
                areaSelected = true;
                areaSelectionOriginPoint = mousePosition;
            }
        }
        else {
            if (buildingSelected){
                selectedBuilding->UpdateConnections();
                selectedBuilding->SetPosition(Vector2SubtractValue(mousePosition, BUILDING_SIZE/2));
            }
            else if (areaSelected){ //If not needed
                DrawSelectionRectangle(Rectangle{areaSelectionOriginPoint.x, areaSelectionOriginPoint.y, 
                    mousePosition.x- areaSelectionOriginPoint.x, mousePosition.y - areaSelectionOriginPoint.y}, WHITE);
            }
            
        }
    }
    else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
        if (buildingSelected){
            selectedBuilding->NSelected();
            selectedBuilding->CenterPosition();
            buildingSelected = false;
        }
        else if(areaSelected){

        }
    }

}

void Controller::CheckKeyboard(WorldMap* &worldMap){
    if(IsKeyPressed(KEY_B)){
        worldMap->AddBuilding();
    }
}


void Controller::CheckNewConnection(WorldMap* &worldMap){
    //If right button but not selected
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && !conSelected){
        //Check every building for that coordinates
        for (Building* building: worldMap->GetBuildings()){
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
        //Check every building
        for (Building* building: worldMap->GetBuildings()){
            //Building clicked -> Add/Delte conn
            if (CheckCollisionPointRec(mousePosition, 
                Rectangle{building->GetPosition().x, building->GetPosition().y, BUILDING_SIZE, BUILDING_SIZE}))
            {//Check if conn already exists
                int i = worldMap->ConnectionExists(buildingConnSelected, building);
                if(i==-1){//Add new connection   
                    worldMap->AddConnection(buildingConnSelected, building);
                    conSelected = false;
                    break;
                }
                else{//If a connection already exists -> delete it
                    worldMap->DeleteConnection(buildingConnSelected, building, i);
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

//FIXME    bad recangle
void DrawSelectionRectangle(Rectangle rectangle, Color color)
{
    DrawRectangleRec(rectangle, Color{ 115, 214, 249, 60});
}
