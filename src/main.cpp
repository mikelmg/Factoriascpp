#include "headers/itemA.h"
#include "headers/buildingA.h"
#include "headers/backgroundMesh.h"
#include "headers/globalParam.h"
#include <raylib.h>
#include <ctime>
#include <math.h>
#include <iostream>
#include <raymath.h>
#include "rlgl.h"

using namespace std;



int main()
{
    ItemA itemA1 = ItemA(10, 50, RED);
    ItemA itemA2 = ItemA(50, 50, GREEN);

    BuildingA buildingA1 = BuildingA(100, 100, 5);
    BuildingA buildingA2 = BuildingA(200, 200, 3);

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "My first RAYLIB program!");
    SetTargetFPS(60);

    Camera2D camera = { 0 };
    camera.zoom = 1.0f;

    while (!WindowShouldClose())
    {

        itemA1.Update(GetFrameTime());
        itemA2.Update(GetFrameTime());

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            Vector2 delta = GetMouseDelta();
            delta = Vector2Scale(delta, -1.0f/camera.zoom);

            camera.target = Vector2Add(camera.target, delta);
        }

                float wheel = GetMouseWheelMove();
        if (wheel != 0)
        {
            // Get the world point that is under the mouse
            Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
            
            // Set the offset to where the mouse is
            camera.offset = GetMousePosition();

            // Set the target to match, so that the camera maps the world space point 
            // under the cursor to the screen space point under the cursor at any zoom
            camera.target = mouseWorldPos;

            // Zoom increment
            const float zoomIncrement = 0.125f;

            camera.zoom += (wheel*zoomIncrement);
            if (camera.zoom < zoomIncrement) camera.zoom = zoomIncrement;
        }

        BeginDrawing();

        BeginMode2D(camera);

        ClearBackground(BLACK);

        BackgroundMesh::Draw();

        float upSize = 6* sin( clock()/150.0f  );

        itemA1.Draw(upSize);
        itemA2.Draw(upSize);


        //Detecto si pincho edificio y actualizo su posición
        if( buildingA1.GetSelected() || (IsMouseButtonDown(MOUSE_LEFT_BUTTON) &&
            CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), 
                Rectangle{buildingA1.GetPosition().x, buildingA1.GetPosition().y, BUILDING_SIZE, BUILDING_SIZE})) )
        {
            if (!buildingA1.GetSelected())
                buildingA1.Selected();
            //Mouse pos needs corrections
            buildingA1.SetPosition(Vector2SubtractValue(GetScreenToWorld2D(GetMousePosition(), camera), BUILDING_SIZE/2));
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            buildingA1.NSelected();

        // buildingA1.Update(GetFrameTime());
        buildingA1.Draw();
        buildingA2.Draw();

        //Linea comparacion items
        DrawRectangle(5, 58, SCREENWIDTH, 2, BLUE);
        
        EndMode2D();
        
        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}