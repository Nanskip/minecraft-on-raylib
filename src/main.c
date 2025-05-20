#include "raylib.h"

int main(void)
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Minecraft Clone");
    SetTargetFPS(60);

    int a = 0;

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        // TODO: Add your game logic here

        // Draw
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            DrawText("Welcome to Minecraft Clone!", 190 + a, 200, 20, BLACK);

            a++;
        }
        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
} 