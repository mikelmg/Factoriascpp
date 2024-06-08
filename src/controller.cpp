#include "headers/controller.h"
#include <raymath.h>
#include <iostream>
#include <algorithm> 


void DrawSelectionRectangle(Rectangle rectangle, Color color);
void PrintConnections(WorldMap* &worldMap);

Controller::Controller(Camera2D* camera){
    this->camera = camera;
    conSelected = false;
    areaPreSelected = false;
    activeSelection = false;
    conCreated = false;
}

void Controller::UpdateMousePosition(){
    mousePosition = GetScreenToWorld2D(GetMousePosition(), *camera);
}

void Controller::Update(WorldMap* &worldMap){
    UpdateMousePosition();
    CheckNewConnection(worldMap);
    CheckLeftClick(worldMap);
    CheckKeyboard(worldMap);

}

void Controller::CheckLeftClick(WorldMap* &worldMap)
{
    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !conCreated ){
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){//First frame
            LeftButtonPressed(worldMap);
        }
        else {
            if (activeSelection){
                for(Selectable* selectable: selectedVector) {
                    Vector2 offsetM = Vector2Subtract(mouseOriginalPosition, mousePosition);
                    selectable->SetPosition(Vector2Subtract(selectable->GetSelectedPosition(), offsetM));
                    selectable->UpdateConnections();
                }
            }
            if (areaPreSelected){ //FIXME No control of layer
                DrawSelectionRectangle();
            }
        }
    }
    else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
        if (conCreated)
            conCreated = false;
        else
            LeftButtonReleased(worldMap);
    }

}

//Only first frame of click
void Controller::LeftButtonPressed(WorldMap* &worldMap){

    if (!activeSelection) {
        //Check if click in any selectable
        activeSelection = SelectOnClick(worldMap);
    }
    else{
        bool out = true;
        //Check if click in any already selected
        for(Selectable* selectable: selectedVector){
            if( CheckCollisionPointRec(mousePosition, Rectangle{selectable->GetPosition().x, selectable->GetPosition().y, (float)selectable->GetSize(), (float)selectable->GetSize()})){
                offset = Vector2Subtract(mousePosition, selectable->GetPosition());
                out = false;
                break;
            }
        }
        if(out){
            ClearSelection();
            activeSelection = SelectOnClick(worldMap);
        }
    }
    if (!activeSelection){  //If click in area
        areaSelectionOriginPoint = mousePosition;
        areaPreSelected = true;
    }
    mouseOriginalPosition = mousePosition;   
}

void Controller::LeftButtonReleased(WorldMap* &worldMap){
    if (activeSelection) {
        for(Selectable* selectable: selectedVector) {
            selectable->StoreInitialPosition();
            selectable->CenterPosition();
        }
    }
    else if(areaPreSelected){
        areaPreSelected = false;
        activeSelection = SelectArea(worldMap);
    }
}

void Controller::CheckKeyboard(WorldMap* &worldMap){
    if(IsKeyPressed(KEY_B)){
        Vector2 position = {0,0};
        worldMap->AddBuilding(position);
    }

    if (IsKeyPressed(KEY_DELETE) && activeSelection) {
        cout << "DELETING" << endl;
        PrintConnections(worldMap);
        for (Selectable* selectable: selectedVector) {
            worldMap->EraseSelectable(selectable);
        }
        PrintConnections(worldMap);
        selectedVector.clear();
        activeSelection = false;
    }
}


void Controller::CheckNewConnection(WorldMap* &worldMap){
    //If right button but not selected
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && !conSelected){
        //Check every building for that coordinates

        bool out = true;
        //Check if click in any already selected
        for(Selectable* selectable: selectedVector){
            if( CheckCollisionPointRec(mousePosition, Rectangle{selectable->GetPosition().x, selectable->GetPosition().y, (float)selectable->GetSize(), (float)selectable->GetSize()})){
                out = false;
                break;
            }
        }
        if(out){
            ClearSelection();
            activeSelection = SelectOnClick(worldMap);
        }

        for(Selectable* selectable: worldMap->GetSelectables()){
            if( CheckCollisionPointRec(mousePosition, Rectangle{selectable->GetPosition().x, selectable->GetPosition().y, (float)selectable->GetSize(), (float)selectable->GetSize()})){
                activeSelection = true;
                conSelected = true;
                if (!selectable->GetSelected()){
                    selectable->Selected();
                    selectedVector.push_back(selectable);
                }
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
                CreateConnection(worldMap, selectable);

            }           
        }
        PrintConnections(worldMap);
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

void Controller::ClearSelection(){
    activeSelection = false;
    for(Selectable* selectable: selectedVector){
        selectable->NSelected();
    }
    selectedVector.clear();
}

//Selects a building if mouse collision
bool Controller::SelectOnClick(WorldMap* &worldMap){
    for(Selectable* selectable: worldMap->GetSelectables()){
        if( CheckCollisionPointRec(mousePosition, Rectangle{selectable->GetPosition().x, selectable->GetPosition().y, (float)selectable->GetSize(), (float)selectable->GetSize()})){
            selectable->StoreInitialPosition();
            selectable->Selected();
            selectedVector.push_back(selectable);
            return true;
        }
    }
    return false;
}

void Controller::CreateConnection(WorldMap* &worldMap, Selectable* target){
    bool newConnection = false;
    vector <int> index;

    for(Selectable* selectable: selectedVector){
        if(selectable != target){
            int aux = worldMap->ConnectionExists(selectable, target); //-1 if not exists
            if(aux==-1 ){//Add new connection
                worldMap->AddConnection(selectable, target);
                newConnection = true;
            }
        index.push_back(aux);
        }
    }

    if(!newConnection){
        std::sort(index.begin(), index.end(), greater<int>());
        for (int i = 0; i < index.size(); i++) {
            PrintConnections(worldMap);
            worldMap->DeleteConnection(index[i]);
        }
        PrintConnections(worldMap);

    }
    conCreated = true;
}

// Function template to check if all elements of containee are present in container
template <typename T>
bool contains_all_elements(const std::vector<T>& container, const std::vector<T>& containee) {
    // Count elements in container
    std::unordered_map<T, int> container_count;
    for (const T& element : container) {
        ++container_count[element];
    }

    // Check elements in containee
    for (const T& element : containee) {
        if (container_count[element] == 0) {
            return false;
        }
        --container_count[element];
    }

    return true;
}

void PrintConnections(WorldMap* &worldMap){
    int i = 0;

    for(Connection* con: worldMap->GetConnections()){
        std::cout << "Connection: " <<  i << ": ";
        std::cout << con->GetOrigin()->GetPosition().x << " " << con->GetOrigin()->GetPosition().y
            << " --> " << con->GetTarget()->GetPosition().x << " " << con->GetTarget()->GetPosition().y;
        std::cout << std::endl;
        i++;
    }
    std::cout << std::endl;
}