#pragma once

#include <assert.h>	
#include <string>		
#include <vector>
#include "Player.h"
#include "Wall.h"
#include "Tile.h"
#include "Safezone.h"

using namespace std;

class Game
{
   public:
      Player player;
      vector<Tile> tiles;

      void Setup();
      void ProcessInput(int key);
      vector<vector<char>> PrepareGrid();
      bool IsRunning();

      //Check for specific tiles
      bool IsSafezoneAtPosition(int x, int y);
      bool IsAquaAtPosition(int x, int y);
      bool IsCarAtPosition(int x, int y);
      bool IsVanAtPosition(int x, int y);
      bool IsLogAtPosition(int x, int y);
};