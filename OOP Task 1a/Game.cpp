#include "Game.h"

void Game::Setup()
{
    SetupEnvironmentTiles();
    SetupMoveableTiles();
}

void Game::ProcessInput(int key)
{
    player.Move(key);
}

/// <summary>
/// This function builds up a 2D grid of characters representing the current state of the game.
/// The characters are later used to decide which colour sqaure to display, but you could display images instead.
/// </summary>

vector<vector<char>> Game::PrepareGrid() 
{
    // create the 2D grid
    vector<vector<char>> grid;

    // for each row
    for (int row = 1; row <= SIZE; ++row)
    {
        // create the inner vector to add to the 2D grid
        vector<char> line;
        // for each column, work out what's in that position and add the relevant char to the 2D grid
        for (int col = 1; col <= SIZE; ++col)
        {
            if (row == player.GetY() && col == player.GetX())   line.push_back(player.GetSymbol());
            else if (IsSafezoneAtPosition(col, row))            line.push_back(SAFEZONE);
            else if (IsAquaAtPosition(col, row))                line.push_back(AQUA);
            else if (IsRoadAtPosition(col, row))                line.push_back(ROAD);
            else if (IsGoalAtPosition(col, row))                line.push_back(GOAL);
            else                                                line.push_back(FLOOR);

            if (IsCarAtPosition(col, row))                      line.insert(line.begin() + col, CAR);
        }
        // now that the row is full, add it to the 2D grid
        grid.push_back(line);
    }
    return grid;
}

void Game::CheckForPlayerDeath()
{
    for each(Aqua a in aquas)
    {
        if (player.GetX() == a.GetX() && player.GetY() == a.GetY()) player.Die();
    }
}

bool Game::IsSafezoneAtPosition(int x, int y)
{
    for (size_t i = 0; i < tiles.size(); ++i)
    {
        if (tiles[i].IsAtPosition(x, y) && tiles[i].GetSymbol() == SAFEZONE)
        {
            return true;
        }
    }
    return false;
}

bool Game::IsAquaAtPosition(int x, int y)
{
    for (size_t i = 0; i < tiles.size(); ++i)
    {
        if (tiles[i].IsAtPosition(x, y) && tiles[i].GetSymbol() == AQUA)
        {
            return true;
        }
    }
    return false;
}

bool Game::IsRoadAtPosition(int x, int y)
{
    for (size_t i = 0; i < tiles.size(); ++i)
    {
        if (tiles[i].IsAtPosition(x, y) && tiles[i].GetSymbol() == ROAD)
        {
            return true;
        }
    }
    return false;
}

bool Game::IsGoalAtPosition(int x, int y)
{
    for (size_t i = 0; i < tiles.size(); ++i)
    {
        if (tiles[i].IsAtPosition(x, y) && tiles[i].GetSymbol() == GOAL)
        {
            return true;
        }
    }
    return false;
}

bool Game::IsCarAtPosition(int x, int y)
{
    for (size_t i = 0; i < vehicles.size(); ++i)
    {
        if (vehicles[i].IsAtPosition(x, y) && vehicles[i].GetSymbol() == CAR) return true;
    }
    return false;
}

bool Game::IsRunning()
{
    if (player.GetCurrentLives() <= 0) return false;
    else return true;
}

//Load Tile functions

void Game::SetupEnvironmentTiles()
{
    PushTiles_Safezone();
    PushTiles_Road();
    PushTiles_Aqua();
    PushTiles_Goal();
}
void Game::SetupMoveableTiles()
{
    SetupTiles_Vehicle();
}

void Game::UpdateMoveableTiles()
{
    UpdateTiles_Vehicle();
}

void Game::PushTiles_Safezone()
{
    for (int i = 1; i <= 15; i++) { safezones.push_back(Safezone(i, 8)); }
    for (int i = 1; i <= 15; i++) { safezones.push_back(Safezone(i, 9)); }
    for (int i = 1; i <= 15; i++) { safezones.push_back(Safezone(i, 14)); }
    for (int i = 1; i <= 15; i++) { safezones.push_back(Safezone(i, 15)); }
    for each (Safezone sz in safezones) { tiles.push_back(sz); }
}

void Game::PushTiles_Road()
{
    for (int i = 1; i <= 15; i++) { roads.push_back(Road(i, 10)); }
    for (int i = 1; i <= 15; i++) { roads.push_back(Road(i, 11)); }
    for (int i = 1; i <= 15; i++) { roads.push_back(Road(i, 12)); }
    for (int i = 1; i <= 15; i++) { roads.push_back(Road(i, 13)); }
    for each (Road r in roads) { tiles.push_back(r); }
}

void Game::PushTiles_Aqua()
{
    for (int i = 1; i <= 15; i++) { aquas.push_back(Aqua(i, 3)); }
    for (int i = 1; i <= 15; i++) { aquas.push_back(Aqua(i, 4)); }
    for (int i = 1; i <= 15; i++) { aquas.push_back(Aqua(i, 5)); }
    for (int i = 1; i <= 15; i++) { aquas.push_back(Aqua(i, 6)); }
    for (int i = 1; i <= 15; i++) { aquas.push_back(Aqua(i, 7)); }
    for each (Aqua a in aquas) { tiles.push_back(a); }
}

void Game::PushTiles_Goal()
{
    for (int i = 1; i <= 15; i++) { goals.push_back(Goal(i, 1)); }
    for (int i = 1; i <= 15; i++) { goals.push_back(Goal(i, 2)); }
    for each (Goal g in goals) { tiles.push_back(g); }
}

void Game::SetupTiles_Vehicle()
{
    cars.push_back(Car(15, 13, 30));

    for (auto& car : cars)
    {
        vehicles.push_back(car);
    }
}

void Game::UpdateTiles_Vehicle()
{
    for (auto& v : vehicles)
    {
        v.CalculateMove();
    }
}