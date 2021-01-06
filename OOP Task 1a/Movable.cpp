#include "Movable.h"

Movable::Movable()
{

}

int Movable::GetX() const { return x; }

int Movable::GetY() const { return y; }

bool Movable::IsReadyToMove() const
{
	return this->isReadyToMove;
}

void Movable::SetReadyToMove(bool value)
{
	this->isReadyToMove = value;
}

void Movable::SetX(int newX)
{
	this->x = newX;
}

void Movable::SetY(int newY)
{
	this->y = newY;
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
