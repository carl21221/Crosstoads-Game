#include "Log.h"

Log::Log(int x, int y, int moveDelay)
{
	this->x = x;
	this->y = y;
	this->symbol = LOG;
	this->moveTimerMax = moveDelay;
	this->moveTimer = moveTimerMax;
}