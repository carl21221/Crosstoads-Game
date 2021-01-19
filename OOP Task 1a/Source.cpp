#include <iostream>
#include "raylib.h"
#include "Game.h"
#include "Constants.h"

//Function Declarations
Texture2D GetTextureFromImagePath(const char* path, int cellSizeX, int cellSizeY);

using namespace std;

int main()
{

    const int gameSizeX = 600;
    const int gameSizeY = 640;
    InitWindow(gameSizeX, gameSizeY, "Frogger");
    SetTargetFPS(60);
    const int cellSize = (int)((float)GetScreenWidth() / (float)(SIZE));


    // Precache textures
    Texture2D texture_env_road = GetTextureFromImagePath("images/frogger_env_road.png", cellSize, cellSize);
    Texture2D texture_env_grass = GetTextureFromImagePath("images/frogger_env_grass.png", cellSize, cellSize);
    Texture2D texture_env_aqua = GetTextureFromImagePath("images/frogger_env_aqua.png", cellSize, cellSize);

    Texture2D texture_vehicle_car = GetTextureFromImagePath("images/frogger_car_left.png", cellSize, cellSize);
    Texture2D texture_vehicle_van_front = GetTextureFromImagePath("images/frogger_van_left_front.png", cellSize, cellSize);
    Texture2D texture_vehicle_van_back = GetTextureFromImagePath("images/frogger_van_left_back.png", cellSize, cellSize);
    Texture2D texture_vehicle_truck_left_front = GetTextureFromImagePath("images/frogger_truck_left_front.png", cellSize, cellSize);
    Texture2D texture_vehicle_truck_left_mid = GetTextureFromImagePath("images/frogger_truck_left_mid.png", cellSize, cellSize);
    Texture2D texture_vehicle_truck_left_back = GetTextureFromImagePath("images/frogger_truck_left_back.png", cellSize, cellSize);

    Texture2D texture_log_leftcap = GetTextureFromImagePath("images/frogger_log_left_cap.png", cellSize, cellSize);
    Texture2D texture_log_rightcap = GetTextureFromImagePath("images/frogger_log_right_cap.png", cellSize, cellSize);
    Texture2D texture_log_mid = GetTextureFromImagePath("images/frogger_log_mid.png", cellSize, cellSize);

    Texture2D texture_lillypad = GetTextureFromImagePath("images/frogger_lillypad.png", cellSize, cellSize);

    Texture2D texture_player_up = GetTextureFromImagePath("images/frogger_frog_up.png", cellSize, cellSize);
    Texture2D texture_player_down = GetTextureFromImagePath("images/frogger_frog_down.png", cellSize, cellSize);
    Texture2D texture_player_left = GetTextureFromImagePath("images/frogger_frog_left.png", cellSize, cellSize);
    Texture2D texture_player_right = GetTextureFromImagePath("images/frogger_frog_right.png", cellSize, cellSize);


    //Precache Sound 
    InitAudioDevice();
    Sound sound_splash = LoadSound("sound/frogger_splash.wav");
    Sound sound_jump1 = LoadSound("frogger_jump.wav");
    Sound sound_jump2 = LoadSound("frogger_jump2.wav");
    Sound sound_ambient = LoadSound("sound/frogger_streetnoise.mp3");
    Sound sound_splat = LoadSound("sound/frogger_splat.wav");
    //TODO: FIX MISSING SOUND ISSUES

    SetSoundVolume(sound_jump1, 0.5);

    SetMasterVolume(0.5);

    Game game;
    game.Setup();

    while (!WindowShouldClose())
    {
        game.GetTimer()->Tick();
        BeginDrawing();
        ClearBackground(DARKGRAY);
        if (!game.IsGameOver())
        {
            if (!IsSoundPlaying(sound_ambient))
            {
                SetSoundVolume(sound_ambient, 0.05);
                PlaySound(sound_ambient);
            }

            if (IsKeyPressed(KEY_RIGHT))  game.ProcessInput(KEY_RIGHT);
            PlaySound(sound_jump2);
            if (IsKeyPressed(KEY_LEFT))   game.ProcessInput(KEY_LEFT);
            PlaySound(sound_jump2);
            if (IsKeyPressed(KEY_UP))     game.ProcessInput(KEY_UP);
            PlaySound(sound_jump2);
            if (IsKeyPressed(KEY_DOWN))   game.ProcessInput(KEY_DOWN); 
            PlaySound(sound_jump2);

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

        //Draw Environment
        const auto envGrid = game.PrepareEnvGrid();
        for (int x = 0; x < SIZE; x++)
        {
            for (int y = 0; y < SIZE; y++)
            {
                int xPosition = x * cellSize;
                int yPosition = y * cellSize;
                switch (envGrid[y][x])
                {
                case AQUA:      DrawTexture(texture_env_aqua, xPosition, yPosition, WHITE);         break;
                case SAFEZONE:  DrawTexture(texture_env_grass, xPosition, yPosition, WHITE);        break;
                case ROAD:      DrawTexture(texture_env_road, xPosition, yPosition, WHITE);         break;
                case GOAL:      
                    Goal* thisGoal = game.GetGoalInstance(x+1, y+1);
                    if (thisGoal != nullptr)
                    {
                        if (thisGoal->IsTaken())
                        {
                            DrawTexture(texture_env_grass, xPosition, yPosition, WHITE); 
                            DrawTexture(texture_player_up, xPosition, yPosition, WHITE);
                        }
                        else  DrawTexture(texture_env_grass, xPosition, yPosition, WHITE);
                    }
                    break;
                }
            }
        }

        //Draw Moveables
        const auto movGrid = game.PrepareMovGrid();
        for (int x = 0; x < SIZE; x++)
        {
            for (int y = 0; y < SIZE; y++)
            {
                int xPosition = x * cellSize;
                int yPosition = y * cellSize;
                int leftTile = x - 1;
                int rightTile = x + 1;

                // Ensure the leftTile and rightTiles point to a valid tile
                if (leftTile < 0) leftTile = SIZE - 1;
                if (rightTile >= SIZE) rightTile = 0;

                switch (movGrid[y][x])
                {
                case CAR:  DrawTexture(texture_vehicle_car, xPosition, yPosition, WHITE); break;

                case VAN:
                    if (movGrid[y][leftTile] == VAN)
                        DrawTexture(texture_vehicle_van_back, xPosition, yPosition, WHITE);
                    else 
                        DrawTexture(texture_vehicle_van_front, xPosition, yPosition, WHITE);
                    break;

                case TRUCK:  
                    if (movGrid[y][leftTile] == TRUCK && (movGrid[y][rightTile] == TRUCK)) 
                        DrawTexture(texture_vehicle_truck_left_mid, xPosition, yPosition, WHITE);
                    else if (movGrid[y][leftTile] == TRUCK && (movGrid[y][rightTile] != TRUCK)) 
                        DrawTexture(texture_vehicle_truck_left_back, xPosition, yPosition, WHITE);
                    else if (movGrid[y][leftTile] != TRUCK && (movGrid[y][rightTile] == TRUCK)) 
                        DrawTexture(texture_vehicle_truck_left_front, xPosition, yPosition, WHITE);
                    else 
                        DrawTexture(texture_vehicle_truck_left_front, xPosition, yPosition, WHITE); break;
                    break;
                    
                case LOG:
                    if (movGrid[y][leftTile] == LOG && (movGrid[y][rightTile] == LOG))
                        DrawTexture(texture_log_mid, xPosition, yPosition, WHITE);
                    else if (movGrid[y][leftTile] == LOG && (movGrid[y][rightTile] != LOG))
                        DrawTexture(texture_log_rightcap, xPosition, yPosition, WHITE);
                    else if (movGrid[y][leftTile] != LOG && (movGrid[y][rightTile] == LOG))
                        DrawTexture(texture_log_leftcap, xPosition, yPosition, WHITE);
                    else
                        DrawTexture(texture_vehicle_truck_left_front, xPosition, yPosition, WHITE); break;
                    break;

                case LILLYPAD:
                    DrawTexture(texture_lillypad, xPosition, yPosition, WHITE);

                case 'x': break;
                default:        assert(false);
                }
            }
        }

        //Draw Player wih orientation
        if(game.GetPlayer()->GetDirection() == 'U')
            DrawTexture(texture_player_up, (game.GetPlayer()->GetX() - 1) * cellSize, (game.GetPlayer()->GetY() - 1) * cellSize, WHITE);
        else if (game.GetPlayer()->GetDirection() == 'D')
            DrawTexture(texture_player_down, (game.GetPlayer()->GetX() - 1) * cellSize, (game.GetPlayer()->GetY() - 1) * cellSize, WHITE);
        else if (game.GetPlayer()->GetDirection() == 'L')
            DrawTexture(texture_player_left, (game.GetPlayer()->GetX() - 1) * cellSize, (game.GetPlayer()->GetY() - 1) * cellSize, WHITE);
        else
            DrawTexture(texture_player_right, (game.GetPlayer()->GetX() - 1) * cellSize, (game.GetPlayer()->GetY() - 1) * cellSize, WHITE);

        // Draw HUD
        const int fontSize = 10;
        int currentLives = game.GetPlayer()->GetCurrentLives();
        Timer* mainTimer = game.GetTimer();
        std::cout << mainTimer->GetTimeAsString();
        DrawRectangle(0, gameSizeX, gameSizeX, gameSizeY - gameSizeX, BLACK);
        DrawText(TextFormat("Lives: %i", currentLives), (double)gameSizeX * 0.05, (double)gameSizeX + (fontSize / 2), fontSize, GREEN);
        DrawText(TextFormat("Goals Taken: %i/5", game.GetGoalTakenCount()), (double)gameSizeX * 0.5, (double)gameSizeX + (fontSize / 2), fontSize, GREEN);
        DrawText(TextFormat("Timer: %i:%i", game.GetTimer()->GetSeconds(), game.GetTimer()->GetMinutes()),
            (double)gameSizeX * 0.75, (double)gameSizeX + (fontSize / 2), fontSize, GREEN);

        EndDrawing();
 
        // --- game position checks ---

        if (game.CheckForPlayerDeathByVehicle())
        {
            if (!IsSoundPlaying(sound_splat))
            {
                SetSoundVolume(sound_splat, 1);
                PlaySound(sound_splat);
            }
        }
        if (game.CheckForPlayerDeathByAqua())
        {
            //if (!IsSoundPlaying(sound_splash))
            //{
            //    SetSoundVolume(sound_splash, 1);
            //    PlaySound(sound_splash);
            //}
        }
        game.CheckForPlayerWin();
        game.CheckForPlayerOnSticky();

        //---------------------------------
        if (game.GetPlayer()->GetCurrentLives() == 0) game.SetGameOver(true);

    }
    UnloadSound(sound_ambient);
    CloseWindow();
    return 0;
}


/// <summary>
/// Loads a file into an Image object, resizes it and outputs a Texture2D object
/// </summary>
/// <param name="path"></param>
/// <param name="cellSizeX"></param>
/// <param name="cellSizeY"></param>
/// <returns>Texture2D</returns>
Texture2D GetTextureFromImagePath(const char* path, int cellSizeX, int cellSizeY)
{
    Image newImage = LoadImage(path);
    ImageResize(&newImage, cellSizeX, cellSizeY);
    return LoadTextureFromImage(newImage);
}

