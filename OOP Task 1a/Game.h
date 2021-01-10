#pragma once

#include <assert.h>	
#include <string>		
#include <vector>
#include "Player.h"
#include "Wall.h"
#include <iostream>

//Load Tile Librarys
#include "Tile.h"
#include "Safezone.h"
#include "Road.h"
#include "Aqua.h"
#include "Goal.h"

//Load Moveable Librarys
#include "Movable.h"
#include "Car.h"
#include "Van.h"
#include "Truck.h"

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
      
      vector<Movable> vehicles;
      vector<Car> cars;
      vector<Van> vans;
      vector<Truck> trucks;

      void Setup();
      void UpdateMoveableTiles();
      void ProcessInput(int key);
      vector<vector<char>> PrepareGrid();

      bool IsRunning();

      void SetupEnvironmentTiles();
      void SetupMoveableTiles();

      //Check for specific tiles
      bool IsSafezoneAtPosition(int x, int y);
      bool IsRoadAtPosition(int x, int y);
      bool IsAquaAtPosition(int x, int y);
      bool IsGoalAtPosition(int x, int y);

      bool IsCarAtPosition(int x, int y);
      bool IsVanAtPosition(int x, int y);
      bool IsTruckAtPosition(int x, int y);

      bool IsLogAtPosition(int x, int y);

      //Tile Load Functions
      void PushTiles_Safezone();
      void PushTiles_Road();
      void PushTiles_Aqua();
      void PushTiles_Goal();

      void SetupTiles_Vehicle();
      void UpdateTiles_Vehicle();

      //Player Functions
      void CheckForPlayerDeath();
      bool IsPlayerAtPosition(int x, int y);
};