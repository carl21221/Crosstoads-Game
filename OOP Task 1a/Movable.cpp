#include "Movable.h"
#include <iostream>

Movable::Movable()
{
}

void Movable::CalculateMove()
{
	if (this->isReadyToMove == true)
	{
		UpdateX(1);
	}
	else
	{
		UpdateMoveTimer(1);
	}
}

bool Movable::IsReadyToMove() const { return this->isReadyToMove; }

void Movable::SetReadyToMove(bool value) { this->isReadyToMove = value; }

void Movable::SetDirection(std::string direction)
{
	if (direction == "left") this->direction = "left";
	else if (direction == "right") this->direction = "right";
	else this->direction = "left";
}

std::string Movable::GetDirection() { return this->direction; }

bool Movable::IsDirectionValid(std::string direction)
{
	if (direction == "left") return true;
	if (direction == "right") return true;
	else return false;
}

void Movable::UpdateMoveTimer(int amount) 
{
	this->moveTimer = this->moveTimer - amount;
	if (this->moveTimer <= 0)
	{
		this->isReadyToMove = true;
		ResetMoveTimer(); // set timer to max
	}
}

void Movable::ResetMoveTimer() { this->moveTimer = this->moveTimerMax; }

void Movable::UpdateX(int value)
{
	if (this->direction == "left")
	{
		this->x = this->x - value;
		if(this->x <= 0) this->x = 15;
	}
	else if (this->direction == "right")
	{
		this->x = this->x + value;
		if (this->x > 15) this->x = 1;
	}

	SetReadyToMove(false); //once moved, set bool to false
}

