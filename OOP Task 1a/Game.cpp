#include "Game.h"

void Game::Setup()
{
    SetupEnvironmentTiles();
    SetupMoveableTiles();
    this->player.ResetLives();
}

void Game::SetGameOver(bool value) { this->isGameOver = value; }

bool Game::IsGameOver() { return this->isGameOver; }

Player* Game::GetPlayer() { return &this->player; }

void Game::ProcessInput(int key) { player.Move(key); }

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
        vector<char> line;
        for (int col = 1; col <= SIZE; ++col)
        {
            if (IsSafezoneAtPosition(col, row))     line.push_back(SAFEZONE);
            else if (IsAquaAtPosition(col, row))    line.push_back(AQUA);
            else if (IsRoadAtPosition(col, row))    line.push_back(ROAD);
            else if (IsGoalAtPosition(col, row))    line.push_back(GOAL);
            else                                    line.push_back(FLOOR);

            //Checks if theres a special tile at the position
            //Currently replaces the environment tile underneath. 
            // However, we will later use these checks
            // to add images on top of the grid underneath
            if (IsCarAtPosition(col, row)) line.at(col - 1) = CAR;           
            if (IsVanAtPosition(col, row)) line.at(col - 1) = VAN;
            if (IsTruckAtPosition(col, row)) line.at(col - 1) = TRUCK;
            if (IsLogAtPosition(col, row)) line.at(col - 1) = LOG;
            if (IsPlayerAtPosition(col, row)) line.at(col - 1) = PLAYER;
        }
        // now that the row is full, add it to the 2D grid
        grid.push_back(line);
    }
    return grid;
}

/// <summary>
/// Gets a reference to a log instance at a specific location
/// </summary>
Log* Game::GetLogInstance(int x, int y)
{
    for (Log& log : logs)
    {
        if (log.GetX() == x && log.GetY() == y) return &log;
    }
    return nullptr;
}

/// <summary>
/// Gets a reference to a goal instance at a specific location
/// </summary>
Goal* Game::GetGoalInstance(int x, int y)
{
    for (Goal& goal : goals) 
    { 
        if (goal.GetX() == x && goal.GetY() == y) return &goal;
    }
    return nullptr;
}

void Game::CheckForPlayerResponse()
{
    int playerX = player.GetX();
    int playerY = player.GetY();
      
    // AQUA TILE CHECK
    if (IsAquaAtPosition(playerX, playerY))
    {
        if (!IsLogAtPosition(playerX, playerY)) player.Die();
        else 
        {
            Log* thisLog = GetLogInstance(playerX, playerY);             // Get a reference to a particular log instance
            if (thisLog != nullptr) thisLog->LinkPlayer(player);         // If there is a log at the player position link the player to it
        }
    }

    // GOAL TILE CHECK
    if (IsGoalAtPosition(playerX, playerY))
    {
        Goal* thisGoal = GetGoalInstance(playerX, playerY);
        if(thisGoal != nullptr)
        {
            thisGoal->SetIsTaken(true);
            this->player.PositionAtStart();
        }
    }

    // VEHICLE CHECK 
    for (auto& v : vehicles) { if (IsPlayerAtPosition(v.GetX(), v.GetY())) player.Die(); }
}

bool Game::IsPlayerAtPosition(int x, int y)
{
    for (size_t i = 0; i < tiles.size(); ++i)
    {
        if (player.IsAtPosition(x, y))
        {
            return true;
        }
    }
    return false;
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

bool Game::IsVanAtPosition(int x, int y)
{
    for (size_t i = 0; i < vehicles.size(); ++i)
    {
        if (vehicles[i].IsAtPosition(x, y) && vehicles[i].GetSymbol() == VAN) return true;
    }
    return false;
}

bool Game::IsTruckAtPosition(int x, int y)
{
    for (size_t i = 0; i < vehicles.size(); ++i)
    {
        if (vehicles[i].IsAtPosition(x, y) && vehicles[i].GetSymbol() == TRUCK) return true;
    }
    return false;
}

bool Game::IsLogAtPosition(int x, int y)
{
    for (size_t i = 0; i < logs.size(); ++i)
    {
        if (logs[i].IsAtPosition(x, y) && logs[i].GetSymbol() == LOG) return true;
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
    SetupTiles_Logs();
}
void Game::UpdateMoveableTiles()
{
    UpdateTiles_Vehicle();
    UpdateTiles_Log();
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

    aquas.push_back(Aqua(1, 1));
    aquas.push_back(Aqua(2, 1));
    aquas.push_back(Aqua(4, 1));
    aquas.push_back(Aqua(5, 1));
    aquas.push_back(Aqua(7, 1));
    aquas.push_back(Aqua(8, 1));
    aquas.push_back(Aqua(10, 1));
    aquas.push_back(Aqua(11, 1));
    aquas.push_back(Aqua(13, 1));
    aquas.push_back(Aqua(14, 1));

    aquas.push_back(Aqua(1, 2));
    aquas.push_back(Aqua(2, 2));
    aquas.push_back(Aqua(4, 2));
    aquas.push_back(Aqua(5, 2));
    aquas.push_back(Aqua(7, 2));
    aquas.push_back(Aqua(8, 2));
    aquas.push_back(Aqua(10, 2));
    aquas.push_back(Aqua(11, 2));
    aquas.push_back(Aqua(13, 2));
    aquas.push_back(Aqua(14, 2));

    for each (Aqua a in aquas) { tiles.push_back(a); }
}
void Game::PushTiles_Goal()
{
    goals.push_back(Goal(3, 1));
    goals.push_back(Goal(6, 1));
    goals.push_back(Goal(9, 1));
    goals.push_back(Goal(12, 1));
    goals.push_back(Goal(15, 1));
    goals.push_back(Goal(3, 2));
    goals.push_back(Goal(6, 2));
    goals.push_back(Goal(9, 2));
    goals.push_back(Goal(12, 2));
    goals.push_back(Goal(15, 2));

    for each (Goal g in goals) { tiles.push_back(g); }
}
void Game::SetupTiles_Vehicle()
{
    //Load vehicles into corresponsing vectors here
    cars.push_back(Car(15, 13, 20, "left"));
    cars.push_back(Car(2, 13, 20, "left"));

    cars.push_back(Car(2, 11, 20, "left"));
    cars.push_back(Car(6, 11, 20, "left"));

    vans.push_back(Van(4, 12, 40, "right"));
    vans.push_back(Van(5, 12, 40, "right"));

    trucks.push_back(Truck(10, 10, 50, "right"));
    trucks.push_back(Truck(11, 10, 50, "right"));
    trucks.push_back(Truck(12, 10, 50, "right"));

    //These loops put all vehicle types in the vehicles list
    //DO NOT MODIFY
    for (auto& car : cars) { vehicles.push_back(car); }
    for (auto& van : vans) { vehicles.push_back(van); }
    for (auto& truck : trucks) { vehicles.push_back(truck); }
}



/// <summary>
/// Adds a log to the vector with a specified length. 
/// Truncates the logs if the logs length exceeds the grid width
/// </summary>
void Game::CreateLog(int originX, int originY, int logLength, int moveDelay, std::string direction)
{
    for (int i = 0; i < logLength; i++)
    {
        if ((originX + i) < 15)
        {
            logs.push_back(Log(originX + i, originY, moveDelay, direction));
        }
        else break;
    }
}

void Game::SetupTiles_Logs()
{
    CreateLog(11, 3, 3, 50, "left");
    CreateLog(1, 4, 4, 30, "right");
    CreateLog(4, 5, 5, 20, "left");
    CreateLog(9, 6, 4, 30, "right");
    CreateLog(3, 7, 4, 10, "left");

    // CreateLog function does this for you. 
    // If creating individual tiles, use this below
    //for (auto& log : logs) { logs.push_back(log); }
}

void Game::UpdateTiles_Vehicle()
{
    for (auto& v : vehicles) { v.CalculateMove(); }
}

void Game::UpdateTiles_Log()
{
    for (auto& l : logs) 
    { 
        l.CalculateMove();
        l.UnlinkPlayer();
    }
}