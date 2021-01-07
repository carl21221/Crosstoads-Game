#pragma once

#include <assert.h>	
#include <string>		
#include <vector>
#include "Player.h"
#include "Wall.h"

//Load Tile Librarys
#include "Tile.h"
#include "Safezone.h"
#include "Road.h"
#include "Aqua.h"
#include "Goal.h"

using namespace std;

class Game
{
   public:
      Player player;

      vector<Tile> tiles;
      vector<Safezone> safezones;
      vector<Road> roads;
      vector<Aqua> aquas;
      vector<Goal> goals;

      void Setup();
      void ProcessInput(int key);
      vector<vector<char>> PrepareGrid();

      bool IsRunning();

      //Check for specific tiles
      bool IsSafezoneAtPosition(int x, int y);
      bool IsRoadAtPosition(int x, int y);
      bool IsAquaAtPosition(int x, int y);
      bool IsGoalAtPosition(int x, int y);

      bool IsCarAtPosition(int x, int y);
      bool IsVanAtPosition(int x, int y);
      bool IsLogAtPosition(int x, int y);

      //Tile Load Functions
      void PushTiles_Safezone();
      void PushTiles_Road();
      void PushTiles_Aqua();
      void PushTiles_Goal();

      //Player Functions
      void CheckForPlayerDeath();
};