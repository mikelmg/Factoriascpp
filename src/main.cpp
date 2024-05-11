#include "headers/itemA.h"
#include "headers/buildingA.h"
#include "headers/backgroundMesh.h"
#include <raylib.h>
#include <ctime>
#include <math.h>
#include <iostream>
#include <raymath.h>
using namespace std;


const int SCREENWIDTH = 800;
const int SCREENHEIGHT = 600;

int main()
{
    ItemA itemA1 = ItemA(10, 50, RED);
    ItemA itemA2 = ItemA(50, 50, GREEN);

    BuildingA buildingA1 = BuildingA(100, 100, 5);
    BuildingA buildingA2 = BuildingA(200, 200, 3);

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "My first RAYLIB program!");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        BackgroundMesh::Draw();

        itemA1.Update(GetFrameTime());
        itemA2.Update(GetFrameTime());

        float upSize = 6* sin( clock()/150.0f  );

        itemA1.Draw(upSize);
        itemA2.Draw(upSize);

        //Detecto si pincho edificio y actualizo su posición

        if( buildingA1.GetSelected() || (IsMouseButtonDown(MOUSE_LEFT_BUTTON) &&
            CheckCollisionPointRec(GetMousePosition(), Rectangle{buildingA1.GetPosition().x, buildingA1.GetPosition().y, BUILDING_SIZE, BUILDING_SIZE})) )
        {
            if (!buildingA1.GetSelected())
                buildingA1.Selected();
            //Mouse pos needs corrections
            buildingA1.SetPosition(Vector2SubtractValue(GetMousePosition(), BUILDING_SIZE/2));
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            buildingA1.NSelected();

        // buildingA1.Update(GetFrameTime());
        buildingA1.Draw();
        buildingA2.Draw();

        //Linea comparacion items
        DrawRectangle(5, 58, SCREENWIDTH, 2, BLUE);

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}