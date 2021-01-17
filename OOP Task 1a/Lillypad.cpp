#include "Lillypad.h"

Lillypad::Lillypad(int newX, int newY, int moveDelay, std::string direction)
{
	this->x = x;
	this->y = y;
	this->symbol = 'P';
	this->moveTimerMax = moveDelay;
	this->moveTimer = moveTimerMax;
	this->direction = "left";
	this->player = nullptr;
}