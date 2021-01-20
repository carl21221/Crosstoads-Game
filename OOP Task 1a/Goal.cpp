#include "Goal.h"

//Constructors
Goal::Goal(int x, int y)
{
	this->x = x;
	this->y = y;
	this->symbol = GOAL;
	this->isTaken = false;
}

Goal::Goal(int x, int y, bool takenVal)
{
	this->x = x;
	this->y = y;
	this->symbol = GOAL;
	this->isTaken = takenVal;
}

//Get
const bool Goal::IsTaken() const
{
	return this->isTaken;
}

//Set
void Goal::SetIsTaken(bool val) { this->isTaken = val; }

