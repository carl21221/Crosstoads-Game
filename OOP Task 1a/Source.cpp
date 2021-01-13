#include "raylib.h"
#include "Game.h"
#include <iostream>
#include "Constants.h"

int main()
{
    int windowSize = 600;
    InitWindow(windowSize, windowSize, "Frogger");
    SetTargetFPS(60);
    
    Game game;
    game.Setup();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        if (!game.IsGameOver())
        {
            if (IsKeyPressed(KEY_RIGHT))  game.ProcessInput(KEY_RIGHT);
            if (IsKeyPressed(KEY_LEFT))   game.ProcessInput(KEY_LEFT);
            if (IsKeyPressed(KEY_UP))     game.ProcessInput(KEY_UP);
            if (IsKeyPressed(KEY_DOWN))   game.ProcessInput(KEY_DOWN);

            game.UpdateMoveableTiles();
        }
        else
        {
            while (game.IsGameOver())
            {
                BeginDrawing();
                ClearBackground(BLANK);
                DrawText(("GAME OVER"), 180, 280, 40, RED);
                DrawText(("| Press [SPACE] to restart | Press[ESC] to quit |"), 177, 320, 8, WHITE);
                EndDrawing();
                if (IsKeyPressed(SPACEBAR))
                {
                    game.SetGameOver(false);
                    game.GetPlayer()->ResetLives();
                    break;
                }
                else if (IsKeyPressed(ESCAPE))  CloseWindow();
            }
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
                    //case WALL:      DrawRectangle(xPosition, yPosition, cellSize, cellSize, DARKGREEN); break;
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
            }
        }
        EndDrawing();
        game.CheckForPlayerResponse();
        if (game.player.GetCurrentLives() == 0) game.SetGameOver(true);

    }
    CloseWindow();
    return 0;
}