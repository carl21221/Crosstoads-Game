#include "Car.h" 

Car::Car(int newX, int newY, int moveDelay)
{
	this->x = newX;
	this->y = newY;
	this->symbol = CAR;
	this->moveTimerMax = moveDelay;
	this->moveTimer = moveTimerMax;
}

