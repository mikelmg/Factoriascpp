#pragma once

#include <raylib.h>
#include "worldMap.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

const float DROPDOWN_MENU_SIZE_X = 200;
const float DROPDOWN_MENU_SIZE_Y = 20;

void searchBuilding(WorldMap* worldMap, Vector2 mousePosition, Vector2& dropdownPosition, Building*& buildingSelected, bool& show);


//TODO MAKE DROPBOX PRETTIER
inline void recipeMenu(WorldMap* &worldMap, Vector2 mousePosition, bool editMode) {

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
            if(CheckCollisionPointRec(mousePosition, Rectangle{dropdownPosition.x, dropdownPosition.y, DROPDOWN_MENU_SIZE_X, DROPDOWN_MENU_SIZE_Y * (recipes.size()+1)}))
                show = true;
        }
    }

    if(show){
        Rectangle dropdownRectangle = { dropdownPosition.x, dropdownPosition.y, DROPDOWN_MENU_SIZE_X, DROPDOWN_MENU_SIZE_Y };
        resultDropBox = GuiDropdownBox(dropdownRectangle, recipeNames, buildingSelected->GetRecipe(), editMode);
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
