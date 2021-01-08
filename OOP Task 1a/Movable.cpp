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

void Movable::UpdateMoveTimer(int amount) 
{
	this->moveTimer = this->moveTimer - amount;
	if (this->moveTimer <= 0)
	{
		this->isReadyToMove = true;
		ResetMoveTimer(); // set timer to max
	}
}

void Movable::ResetMoveTimer() { this->moveTimer = 30; } // this->moveTimerMax; }

void Movable::UpdateX(int value)
{
	this->x = this->x - value;
	if(this->x <= 0) this->x = 15;

	SetReadyToMove(false); //once moved, set bool to false
}

