#include "Truck.h"

Truck::Truck(int x, int y, int moveDelay)
{
	this->x = x;
	this->y = y;
	this->symbol = TRUCK;
	this->moveTimerMax = moveDelay;
	this->moveTimer = moveTimerMax;
}

Truck::Truck(int x, int y, int moveDelay, std::string direction)
{
	this->x = x;
	this->y = y;
	this->symbol = TRUCK;
	this->moveTimerMax = moveDelay;
	this->moveTimer = moveTimerMax;

	if (IsDirectionValid(direction)) this->direction = direction;
	else this->direction = "left";
}