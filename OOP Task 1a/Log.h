#pragma once
#include "MovableSticky.h"
#include "Player.h"
#include <iostream>

class Log : public MovableSticky
{
public:
	Log(int newX, int newY, int moveDelay, std::string direction);
};

