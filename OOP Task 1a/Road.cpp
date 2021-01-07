#include "Road.h"

// constructors
Road::Road()
{
	this->symbol = ROAD;
}

Road::Road(int x, int y)
{
	this->x = x;
	this->y = y;
	this->symbol = ROAD;
}