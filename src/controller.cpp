#include "headers/controller.h"
#include <raymath.h>
#include <iostream>


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
//TODO ADD multiple connection when group selected
//TODO Simplify this
void Controller::CheckLeftClick(WorldMap* &worldMap)
{
    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) ){
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){//First frame
            buildingSelected = false;
            selectedBuilding->NSelected();
            
            if (!areaSelected) {
                for(Selectable* selectable: worldMap->GetSelectables()){
                    if( CheckCollisionPointRec(mousePosition, Rectangle{selectable->GetPosition().x, selectable->GetPosition().y, (float)selectable->GetSize(), (float)selectable->GetSize()})){
                        selectable->Selected();
                        selectedBuilding = selectable;
                        buildingSelected = true;
                    }
                }
            }
            else{
                for(Selectable* selectable: selectedVector) 
                    if( CheckCollisionPointRec(mousePosition, Rectangle{selectable->GetPosition().x, selectable->GetPosition().y, (float)selectable->GetSize(), (float)selectable->GetSize()})) buildingSelected = true;

            }
            if (!buildingSelected){
                if(areaSelected){
                    areaSelected = false;
                    for(Selectable* selectable: selectedVector) 
                        selectable->NSelected();
                    selectedVector.clear();
                }
                areaPreSelected = true;
                areaSelectionOriginPoint = mousePosition;
                mouseOriginalPosition = mousePosition;
            }
            else {


                for(Selectable* selectable: worldMap->GetSelectables()){
                    if( CheckCollisionPointRec(mousePosition, Rectangle{selectable->GetPosition().x, selectable->GetPosition().y, (float)selectable->GetSize(), (float)selectable->GetSize()})){
                        selectable->Selected();
                        selectedBuilding = selectable;
                        buildingSelected = true;
                    }
                }
                offset = Vector2Subtract(mousePosition, selectedBuilding->GetPosition());
            }

            mouseOriginalPosition = mousePosition;
        }
        else {
            if (buildingSelected){
                if (areaSelected){
                    for(Selectable* selectable: selectedVector) {
                        Vector2 offsetM = Vector2Subtract(mouseOriginalPosition, mousePosition);
                        selectable->SetPosition(Vector2Subtract(selectable->GetSelectedPosition(), offsetM));
                        selectable->UpdateConnections();
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
                for(Selectable* selectable: selectedVector) {
                    selectable->CenterPosition();
                    selectable->StoreInitialPosition();
                }
                buildingSelected = false;
            }
            else{
                selectedBuilding->CenterPosition();

                std::cout << mouseOriginalPosition.x << " " << mouseOriginalPosition.y << " " << mousePosition.x << " " << mousePosition.y << endl;
                if(mouseOriginalPosition.x == mousePosition.x && mouseOriginalPosition.y != mousePosition.y){
                    selectedBuilding->NSelected();
                    buildingSelected = false;
                }
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
        Vector2 position = {0,0};
        worldMap->AddBuilding(position);
    }

    if (IsKeyPressed(KEY_DELETE) && (buildingSelected || areaSelected)) {
        cout << "DELETING" << endl;
        for (Selectable* selectable: selectedVector) {
            if (selectable->GetSelectableType() == BUILDING)
                worldMap->EraseBuilding((Building*)selectable);
            else if (selectable->GetSelectableType() == MINE)
                worldMap->EraseMine((Mine*)selectable);
            // else if (selectable->GetSelectableType() == BUFFER)
            //     worldMap->EraseBuffer((Buffer*)selectable);
        }
        selectedVector.clear();
        buildingSelected = false;
    }
}


void Controller::CheckNewConnection(WorldMap* &worldMap){
    //If right button but not selected
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && !conSelected){
        //Check every building for that coordinates
        for(Selectable* selectable: worldMap->GetSelectables()){
            if (CheckCollisionPointRec(mousePosition, 
                Rectangle{selectable->GetPosition().x, selectable->GetPosition().y, (float)selectable->GetSize(), (float)selectable->GetSize()}))
            {
                conSelected = true;
                buildingConnSelected = selectable;
            }
        }
    }
    //If left/right button and Selected -> Create/Cancel Connection 
    else if ((IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) && conSelected){
        //Check every building
        for(Selectable* selectable: worldMap->GetSelectables()){
            //Building clicked -> Add/Delte conn
            if (CheckCollisionPointRec(mousePosition, 
                Rectangle{selectable->GetPosition().x, selectable->GetPosition().y, (float)selectable->GetSize(), (float)selectable->GetSize()})&& selectable->GetSelectableType() != MINE)
            {//Check if conn already exists
                int i = worldMap->ConnectionExists(buildingConnSelected, selectable);
                if(i==-1){//Add new connection   
                    worldMap->AddConnection(buildingConnSelected, selectable);
                    conSelected = false;
                    break;
                }
                else{//If a connection already exists -> delete it
                    worldMap->DeleteConnection(buildingConnSelected, selectable, i);
                }
            }            
        }
        //Outside any building -> Cancel connection
        conSelected = false;
    }
    //No button but connection selected->Draw curve
    else if (conSelected){
        for(Selectable* selectable: selectedVector ){
            DrawLineBezier(selectable->GetCenter(), GetScreenToWorld2D(GetMousePosition(), *camera), 4, PINK );
        }
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

    for(Selectable* selectable: worldMap->GetSelectables()){
        if( CheckCollisionRecs(selectionRec, selectable->GetRectangle())){
            selectable->Selected();
            selectedVector.push_back(selectable);
            selectable->StoreInitialPosition();
        }
    }
    
    return !selectedVector.empty();
}
