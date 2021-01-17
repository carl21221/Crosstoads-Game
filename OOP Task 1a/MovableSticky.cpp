#include "MovableSticky.h"

void MovableSticky::LinkPlayer(Player& p) //this allows the log to access the player's member functions
{
	if (p.GetX() == this->x && p.GetY() == this->y)
	{
		this->player = &p;
	}
	else this->player = nullptr;
}

void MovableSticky::UnlinkPlayer() { if (this->player != nullptr) this->player = nullptr; }

void MovableSticky::CalculateMove()
{
	if (this->isReadyToMove == true)
	{
		UpdateX(1);
		if (this->player != nullptr)
		{
			if (this->direction == "left") this->player->MoveX(1);
			else if (this->direction == "right") this->player->MoveX(-1);
		}
	}
	else UpdateMoveTimer(1);
}
