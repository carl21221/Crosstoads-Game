#include "Car.h" 

Car::Car(int newX, int newY, int moveDelay, std::string direction)
{
	this->x = newX;
	this->y = newY;
	this->symbol = CAR;
	this->moveTimerMax = moveDelay;
	this->moveTimer = moveTimerMax;

	if (IsDirectionValid(direction)) this->direction = direction;
	else this->direction = "left";
}

