#include "Safezone.h"

// constructors
Safezone::Safezone()
{
	this->symbol = SAFEZONE;
}

Safezone::Safezone(int x, int y)
{
	this->x = x;
	this->y = y;
	this->symbol = SAFEZONE;
}
