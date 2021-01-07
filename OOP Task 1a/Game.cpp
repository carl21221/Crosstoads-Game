#include "Game.h"

void Game::Setup()
{
    // Method of adding safezones
    PushTiles_Safezone();
    
    for each (Safezone sz in safezones)
    {
        tiles.push_back(sz); // add the value of what is pointed to by sz
    }
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
            if (row == player.GetY() && col == player.GetX()) // CHECK FOR PLAYER
            {
                line.push_back(player.GetSymbol());
            }

            else if (IsSafezoneAtPosition(col, row)) //CHECK IF THERES IS A SAFEZONE MATCHING THAT COORDINATE
            {
                line.push_back(SAFEZONE);
            }
            else if (IsAquaAtPosition(col, row)) //CHECK IF THERES IS AQUA MATCHING THAT COORDINATE
            {
                line.push_back(AQUA);
            }

            else
            {
                line.push_back(FLOOR);
            }
        }

        // now that the row is full, add it to the 2D grid
        grid.push_back(line);
    }

    return grid;
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

bool Game::IsRunning()
{
    // depending on your game you'll need to modify this to return false
    // maybe it's when the player runs out of moves, maybe it's when they get caught, it's up to you!
    return true;
}

//Load Tile functions
void Game::PushTiles_Safezone()
{
    for (int i = 1; i <= 15; i++) { safezones.push_back(Safezone(i, 15)); }
    for (int i = 1; i <= 15; i++) { safezones.push_back(Safezone(i, 14)); }
    for (int i = 1; i <= 15; i++) { safezones.push_back(Safezone(i, 8)); }
    for (int i = 1; i <= 15; i++) { safezones.push_back(Safezone(i, 9)); }
}

void Game::PushTiles_Road()
{
    //for (int i = 1; i <= 15; i++) { safezones.push_back(Road(i, 13)); }
    //for (int i = 1; i <= 15; i++) { safezones.push_back(Road(i, 12)); }
    //for (int i = 1; i <= 15; i++) { safezones.push_back(Road(i, 11)); }
    //for (int i = 1; i <= 15; i++) { safezones.push_back(Road(i, 10)); }
}