#include "Log.h"

Log::Log(int x, int y, int moveDelay)
{
	this->x = x;
	this->y = y;
	this->symbol = LOG;
	this->moveTimerMax = moveDelay;
	this->moveTimer = moveTimerMax;
	this->direction = "left";
	this->player = nullptr;
}
Log::Log(int x, int y, int moveDelay, std::string direction)
{
	this->x = x;
	this->y = y;
	this->symbol = LOG;
	this->moveTimerMax = moveDelay;
	this->moveTimer = moveTimerMax;
	this->player = nullptr;

	if (IsDirectionValid(direction)) this->direction = direction;
	else this->direction = "left";
}