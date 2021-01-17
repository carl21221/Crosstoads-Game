#pragma once
#include "MovableSticky.h"
#include "Player.h"

class Lillypad : public MovableSticky
{
public:
	Lillypad::Lillypad(int newX, int newY, int moveDelay, std::string direction);
private:
	Player* player;
};

