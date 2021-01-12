#pragma once
#include "Movable.h"
#include "Player.h"

class Log : public Movable
{
public:
	Log(int newX, int newY, int moveDelay);
	Log(int newX, int newY, int moveDelay, std::string direction);
private:
	Player* player;
};

