#include "raylib.h"
#include <stdlib.h> // For srand and rand
#include <time.h>   // For time (to seed srand)
#include <perlin.h>

#define WORLD_SIZE 150
#define WORLD_HEIGHT 16

void generateWorld(int world[WORLD_SIZE][WORLD_HEIGHT][WORLD_SIZE], int seed);
void drawCube(int world[WORLD_SIZE][WORLD_HEIGHT][WORLD_SIZE], int x, int y, int z, Vector3 pos, Color color);

float perlinNoise(float x, float y, float z);
int BLOCK_COUNT;


// --- MAIN FUNCTION ---
int main(void)
{
    // Initialization
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Minecraft Clone");
    SetTargetFPS(120);
    DisableCursor();

    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 0.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    int world[WORLD_SIZE][WORLD_HEIGHT][WORLD_SIZE];
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
                    for (int y = 0; y < WORLD_HEIGHT; y++) {
                        for (int z = 0; z < WORLD_SIZE; z++) {
                            if (world[x][y][z] == 1) { // Draw a blue block for value 1
                                // Adjust position to center the world around the origin
                                Vector3 blockPos = { (float)x - WORLD_SIZE / 2.0f,
                                                     (float)y - WORLD_HEIGHT / 2.0f,
                                                     (float)z - WORLD_SIZE / 2.0f };
                                drawCube(world, x, y, z, blockPos, (Color){ 100, 100, 255, 255 });
                            }
                            // Blocks with value 0 (or any other value) are not drawn
                        }
                    }
                }
            }
            EndMode3D();

            DrawText("Welcome to Minecraft Clone!", 3, 3, 20, BLACK);
            DrawText(TextFormat("FPS: %i", GetFPS()), 3, 26, 20, BLACK);
            DrawText(TextFormat("Block Count: %i", BLOCK_COUNT), 3, 49, 20, BLACK);
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void generateWorld(int world[WORLD_SIZE][WORLD_HEIGHT][WORLD_SIZE], int seed) {
    srand(seed);

    float noise_val;

    for (int x = 0; x < WORLD_SIZE; x++) {
        for (int y = 0; y < WORLD_HEIGHT; y++) {
            for (int z = 0; z < WORLD_SIZE; z++) {
                noise_val = smooth2d(x*0.1, z*0.1, 5, seed);
                
                if (noise_val > (y-5)*0.1f) {
                    world[x][y][z] = 1;
                    BLOCK_COUNT += 1;
                } else {
                    world[x][y][z] = 0;
                }
            }
        }
    }
}

void drawCube(int world[WORLD_SIZE][WORLD_HEIGHT][WORLD_SIZE], int x, int y, int z, Vector3 pos, Color color) {
    Vector3 p1 = { pos.x-0.5f, pos.y-0.5f, pos.z-0.5f };
    Vector3 p2 = { pos.x+0.5f, pos.y-0.5f, pos.z-0.5f };
    Vector3 p3 = { pos.x+0.5f, pos.y-0.5f, pos.z+0.5f };
    Vector3 p4 = { pos.x-0.5f, pos.y-0.5f, pos.z+0.5f };
    Vector3 p5 = { pos.x-0.5f, pos.y+0.5f, pos.z-0.5f };
    Vector3 p6 = { pos.x+0.5f, pos.y+0.5f, pos.z-0.5f };
    Vector3 p7 = { pos.x+0.5f, pos.y+0.5f, pos.z+0.5f };
    Vector3 p8 = { pos.x-0.5f, pos.y+0.5f, pos.z+0.5f };

    // Helper lambda for bounds-safe access
    #define HAS_NEIGHBOR(dx, dy, dz) \
        (x + dx >= 0 && x + dx < WORLD_SIZE && \
         y + dy >= 0 && y + dy < WORLD_SIZE && \
         z + dz >= 0 && z + dz < WORLD_SIZE && \
         world[x + dx][y + dy][z + dz] == 1)

    // Bottom (-Y)
    if (!HAS_NEIGHBOR(0, -1, 0)) {
        Color newColor = { color.r*0.9, color.g*0.9, color.b*0.9, color.a};
        DrawTriangle3D(p1, p2, p3, newColor);
        DrawTriangle3D(p1, p3, p4, newColor);
    }

    // Top (+Y)
    if (!HAS_NEIGHBOR(0, 1, 0)) {
        Color newColor = { color.r, color.g, color.b, color.a};
        DrawTriangle3D(p5, p8, p7, newColor);
        DrawTriangle3D(p5, p7, p6, newColor);
    }

    // Front (+Z)
    if (!HAS_NEIGHBOR(0, 0, 1)) {
        Color newColor = { color.r*0.9, color.g, color.b, color.a};
        DrawTriangle3D(p4, p3, p7, newColor);
        DrawTriangle3D(p4, p7, p8, newColor);
    }

    // Back (-Z)
    if (!HAS_NEIGHBOR(0, 0, -1)) {
        Color newColor = { color.r, color.g*0.9, color.b, color.a};
        DrawTriangle3D(p2, p1, p5, newColor);
        DrawTriangle3D(p2, p5, p6, newColor);
    }

    // Left (-X)
    if (!HAS_NEIGHBOR(-1, 0, 0)) {
        Color newColor = { color.r, color.g, color.b*0.9, color.a};
        DrawTriangle3D(p1, p4, p8, newColor);
        DrawTriangle3D(p1, p8, p5, newColor);
    }

    // Right (+X)
    if (!HAS_NEIGHBOR(1, 0, 0)) {
        Color newColor = { color.r*0.9, color.g, color.b*0.9, color.a};
        DrawTriangle3D(p3, p2, p6, newColor);
        DrawTriangle3D(p3, p6, p7, newColor);
    }

    #undef HAS_NEIGHBOR
}
