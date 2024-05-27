#include "headers/controller.h"
#include <raymath.h>

void DrawSelectionRectangle(Rectangle rectangle, Color color);

Controller::Controller(Camera2D* camera){
    this->camera = camera;
    conSelected = false;
    buildingSelected = false;
    areaPreSelected = false;
    areaSelected = false;
}

void Controller::UpdateMousePosition(){
    mousePosition = GetScreenToWorld2D(GetMousePosition(), *camera);
}

void Controller::Update(WorldMap* &worldMap){
    UpdateMousePosition();
    CheckLeftClick(worldMap);
    CheckKeyboard(worldMap);
    CheckNewConnection(worldMap);
}

//TODO Simplify this
void Controller::CheckLeftClick(WorldMap* &worldMap)
{
    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) ){
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){//First frame
            if (!areaSelected) {
                for(Building* building: worldMap->GetBuildings()) {
                    if( CheckCollisionPointRec(mousePosition, Rectangle{building->GetPosition().x, building->GetPosition().y, BUILDING_SIZE, BUILDING_SIZE})){
                        building->Selected();
                        selectedBuilding = building;
                        buildingSelected = true;
                    }
                }
            }
            else{
                for(Building* building: selectedBuildingsVector) 
                    if( CheckCollisionPointRec(mousePosition, Rectangle{building->GetPosition().x, building->GetPosition().y, BUILDING_SIZE, BUILDING_SIZE})) buildingSelected = true;

            }
            if (!buildingSelected){
                if(areaSelected){
                    areaSelected = false;
                    for(Building* building: selectedBuildingsVector) 
                        building->NSelected();
                    selectedBuildingsVector.clear();
                }
                areaPreSelected = true;
                areaSelectionOriginPoint = mousePosition;
            }
            else {
                offset = Vector2Subtract(mousePosition, selectedBuilding->GetPosition());
            }

            mouseOriginalPosition = mousePosition;
        }
        else {
            if (buildingSelected){
                if (areaSelected){
                    for(Building* building: selectedBuildingsVector) {
                        Vector2 offsetM = Vector2Subtract(mouseOriginalPosition, mousePosition);
                        building->SetPosition(Vector2Subtract(building->GetSelectedPosition(), offsetM));
                        building->UpdateConnections();
                    }
                }
                else{
                    selectedBuilding->UpdateConnections();
                    selectedBuilding->SetPosition(Vector2Subtract(mousePosition, offset));
                }
            }
            else if (areaPreSelected){ //FIXME No control of layer
                DrawSelectionRectangle();
            }
            
        }
    }
    else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
        if (buildingSelected){
            if (areaSelected){
                for(Building* building: selectedBuildingsVector) {
                    building->CenterPosition();
                    building->StoreInitialPosition();
                }
                buildingSelected = false;
            }
            else{
                selectedBuilding->NSelected();
                selectedBuilding->CenterPosition();
                buildingSelected = false;
            }
        }
        else if(areaPreSelected){
            areaPreSelected = false;
            areaSelected = SelectArea(worldMap);
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


void Controller::DrawSelectionRectangle()
{
    #define color Color{ 115, 214, 249, 60 }
    
    int rectX = (areaSelectionOriginPoint.x < mousePosition.x) ? areaSelectionOriginPoint.x : mousePosition.x;
    int rectY = (areaSelectionOriginPoint.y < mousePosition.y) ? areaSelectionOriginPoint.y : mousePosition.y;
    int rectWidth = abs(mousePosition.x - areaSelectionOriginPoint.x);
    int rectHeight = abs(mousePosition.y - areaSelectionOriginPoint.y);

    DrawRectangle(rectX, rectY, rectWidth, rectHeight, color);
}


bool Controller::SelectArea(WorldMap* &worldMap){

    float rectX = (areaSelectionOriginPoint.x < mousePosition.x) ? areaSelectionOriginPoint.x : mousePosition.x;
    float rectY = (areaSelectionOriginPoint.y < mousePosition.y) ? areaSelectionOriginPoint.y : mousePosition.y;
    float rectWidth = abs(mousePosition.x - areaSelectionOriginPoint.x);
    float rectHeight = abs(mousePosition.y - areaSelectionOriginPoint.y);

    Rectangle selectionRec{rectX, rectY, rectWidth, rectHeight};

    for(Building* building: worldMap->GetBuildings()) {
        
        if( CheckCollisionRecs(selectionRec, building->GetRectangle())){
            building->Selected();
            selectedBuildingsVector.push_back(building);
            building->StoreInitialPosition();

        }
    }

    return !selectedBuildingsVector.empty();
}
