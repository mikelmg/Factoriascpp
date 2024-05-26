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
    void CheckLeftClick(WorldMap* &worldMap);
    void CheckNewConnection(WorldMap* &worldMap);
    void DrawSelectionRectangle();
    bool SelectArea(WorldMap* &worldMap);

private:
    Camera2D* camera;
    Vector2 mousePosition;
    Building* buildingConnSelected;
    std::vector <Building*> selectedBuildingsVector;
    Building* selectedBuilding;
    Vector2 areaSelectionOriginPoint;
    Vector2 mouseOriginalPosition;
    Vector2 offset;
    bool buildingSelected;
    bool conSelected;
    bool areaPreSelected;
    bool areaSelected;

};