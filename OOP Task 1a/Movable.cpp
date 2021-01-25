#include "Movable.h"

Movable::Movable()
{
}

void Movable::Update()
{
	CalculateMove();
}


// Moves if the object is ready to move, otherwise decrement the move timer
// by 1. Should be called every frame.
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

std::string Movable::GetDirection() const { return this->direction; }

// A support function used to ensure the direction string passed in to
// the constructor is valid.
const bool Movable::IsDirectionValid(const std::string& direction) const
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

//Called when the object has moved
void Movable::ResetMoveTimer() { this->moveTimer = this->moveTimerMax; }

// Called when we are wanting to move the object in a specific direction
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

