#include "Turtle.h"
#include <iostream>

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

bool Turtle::IsSubmerged() { return isUnderwater; }
bool Turtle::IsInTransition() { return inTransition; }

void Turtle::Update()
{
	std::cout << "Turtle Updated.\n";
	CalculateMove();
	UnlinkPlayer();

	if (!inTransition) //if turtle is not in transition,
	{
		std::cout << "Turtle was NOT in transition\n";
		if (transitionDelay <= 0)
		{
			this->inTransition = true;
		}
		else
		{
			transitionDelay--;
			std::cout << "Transition Delay = " + to_string(transitionDelay) + ".\n";
		}
	}
	else //otherwise calculate next state
	{
		std::cout << "Turtle IS in transition\n";
		if (transitionCounter <= 0)
		{
			ToggleState();
			this->inTransition = false;
			transitionCounter = 60;
			transitionDelay = 360;
		}
		else
		{
			transitionCounter--;
			std::cout << "Transition Counter= " + to_string(transitionCounter) + ".\n";
		}

	}
}

void Turtle::ToggleState()
{
	if (isUnderwater) isUnderwater = false;
	else isUnderwater = true;
}