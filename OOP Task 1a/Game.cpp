#include "Game.h"

void Game::Setup()
{
    //puts specific wall tiles into the walls vector
    tiles.push_back(Safezone(14, 0));
    tiles.push_back(Safezone(14, 1));
    tiles.push_back(Safezone(14, 2));
    tiles.push_back(Safezone(14, 3));
    tiles.push_back(Safezone(14, 4));
    tiles.push_back(Safezone(14, 5));
    tiles.push_back(Safezone(14, 6));
    tiles.push_back(Safezone(14, 7));
    tiles.push_back(Safezone(14, 8));
    tiles.push_back(Safezone(14, 9));
    tiles.push_back(Safezone(14, 10));
    tiles.push_back(Safezone(14, 11));
    tiles.push_back(Safezone(14, 12));
    tiles.push_back(Safezone(14, 13));
    tiles.push_back(Safezone(14, 14));

    tiles.push_back(Safezone(13, 0));
    tiles.push_back(Safezone(13, 1));
    tiles.push_back(Safezone(13, 2));
    tiles.push_back(Safezone(13, 3));
    tiles.push_back(Safezone(13, 4));
    tiles.push_back(Safezone(13, 5));
    tiles.push_back(Safezone(13, 6));
    tiles.push_back(Safezone(13, 7));
    tiles.push_back(Safezone(13, 8));
    tiles.push_back(Safezone(13, 9));
    tiles.push_back(Safezone(13, 10));
    tiles.push_back(Safezone(13, 11));
    tiles.push_back(Safezone(13, 12));
    tiles.push_back(Safezone(13, 13));
    tiles.push_back(Safezone(13, 14));
    

    // for just one level, add all the tiles here

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
        else return false;
    }
}

bool Game::IsAquaAtPosition(int x, int y)
{
    for (size_t i = 0; i < tiles.size(); ++i)
    {
        if (tiles[i].IsAtPosition(x, y) && tiles[i].GetSymbol() == AQUA)
        {
            return true;
        }
        else return false;
    }
}

bool Game::IsRunning()
{
    // depending on your game you'll need to modify this to return false
    // maybe it's when the player runs out of moves, maybe it's when they get caught, it's up to you!
    return true;
}