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
    void LeftButtonPressed(WorldMap* &worldMap);
    void LeftButtonReleased(WorldMap* &worldMap);
    void CheckNewConnection(WorldMap* &worldMap);
    void DrawSelectionRectangle();
    bool SelectArea(WorldMap* &worldMap);
    void ClearSelection();
    bool SelectOnClick(WorldMap* &worldMap);
    void CreateConnection(WorldMap* &worldMap, Selectable* target); //FIXME Position of origin changes

private:
    Camera2D* camera;
    Vector2 mousePosition;
    std::vector <Selectable*> selectedVector;
    Vector2 areaSelectionOriginPoint;
    Vector2 mouseOriginalPosition;
    Vector2 offset;
    bool conSelected;
    bool areaPreSelected;
    bool activeSelection;
    bool conCreated;

};