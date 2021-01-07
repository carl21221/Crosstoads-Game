#include "Movable.h"

Movable::Movable()
{
}

bool Movable::IsReadyToMove() const
{
	return this->isReadyToMove;
}

void Movable::SetReadyToMove(bool value)
{
	this->isReadyToMove = value;
}

void Movable::DecrementMoveTimer(int amount) 
{
	moveTimer = moveTimer - amount;
	if (moveTimer <= 0)
	{
		this->isReadyToMove = true;
		this->moveTimer = this->moveTimerMax;
	}
}

void Movable::MoveX(int value)
{
	if (value >= 0) this->x = this->x + value;
}

void Movable::MoveY(int value)
{
	if (value >= 0) this->y = this->y + value;
}
