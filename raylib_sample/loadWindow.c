#include <stdio.h>
#include "raylib.h"

void display() {
    SetTraceLogLevel(LOG_WARNING);
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Barangay Management System");

    // Set the initial color
    Color textColor = RED;
    int colorChangeCounter = 0;

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose()) { // Main game loop
        // change color every 20 frames
        if (colorChangeCounter >= 30) {
            textColor = (Color){ GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255 };
            colorChangeCounter = 0;
        }
        colorChangeCounter++;

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // get the width of the text to center it
        int textWidth = MeasureText("Welcome to Barangay Management System", 30);
        int textWidth2 = MeasureText("Midterms Project", 20);
        DrawText("Welcome to Barangay Management System", (screenWidth - textWidth) / 2, 200, 30, textColor);
        DrawText("Midterms Project", (screenWidth - textWidth2) / 2, 250, 20, textColor);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context
}
