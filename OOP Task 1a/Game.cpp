#include "Game.h"

void Game::Setup()
{
    this->isGameWon == false;
    this->isGameOver == false;
    this->player.ResetLives();
    this->mainTimer.Reset();
    SetupEnvironmentTiles();
    SetupMoveableTiles();
    ResetGoals();


}

const void Game::SetGameOver(const bool& value) { this->isGameOver = value; }

const bool Game::IsGameOver() const { return this->isGameOver; }

const void Game::SetGameWon(const bool& value) { this->isGameWon = value; }

const bool Game::IsGameWon() const { return this->isGameWon; }

Player* Game::GetPlayer() { return &this->player; }

const void Game::ProcessInput(const int& key) { player.Move(key); }

Timer* Game::GetTimer() { return &mainTimer; }

const vector<vector<char>> Game::PrepareEnvGrid()
{
    // create the 2D grid
    vector<vector<char>> envGrid;
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
        }
        // now that the row is full, add it to the 2D grid
        envGrid.push_back(line);
    }
    return envGrid;
}

const vector<vector<char>> Game::PrepareMovGrid()
{
    vector<vector<char>> movGrid;
    for (int row = 1; row <= SIZE; ++row)
    {
        vector<char> line;
        for (int col = 1; col <= SIZE; ++col)
        {
            if (IsCarAtPosition(col, row))              line.push_back(CAR);
            else if (IsVanAtPosition(col, row))         line.push_back(VAN);
            else if (IsTruckAtPosition(col, row))       line.push_back(TRUCK);
            else if (IsLogAtPosition(col, row))         line.push_back(LOG);
            else if (IsLillypadAtPosition(col, row)) {  line.push_back(LILLYPAD);}
            else                                        line.push_back('x');
        }
        movGrid.push_back(line);
    }
    return movGrid;
}


// Stores a pointer to a specific instance in the game's vectors. 
// Allows me to link the player so the log can move the player.
Log* Game::GetLogInstance(int x, int y)
{
    for (Log& log : logs)
    {
        if (log.GetX() == x && log.GetY() == y) return &log;
    }
    return nullptr;
}

// Same as GetLogInstance above, but for Lillypad objects
Lillypad* Game::GetLillypadInstance(int x, int y)
{
    for (Lillypad& lp : lillypads)
    {
        if (lp.GetX() == x && lp.GetY() == y) return &lp;
    }
    return nullptr;
}

// Stores a pointer to a specific goal in the game's vector "goals"
// This allows me to change the goal's state to "Taken" once the player steps on it
Goal* Game::GetGoalInstance(int x, int y)
{
    for (Goal& goal : goals) 
    { 
        if (goal.GetX() == x && goal.GetY() == y) return &goal;
    }
    return nullptr;
}

// Gets specific instance to a movable object.
Movable* Game::GetMovableInstance(int x, int y)
{
    for (Movable m : vehicles)
    {
        if (m.GetX() == x && m.GetY() == y) return &m;
    }
    return nullptr;
}

// Specific player checks -----
bool Game::CheckForPlayerDeathByVehicle()
{
    int playerX = player.GetX();
    int playerY = player.GetY();

    for (auto& v : vehicles)
    {
        if (IsPlayerAtPosition(v.GetX(), v.GetY()))
        {
            player.Die();
            return true;
        }
    }
    return false;
}

bool Game::CheckForPlayerDeathByAqua()
{
    int playerX = player.GetX();
    int playerY = player.GetY();

    // AQUA TILE CHECK
    if (IsAquaAtPosition(playerX, playerY))
    {
        if (!IsLogAtPosition(playerX, playerY) && (!IsLillypadAtPosition(playerX, playerY)))
        {
            player.Die();
            return true;
        }
    }
    return false;
}

bool Game::CheckForPlayerOnGoal()
{
    int playerX = player.GetX();
    int playerY = player.GetY();

    if (IsGoalAtPosition(playerX, playerY))
    {
        Goal* thisGoal = GetGoalInstance(playerX, playerY);
        if (thisGoal != nullptr)
        {
            thisGoal->SetIsTaken(true);
            this->player.PositionAtStart();
            return true;
        }
    }
    return false;
}

bool Game::CheckForPlayerWin()
{
    if (GetGoalTakenCount() == GetGoalTotalCount()) return true;
    else return false;
}

bool Game::CheckForPlayerOnSticky()
{
    int playerX = player.GetX();
    int playerY = player.GetY();

    if (IsLogAtPosition(playerX, playerY))
    {
        Log* thisLog = GetLogInstance(playerX, playerY);             // Get a reference to a particular log instance
        if (thisLog != nullptr)
        {
            thisLog->LinkPlayer(player);         // If there is a log at the player position link the player to it
            return true;
        }
    }
    else if (IsLillypadAtPosition(playerX, playerY))
    {
        Lillypad* thisLillyPad = GetLillypadInstance(playerX, playerY);             // Get a reference to a particular lillypad instance
        if (thisLillyPad != nullptr)
        {
            thisLillyPad->LinkPlayer(player);         // If there is a lillypad at the player position link the player to it
            return true;
        }
    }
    return false;
}

// ----------------------------

// Checks to see if a specific element is at a specified position.

const bool Game::IsPlayerAtPosition(const int& x, const int& y) const
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

const bool Game::IsSafezoneAtPosition(const int& x, const int& y) const
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

const bool Game::IsAquaAtPosition(const int& x, const int& y) const
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

const bool Game::IsRoadAtPosition(const int& x, const int& y) const
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

const bool Game::IsGoalAtPosition(const int& x, const int& y) const
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

const bool Game::IsCarAtPosition(const int& x, const int& y) const
{
    for (size_t i = 0; i < vehicles.size(); ++i)
    {
        if (vehicles[i].IsAtPosition(x, y) && vehicles[i].GetSymbol() == CAR) return true;
    }
    return false;
}

const bool Game::IsVanAtPosition(const int& x, const int& y) const
{
    for (size_t i = 0; i < vehicles.size(); ++i)
    {
        if (vehicles[i].IsAtPosition(x, y) && vehicles[i].GetSymbol() == VAN) return true;
    }
    return false;
}

const bool Game::IsTruckAtPosition(const int& x, const int& y) const
{
    for (size_t i = 0; i < vehicles.size(); ++i)
    {
        if (vehicles[i].IsAtPosition(x, y) && vehicles[i].GetSymbol() == TRUCK) return true;
    }
    return false;
}

const bool Game::IsLogAtPosition(const int& x, const int& y) const
{
    for (size_t i = 0; i < logs.size(); ++i)
    {
        if (logs[i].IsAtPosition(x, y) && logs[i].GetSymbol() == LOG) return true;
    }
    return false;
}

const bool Game::IsLillypadAtPosition(const int& x, const int& y) const
{
    for (size_t i = 0; i < lillypads.size(); ++i)
    {
        if (lillypads[i].IsAtPosition(x, y) && lillypads[i].GetSymbol() == LILLYPAD) return true;
    }
    return false;
}

const bool Game::IsStickyAtPosition(const int& x, const int& y) const
{
    for (size_t i = 0; i < movStickies.size(); ++i)
    {
        if (movStickies[i]->IsAtPosition(x, y) && (movStickies[i]->GetSymbol() == LILLYPAD || movStickies[i]->GetSymbol() == LOG)) return true;
    }
    return false;
}


// -------------------------------------------------------------------


bool Game::IsRunning() const
{
    if (player.GetCurrentLives() <= 0) return false;
    else return true;
}

//Load Tile functions
const void Game::SetupEnvironmentTiles()
{
    safezones.clear();
    PushTiles_Safezone();
    roads.clear();
    PushTiles_Road();
    aquas.clear();
    PushTiles_Aqua();
    goals.clear();
    PushTiles_Goal();
}

const void Game::SetupMoveableTiles()
{
    SetupTiles_Vehicle();
    SetupTiles_MoveableStickies();
}

const void Game::UpdateMoveableTiles()
{
    UpdateTiles_Vehicle();
    UpdateTiles_MovSticky();
}

const void Game::PushTiles_Safezone()
{
    for (int i = 1; i <= 15; i++) { safezones.push_back(Safezone(i, 1)); }
    for (int i = 1; i <= 15; i++) { safezones.push_back(Safezone(i, 8)); }
    for (int i = 1; i <= 15; i++) { safezones.push_back(Safezone(i, 14)); }
    for (int i = 1; i <= 15; i++) { safezones.push_back(Safezone(i, 15)); }
    for each (Safezone sz in safezones) { tiles.push_back(sz); }
}

const void Game::PushTiles_Road()
{
    for (int i = 1; i <= 15; i++) { roads.push_back(Road(i, 9)); }
    for (int i = 1; i <= 15; i++) { roads.push_back(Road(i, 10)); }
    for (int i = 1; i <= 15; i++) { roads.push_back(Road(i, 11)); }
    for (int i = 1; i <= 15; i++) { roads.push_back(Road(i, 12)); }
    for (int i = 1; i <= 15; i++) { roads.push_back(Road(i, 13)); }
    for each (Road r in roads) { tiles.push_back(r); }
}

const void Game::PushTiles_Aqua()
{
    for (int i = 1; i <= 15; i++) { aquas.push_back(Aqua(i, 3)); }
    for (int i = 1; i <= 15; i++) { aquas.push_back(Aqua(i, 4)); }
    for (int i = 1; i <= 15; i++) { aquas.push_back(Aqua(i, 5)); }
    for (int i = 1; i <= 15; i++) { aquas.push_back(Aqua(i, 6)); }
    for (int i = 1; i <= 15; i++) { aquas.push_back(Aqua(i, 7)); }
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

const void Game::PushTiles_Goal()
{
    goals.push_back(Goal(3, 2));
    goals.push_back(Goal(6, 2));
    goals.push_back(Goal(9, 2));
    goals.push_back(Goal(12, 2));
    goals.push_back(Goal(15, 2));

    for each (Goal g in goals) { tiles.push_back(g); }
}

const void Game::SetupTiles_Vehicle()
{
    //Flush the vectors in case of a game restart
    cars.clear(); vans.clear(); trucks.clear(); vehicles.clear();

    //Load vehicles into corresponsing vectors here
    cars.push_back(Car(15, 13, 20, "left"));
    cars.push_back(Car(2, 13, 20, "left"));

    cars.push_back(Car(2, 11, 20, "left"));
    cars.push_back(Car(6, 11, 20, "left"));
    cars.push_back(Car(6, 11, 20, "left"));

    cars.push_back(Car(1, 9, 5, "right"));
    cars.push_back(Car(7, 9, 5, "right"));
    cars.push_back(Car(12, 9, 5, "right"));

    CreateVan(4, 12, 2,40,"right");
    CreateTruck(1, 10, 3, 20, "right");

    //These loops put all vehicle types in the vehicles list
    //DO NOT MODIFY

    for (auto& car : cars) { vehicles.push_back(car); }
    for (auto& van : vans) { vehicles.push_back(van); }
    for (auto& truck : trucks) { vehicles.push_back(truck); }
}

// Handles the creation of logs with a specified length. Makes it more efficient to add logs to the level
const void Game::CreateLog(const int& originX, const int& originY, const int& logLength, const int& moveDelay, const std::string& direction)
{
    int lengthCounter = 0;
    for (int i = 0; i < logLength; i++)
    {
        int newX = originX + i;

        if (newX >= 15) newX -= 15;
        logs.push_back(Log(newX, originY, moveDelay, direction));
        lengthCounter++;
    }
    std::cout << "DEBUG: A Log of length " << lengthCounter << " was created. \n";
}

// Handles the creation of trucks with a specified length. Makes it more efficient to add trucks to the level
const void Game::CreateTruck(const int& originX, const int& originY, const int& truckLength, const int& moveDelay, const std::string& direction)
{
    int lengthCounter = 0;
    for (int i = 0; i < truckLength; i++) // for however long the truck is
    {
        int newX = originX + i;

        if (newX >= 15) newX -= 15;

        trucks.push_back(Truck(newX, originY, moveDelay, direction));
        lengthCounter++;
    }
    std::cout << "DEBUG: A Truck of length " << lengthCounter << " was created. \n";
}

// Handles the creation of vans with a specified length. Makes it more efficient to add vans to the level. 
// This one is purely for flexibility. Vans SHOULD only be 2 tiles wide
const void Game::CreateVan(const int& originX, const int& originY, const int& vanLength, const int& moveDelay, const std::string& direction)
{
    int lengthCounter = 0;
    for (int i = 0; i < vanLength; i++) // for however long the van is
    {
        int newX = originX + i;

        if (newX >= 15) newX -= 15;

        vans.push_back(Van(newX, originY, moveDelay, direction));
        lengthCounter++;
    }
    std::cout << "A van of length " << lengthCounter << " was created\n";
}

const void Game::SetupTiles_MoveableStickies()
{
    //Flush vectors in case game has been restarted
    logs.clear(); lillypads.clear(); movStickies.clear();

    //Create logs here using the "CreateLog" function
    CreateLog(11, 3, 3, 50, "left");
    CreateLog(1, 4, 4, 30, "right");
    CreateLog(4, 5, 5, 20, "left");
    CreateLog(9, 6, 4, 30, "right");
    CreateLog(3, 7, 4, 10, "left");

    //Add lillypads here.
    lillypads.push_back(Lillypad(1, 5, 20, "left"));

    //loop through both log and lillypad vectors and pass pointers to each object to the movStickies vector
    for (auto& log : logs) { movStickies.push_back(&log); }
    for (auto& lillypad : lillypads) { movStickies.push_back(&lillypad); }
}

// Functions to calculate movements of tiles

const void Game::UpdateTiles_Vehicle()
{
    for (auto& v : vehicles) { v.CalculateMove(); }
}

const void Game::UpdateTiles_MovSticky()
{
    for (MovableSticky* s : movStickies) 
    { 
        s->CalculateMove();
        s->UnlinkPlayer();
    }
}

// ------------------------------------------

const int Game::GetGoalTakenCount() const
{
    int goalCount = 0;
    for (Goal g : goals)
    {
        if (g.IsTaken()) goalCount++;
    }
    return goalCount;
}

const int Game::GetGoalTotalCount() const
{
    return goals.size();
}

void Game::ResetGoals()
{
    for (Goal &g : goals)
    {
        g.SetIsTaken(false);
    }
}