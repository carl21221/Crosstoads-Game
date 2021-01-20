#pragma once
#include "MovableSticky.h"
#include "Player.h"
#include <iostream>

class Lillypad : public MovableSticky
{
public:
	Lillypad(int newX, int newY, int moveDelay, std::string direction);
};

