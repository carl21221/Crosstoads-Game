#pragma once
//Load inbuilt Libraries
#include <assert.h>	
#include <string>		
#include <vector>
#include <iostream>
#include "Player.h"
#include "Timer.h"

//Load Tile Libraries
#include "Tile.h"
#include "Safezone.h"
#include "Road.h"
#include "Aqua.h"
#include "Goal.h"

//Load Moveable Libraries
#include "Movable.h"
#include "Car.h"
#include "Van.h"
#include "Truck.h"
#include "Log.h"
#include "Lillypad.h"

using namespace std;

class Game
{
public:
    //Member Variables
    Timer mainTimer;
    vector<Tile> tiles;
    vector<Safezone> safezones;
    vector<Road> roads;
    vector<Aqua> aquas;
    vector<Goal> goals;
    vector<Car> cars;
    vector<Van> vans;
    vector<Truck> trucks;
    vector<Movable> vehicles;
    vector<Log> logs;
    vector<Lillypad> lillypads;
    vector<MovableSticky*> movStickies;

    void SetActive();
    void SetInactive();
    bool IsGameActive() const;
    const bool IsGameOver() const;
    const void SetGameToWon();
    const bool IsGameWon() const;
    const int GetGoalTakenCount() const;
    const int GetGoalTotalCount() const;
    const vector<vector<char>> PrepareEnvGrid();
    const vector<vector<char>> PrepareMovGrid();
    Timer* GetTimer();
    Player* GetPlayer();
    Log* GetLogInstance(int x, int y);
    Lillypad* GetLillypadInstance(int x, int y);
    Goal* GetGoalInstance(int x, int y);
    Movable* GetMovableInstance(int x, int y);

    const bool IsSafezoneAtPosition(const int& x, const int& y) const;
    const bool IsRoadAtPosition(const int& x, const int& y) const;
    const bool IsAquaAtPosition(const int& x, const int& y) const;
    const bool IsGoalAtPosition(const int& x, const int& y) const;
    const bool IsCarAtPosition(const int& x, const int& y) const;
    const bool IsVanAtPosition(const int& x, const int& y) const;
    const bool IsTruckAtPosition(const int& x, const int& y) const;
    const bool IsLogAtPosition(const int& x, const int& y) const;
    const bool IsLillypadAtPosition(const int& x, const int& y) const;
    const bool IsStickyAtPosition(const int& x, const int& y) const;
    const bool IsPlayerAtPosition(const int& x, const int& y) const;

    bool CheckForPlayerDeathByVehicle();
    bool CheckForPlayerDeathByAqua();
    bool CheckForPlayerOnGoal();
    bool CheckForPlayerWin();
    bool CheckForPlayerOnSticky();

    const void SetGameToOver();

    //Setters
    const void SetGameOver(const bool& value);
    const void SetGameWon(const bool& value);

    //Mutators
    void Setup();
    const void ProcessInput(const int& key);
    const void UpdateMoveableTiles();

private:
    // Member Variables
    Player player;
    bool isGameActive = false;
    bool isGameOver = false;
    bool isGameWon = false;

    //Support functions
    const void PushTiles_Safezone();
    const void PushTiles_Road();
    const void PushTiles_Aqua();
    const void PushTiles_Goal();
    const void SetupTiles_Vehicle();
    const void SetupTiles_MoveableStickies();
    const void UpdateTiles_Vehicle();
    const void UpdateTiles_MovSticky();
    const void SetupEnvironmentTiles();
    const void SetupMoveableTiles();

    const void CreateLog(const int& originX, const int& originY, const int& logLength, const int& moveDelay, const std::string& direction);
    const void CreateTruck(const int& originX, const int& originY, const int& truckLength, const int& moveDelay, const std::string& direction);
    const void CreateVan(const int& originX, const int& originY, const int& vanLength, const int& moveDelay, const std::string& direction);

    void ResetGoals();
};