#include "headers/item.h"
#include "headers/Building.h"
#include "headers/backgroundMesh.h"
#include "headers/globalParam.h"
#include "headers/worldMap.h"
#include <raylib.h>
#include <ctime>
#include <math.h>
#include <iostream>
#include <raymath.h>
#include <unordered_map>

using namespace std;

int main()
{

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Factores!");
    // SetTargetFPS(60);

    Camera2D camera = { 0 };
    camera.zoom = 1.0f;

    WorldMap worldMap = WorldMap(&camera);


    while (!WindowShouldClose())
    {

        // itemA1.Update(GetFrameTime());
        // itemA2.Update(GetFrameTime());

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

        BackgroundMesh::Draw(camera);

        float upSize = 6* sin( clock()/150.0f  );

        // itemA1.Draw(upSize);
        // itemA2.Draw(upSize);

        worldMap.Update(GetFrameTime());

        worldMap.Draw(upSize);

        //Linea comparacion items
        DrawRectangle(5, 58, SCREENWIDTH, 2, BLUE);
        
        EndMode2D();
        
        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}