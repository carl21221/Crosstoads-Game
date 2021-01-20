#include "Lillypad.h"

Lillypad::Lillypad(int newX, int newY, int moveDelay, std::string direction)
{
	this->x = newX;
	this->y = newY;
	this->symbol = LILLYPAD;
	this->moveTimerMax = moveDelay;
	this->moveTimer = moveTimerMax;
	this->player = nullptr;

	if (IsDirectionValid(direction)) this->direction = direction;
	else this->direction = "left";
}