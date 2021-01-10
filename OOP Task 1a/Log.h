#pragma once
#include "Movable.h"
#include "Player.h"

class Log : public Movable
{
public:
	Log(int newX, int newY, int moveDelay);
private:
	Player* player;
};

