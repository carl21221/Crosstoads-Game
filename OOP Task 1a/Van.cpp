#include "Van.h"

Van::Van(int x, int y, int moveDelay)
{
	this->x = x;
	this->y = y;
	this->symbol = VAN;
	this->moveTimerMax = moveDelay;
	this->moveTimer = moveTimerMax;
}