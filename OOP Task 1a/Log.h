#pragma once
#include "Movable.h"
#include "Player.h"
#include <iostream>

class Log : public Movable
{
public:
	Log(int newX, int newY, int moveDelay);
	Log(int newX, int newY, int moveDelay, std::string direction);
	void LinkPlayer(Player& p);
	void UnlinkPlayer();
	void CalculateMove();
private:
	Player* player;
};

