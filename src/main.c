#include "raylib.h"
#include <stdlib.h> // For srand and rand
#include <time.h>   // For time (to seed srand)

#define WORLD_SIZE 10

void generateWorld(int world[WORLD_SIZE][WORLD_SIZE][WORLD_SIZE], int seed);
float perlinNoise(float x, float y, float z);


// --- MAIN FUNCTION ---
int main(void)
{
    // Initialization
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Minecraft Clone");
    SetTargetFPS(60);
    DisableCursor();

    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 0.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    int world[WORLD_SIZE][WORLD_SIZE][WORLD_SIZE];
    generateWorld(world, (int)time(NULL));

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        UpdateCamera(&camera, CAMERA_FREE);

        // Draw
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
            {
                for (int x = 0; x < WORLD_SIZE; x++) {
                    for (int y = 0; y < WORLD_SIZE; y++) {
                        for (int z = 0; z < WORLD_SIZE; z++) {
                            if (world[x][y][z] == 1) { // Draw a blue block for value 1
                                // Adjust position to center the world around the origin
                                Vector3 blockPos = { (float)x - WORLD_SIZE / 2.0f,
                                                     (float)y - WORLD_SIZE / 2.0f,
                                                     (float)z - WORLD_SIZE / 2.0f };
                                DrawCube(blockPos, 1.0f, 1.0f, 1.0f, BLUE);
                                DrawCubeWires(blockPos, 1.0f, 1.0f, 1.0f, DARKBLUE);
                            } else if (world[x][y][z] == 2) { // Draw a red block for value 2
                                Vector3 blockPos = { (float)x - WORLD_SIZE / 2.0f,
                                                     (float)y - WORLD_SIZE / 2.0f,
                                                     (float)z - WORLD_SIZE / 2.0f };
                                DrawCube(blockPos, 1.0f, 1.0f, 1.0f, RED);
                                DrawCubeWires(blockPos, 1.0f, 1.0f, 1.0f, ORANGE);
                            }
                            // Blocks with value 0 (or any other value) are not drawn
                        }
                    }
                }
            }
            EndMode3D();

            DrawText("Welcome to Minecraft Clone!", 3, 3, 20, BLACK);
            DrawText(TextFormat("FPS: %i", GetFPS()), 3, 26, 20, BLACK);
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void generateWorld(int world[WORLD_SIZE][WORLD_SIZE][WORLD_SIZE], int seed) {
    srand(seed);

    for (int x = 0; x < WORLD_SIZE; x++) {
        for (int y = 0; y < WORLD_SIZE; y++) {
            for (int z = 0; z < WORLD_SIZE; z++) {
                float noise_val = perlinNoise((float)x * 0.1f, (float)y * 0.1f, (float)z * 0.1f);
                
                if (noise_val > 0.6f) {
                    world[x][y][z] = 2;
                } else if (noise_val > 0.3f) {
                    world[x][y][z] = 1;
                } else {
                    world[x][y][z] = 0;
                }
            }
        }
    }
}

float perlinNoise(float x, float y, float z) {
    unsigned int hash_val = (unsigned int)(x * 73856093) ^ (unsigned int)(y * 19349663) ^ (unsigned int)(z * 83492791);
    
    return (float)((hash_val % 100000) / 100000.0f);
}