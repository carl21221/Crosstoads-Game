#include "Van.h"

Van::Van(int x, int y, int moveDelay, std::string direction)
{
	this->x = x;
	this->y = y;
	this->symbol = VAN;
	this->moveTimerMax = moveDelay;
	this->moveTimer = moveTimerMax;

	if (IsDirectionValid(direction)) this->direction = direction;
	else this->direction = "left";
}