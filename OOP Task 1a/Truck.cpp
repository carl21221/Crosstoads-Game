#include "Truck.h"

Truck::Truck(int x, int y, int moveDelay)
{
	this->x = x;
	this->y = y;
	this->symbol = TRUCK;
	this->moveTimerMax = moveDelay;
	this->moveTimer = moveTimerMax;
}