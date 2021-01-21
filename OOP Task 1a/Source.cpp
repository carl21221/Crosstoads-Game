#include <iostream>
#include <fstream>
#include "raylib.h"
#include "Game.h"
#include "Constants.h"


// -----------------------------------------------------------
//
//          FIX PLAYER RESPONSE TO WIN AND DEATH SCREENS
//
// -----------------------------------------------------------


//Source Header - Function Declarations
const Texture2D GetTextureFromImagePath(const char* path, const int& cellSizeX, const int& cellSizeY);
int GetHighscoreFromFile();
int CalculateHighscore(const int& time, const int& livesLeft);
void SaveScoreToFile(const int& score);

using namespace std;

int main()
{
    const int gameSizeX = 600;
    const int gameSizeY = 640; // Allow for HUD underneath at the very bottom
    InitWindow(gameSizeX, gameSizeY, "Crosstoads");
    SetTargetFPS(60);
    const int cellSize = (int)((float)GetScreenWidth() / (float)(SIZE));

    // Precache textures
    const Texture2D texture_env_road = GetTextureFromImagePath("images/frogger_env_road.png", cellSize, cellSize);
    const Texture2D texture_env_grass = GetTextureFromImagePath("images/frogger_env_grass.png", cellSize, cellSize);
    const Texture2D texture_env_aqua = GetTextureFromImagePath("images/frogger_env_aqua.png", cellSize, cellSize);
    const Texture2D texture_vehicle_car = GetTextureFromImagePath("images/frogger_car_left.png", cellSize, cellSize);
    const Texture2D texture_vehicle_van_front = GetTextureFromImagePath("images/frogger_van_left_front.png", cellSize, cellSize);
    const Texture2D texture_vehicle_van_back = GetTextureFromImagePath("images/frogger_van_left_back.png", cellSize, cellSize);
    const Texture2D texture_vehicle_truck_left_front = GetTextureFromImagePath("images/frogger_truck_left_front.png", cellSize, cellSize);
    const Texture2D texture_vehicle_truck_left_mid = GetTextureFromImagePath("images/frogger_truck_left_mid.png", cellSize, cellSize);
    const Texture2D texture_vehicle_truck_left_back = GetTextureFromImagePath("images/frogger_truck_left_back.png", cellSize, cellSize);
    const Texture2D texture_log_leftcap = GetTextureFromImagePath("images/frogger_log_left_cap.png", cellSize, cellSize);
    const Texture2D texture_log_rightcap = GetTextureFromImagePath("images/frogger_log_right_cap.png", cellSize, cellSize);
    const Texture2D texture_log_mid = GetTextureFromImagePath("images/frogger_log_mid.png", cellSize, cellSize);
    const Texture2D texture_lillypad = GetTextureFromImagePath("images/frogger_lillypad.png", cellSize, cellSize);
    const Texture2D texture_player_up = GetTextureFromImagePath("images/frogger_frog_up.png", cellSize, cellSize);
    const Texture2D texture_player_down = GetTextureFromImagePath("images/frogger_frog_down.png", cellSize, cellSize);
    const Texture2D texture_player_left = GetTextureFromImagePath("images/frogger_frog_left.png", cellSize, cellSize);
    const Texture2D texture_player_right = GetTextureFromImagePath("images/frogger_frog_right.png", cellSize, cellSize);
    //Precache Sound 
    const Sound sound_splash = LoadSound("sound/frogger_splash.mp3");
    const Sound sound_ambient = LoadSound("sound/frogger_streetnoise_fix.mp3");
    const Sound sound_splat = LoadSound("sound/frogger_splat.wav");
    const Sound sound_bgmusic = LoadSound("sound/frogger_menutheme.mp3");
    const Sound sound_victory = LoadSound("sound/frogger_victory.mp3");
    const Sound sound_goaltaken = LoadSound("sound/frogger_goaltaken.mp3");

    InitAudioDevice();
    SetMasterVolume(0.5);

    Game game;
    game.Setup();

    bool scoreLoaded = false;
    int currentHighscore = 0;

    while (!WindowShouldClose())
    {
        //Uses a bool to load the score ONCE per game. Saves CPU cycles (however miniscule).
        if (!scoreLoaded)
        {
            currentHighscore = GetHighscoreFromFile();
            scoreLoaded = true;
        }

        game.GetTimer()->Tick();
        BeginDrawing();
        ClearBackground(DARKGRAY);
        if (!game.IsGameOver() && !game.IsGameWon())
        {
            if (!IsSoundPlaying(sound_bgmusic))
            {
                SetSoundVolume(sound_bgmusic, 0.5);
                PlaySound(sound_bgmusic);
            }

            if (IsKeyPressed(KEY_RIGHT))  game.ProcessInput(KEY_RIGHT);
            if (IsKeyPressed(KEY_LEFT))   game.ProcessInput(KEY_LEFT);
            if (IsKeyPressed(KEY_UP))     game.ProcessInput(KEY_UP);
            if (IsKeyPressed(KEY_DOWN))   game.ProcessInput(KEY_DOWN);

            game.UpdateMoveableTiles();
        }

        while (game.IsGameOver())
        {
            if (IsSoundPlaying(sound_bgmusic))
            {
                StopSound(sound_bgmusic);
            }
            // Draw HUD elements
            BeginDrawing();
            ClearBackground(BLANK);
            DrawText(("GAME OVER"), 180, 280, 40, RED);
            DrawText(("| Press [SPACE] to restart | Press[ESC] to quit |"), 177, 320, 8, WHITE);
            EndDrawing();

            //check for key presses
            if (IsKeyPressed(SPACEBAR))
            {
                game.Setup();
                game.SetGameWon(false);
                scoreLoaded = false;
                break;
            }
            if (IsKeyDown(ESCAPE))
            {
                game.SetGameOver(false);
                CloseWindow();
            }
        }

        bool firstWinLoop = true;
        while (game.IsGameWon())
        {
            if (firstWinLoop)
            {
                StopSound(sound_bgmusic);
                PlaySound(sound_victory);
                SaveScoreToFile(CalculateHighscore(game.GetTimer()->GetTimeInSeconds(), game.GetPlayer()->GetCurrentLives()));
                firstWinLoop = false;
            }
            // Draw HUD elements
            BeginDrawing();
            ClearBackground(DARKGREEN);
            DrawText(("YOU WON!"), 180, 280, 40, WHITE);
            DrawText(("| Press [SPACE] to play again | Press[ESC] to quit |"), 177, 320, 8, WHITE);
            EndDrawing();
            //check for key presses
            if (IsKeyPressed(SPACEBAR))
            {
                game.Setup();
                game.SetGameWon(false);
                scoreLoaded = false; //When the game restarts, ensures that the highscore reloads
                break;
            }
            if (IsKeyPressed(ESCAPE))
            {
                game.SetGameWon(false);
                CloseWindow();
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

        // Draw HUD on bottom of the screen
        const int fontSize = 20;
        int currentLives = game.GetPlayer()->GetCurrentLives();

        DrawRectangle(0, gameSizeX, gameSizeX, gameSizeY - gameSizeX, BLACK);
        DrawText(TextFormat("Lives: %i", currentLives), 
            (double)gameSizeX * 0.05, (double)gameSizeX + (fontSize / 2), fontSize, GREEN);

        DrawText(TextFormat("Timer: %02i:%02i", game.GetTimer()->GetMinutes(), game.GetTimer()->GetSeconds()),
            (double)gameSizeX * 0.75, (double)gameSizeX + (fontSize / 2), fontSize, GREEN);

        DrawText(TextFormat("Highscore: %i", currentHighscore),
            (double)gameSizeX * 0.30, (double)gameSizeX + (fontSize / 2), fontSize, GREEN);

        EndDrawing();
 
        // --- Player Position Checks ---
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
            if (!IsSoundPlaying(sound_splash))
            {
                SetSoundVolume(sound_splash, 1);
                PlaySound(sound_splash);
            }
        }
        if (game.CheckForPlayerOnGoal())
        {
            if (!IsSoundPlaying(sound_goaltaken))
            {
                PlaySound(sound_goaltaken);
            }
        }
        game.CheckForPlayerOnSticky();

        //---------------------------------

        //Check to see if the player has any lives left
        if (game.GetPlayer()->GetCurrentLives() == 0) game.SetGameOver(true);
        else game.SetGameOver(false);

        //Final check to see if the player has any lives left
        if (game.CheckForPlayerWin())  game.SetGameWon(true);
        else game.SetGameWon(false);
    }
    UnloadSound(sound_ambient);
    CloseWindow();
    return 0;
}

// Performs all the loading and resizing of an image to return a single Texture2D object for raylib
const Texture2D GetTextureFromImagePath(const char* path, const int& cellSizeX, const int& cellSizeY)
{
    Image newImage = LoadImage(path);
    ImageResize(&newImage, cellSizeX, cellSizeY);
    return LoadTextureFromImage(newImage);
}

//Opens the highscore file, reads every line and returns the largest number.
int GetHighscoreFromFile()
{
    int currentHighscore = 0;
    ifstream highscoresFile;
    highscoresFile.open("stats/highscores.txt");
    if (highscoresFile.is_open())
    {
        std::string line = "";
        while (std::getline(highscoresFile, line))
        {
            int highscore = atoi(line.c_str());
            if (highscore > currentHighscore) currentHighscore = highscore;
        }
    }
    return currentHighscore;
}

//Performs an algorithm which computes an integer based on lives left and seconds taken
int CalculateHighscore(const int& seconds, const int& livesLeft)
{
    int score = 0;
    if (seconds != 0 && livesLeft != 0) return (livesLeft * 1000) - seconds;
    return 0;
}

//Opens the high score file and appends the players current score to the end
void SaveScoreToFile(const int& score)
{
    std::ofstream ofile;
    ofile.open("stats/highscores.txt", std::ofstream::app);
    ofile << endl << score;
}