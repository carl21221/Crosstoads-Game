#include "raylib.h"
#include "Game.h"
#include <iostream>
#include "Constants.h"

int main()
{
    InitWindow(600, 600, "Frogger");
    SetTargetFPS(60);

    Game game;
    game.Setup();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        if (game.IsRunning())
        {
            if (IsKeyPressed(KEY_RIGHT))  game.ProcessInput(KEY_RIGHT);
            if (IsKeyPressed(KEY_LEFT))   game.ProcessInput(KEY_LEFT);
            if (IsKeyPressed(KEY_UP))     game.ProcessInput(KEY_UP);
            if (IsKeyPressed(KEY_DOWN))   game.ProcessInput(KEY_DOWN);

            game.UpdateMoveableTiles();
        }
        else
        {
            DrawText("TODO: Why did the game end?", 610, 10, 20, LIGHTGRAY);
        }

        const int cellSize = (int)((float)GetScreenHeight() / (float)(SIZE));

        const auto grid = game.PrepareGrid();

        for (int x = 0; x < SIZE; x++)
        {
            for (int y = 0; y < SIZE; y++)
            {
                int xPosition = x * cellSize;
                int yPosition = y * cellSize;

                switch (grid[y][x])
                {
                    case FLOOR:     DrawRectangle(xPosition, yPosition, cellSize, cellSize, DARKGRAY);  break;
                    case WALL:      DrawRectangle(xPosition, yPosition, cellSize, cellSize, DARKGREEN); break;
                    case PLAYER:    DrawRectangle(xPosition, yPosition, cellSize, cellSize, GREEN);     break;
                    case AQUA:      DrawRectangle(xPosition, yPosition, cellSize, cellSize, SKYBLUE);   break;
                    case SAFEZONE:  DrawRectangle(xPosition, yPosition, cellSize, cellSize, PINK);      break;
                    case ROAD:      DrawRectangle(xPosition, yPosition, cellSize, cellSize, BLACK);     break;
                    case GOAL:      DrawRectangle(xPosition, yPosition, cellSize, cellSize, GOLD);      break;

                    case CAR:       DrawRectangle(xPosition, yPosition, cellSize, cellSize, RED);       break; 
                    case LOG:       DrawRectangle(xPosition, yPosition, cellSize, cellSize, BROWN);     break;
                    case VAN:       DrawRectangle(xPosition, yPosition, cellSize, cellSize, WHITE);     break;
                    case TRUCK:     DrawRectangle(xPosition, yPosition, cellSize, cellSize, LIGHTGRAY); break;
                    default:        assert(false);
                }
                //DrawRectangleLines(x * cellSize, y * cellSize, cellSize, cellSize, LIGHTGRAY);

            }
        }
        EndDrawing();
        game.CheckForPlayerResponse();
        game.CheckForPlayerResponse();
    }
    CloseWindow();
    return 0;
}