#pragma once

#include <raylib.h>
#include "worldMap.h"

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

//TODO MAKE DROPBOX PRETTIER
inline void recipeMenu(WorldMap* &worldMap, Vector2 mousePosition, bool editMode) {

    static Vector2 dropdownPosition;
    static bool show;
    editMode = true;
    static Building* buildingSelected;

    // if (editMode) GuiLock();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        // show = false;
        for (Building* building : worldMap->GetBuildings()) {
            if( CheckCollisionPointRec(mousePosition, Rectangle{building->GetPosition().x, building->GetPosition().y, (float)building->GetSize(), (float)building->GetSize()})){
                dropdownPosition = mousePosition;
                buildingSelected = building;
                show = true;
            }
        }
    }

    if(show){
        int recipe = buildingSelected->GetRecipe();
        GuiDropdownBox((Rectangle){ dropdownPosition.x, dropdownPosition.y, 140, 28 }, "No Recipe;RECIPE1;RECIPE2", 
            &recipe, editMode);
        if (recipe != buildingSelected->GetRecipe()) {
            buildingSelected->SetRecipe(recipe);
        }
        editMode = true;
    }

    
}
