#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Pucci Whitesnake");

    SetTargetFPS(60);              

    while (!WindowShouldClose())    
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("You say goodbye I say hello", 50, 50, 50, LIGHTGRAY);
        EndDrawing();
    }
    CloseWindow();        
    return 0;
}
