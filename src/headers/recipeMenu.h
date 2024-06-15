#pragma once

#include <raylib.h>
#include "worldMap.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

const float DROPDOWN_MENU_SIZE_X = 200;
const float DROPDOWN_MENU_SIZE_Y = 20;

void searchBuilding(WorldMap* worldMap, Vector2 mousePosition, Vector2& dropdownPosition, Building*& buildingSelected, bool& show);


//TODO MAKE DROPBOX PRETTIER
inline void recipeMenu(WorldMap* &worldMap, Vector2 mousePosition, bool editMode, Camera2D* camera) {

    static Vector2 dropdownPosition;
    static bool show;
    editMode = true;
    static Building* buildingSelected;
    int resultDropBox;

    // if (editMode) GuiLock();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (!show) {
            searchBuilding(worldMap, mousePosition, dropdownPosition, buildingSelected, show);
        }
        else{
            show = false;
            searchBuilding(worldMap, mousePosition, dropdownPosition, buildingSelected, show);
            cout << recipes.size() << endl;
            if(CheckCollisionPointRec(mousePosition, Rectangle{dropdownPosition.x, dropdownPosition.y, DROPDOWN_MENU_SIZE_X, DROPDOWN_MENU_SIZE_Y * (recipes.size()+1) + 5}))
                show = true;
        }
    }

    if(show){
        cout << "Offset: "<< camera->offset.x << ", " << camera->offset.y << endl;
        cout << "Target: "<< camera->target.x << ", " << camera->target.y << endl;
        Rectangle dropdownRectangle = { (dropdownPosition.x - camera->target.x) * camera->zoom + camera->offset.x, 
            (dropdownPosition.y- camera->target.y) * camera->zoom + camera->offset.y, DROPDOWN_MENU_SIZE_X, DROPDOWN_MENU_SIZE_Y };

        EndMode2D();
        resultDropBox = GuiDropdownBox( dropdownRectangle, recipeNames, buildingSelected->GetRecipe(), editMode);
        BeginMode2D(*camera);

        editMode = true;
    } 
}

inline void searchBuilding(WorldMap* worldMap, Vector2 mousePosition, Vector2& dropdownPosition, Building*& buildingSelected, bool& show) {
    for (Building* building : worldMap->GetBuildings()) {
        if( CheckCollisionPointRec(mousePosition, Rectangle{building->GetPosition().x, building->GetPosition().y, (float)building->GetSize(), (float)building->GetSize()})){
            dropdownPosition = mousePosition;
            buildingSelected = building;
            show = true;
        }
    }
}
