#include "Turtle.h"

Turtle::Turtle(int newX, int newY, int moveDelay, std::string direction, int sinkDelay)
{
	this->x = newX;
	this->y = newY;
	this->symbol = TURTLE;
	this->moveTimerMax = moveDelay;
	this->moveTimer = moveTimerMax;
	this->player = nullptr;
	this->sinkDelay = sinkDelay;


	if (IsDirectionValid(direction)) this->direction = direction;
	else this->direction = "left";
}

void Turtle::Update()
{
	CalculateMove();
	UnlinkPlayer();

	if (!inTransition) //if turtle is not in transition,
	{
		if (transitionDelay <= 0)
		{
			this->inTransition = true;
			transitionDelay = 360;
		}
		else transitionDelay--;
	}
	else //otherwise calculate next state
	{
		if (transitionCounter <= 0)
		{
			ToggleState();
			transitionCounter = 60;
		}
		else transitionCounter--;
	}
}

void Turtle::ToggleState()
{
	if (isUnderwater) isUnderwater = false;
	else isUnderwater = true;
}