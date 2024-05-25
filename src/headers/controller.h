#pragma once
#include "worldMap.h"
#include <raylib.h>

const int LINE_SPACING = 10;      

class Controller{
public:
    Controller(Camera2D* camera);
    void UpdateMousePosition();
    void Update(WorldMap* &worldMap);
    void CheckKeyboard(WorldMap* &worldMap);
    void CheckNewBuildingSelected(WorldMap* &worldMap);
    void CheckNewConnection(WorldMap* &worldMap);


private:
    Camera2D* camera;
    Vector2 mousePosition;
    Building* buildingConnSelected;
    Building* selectedBuilding;
    Vector2 areaSelectionOriginPoint;
    bool buildingSelected;
    bool conSelected;
    bool areaSelected;
};