#pragma once
#include "Movable.h"
class Truck : public Movable
{
public:
	Truck(int x, int y, int moveDelay);
	Truck(int x, int y, int moveDelay, std::string direction);
};

