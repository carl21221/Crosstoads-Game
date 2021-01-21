#include "MovableSticky.h"

//Links the player to the log using a pointer to the player
void MovableSticky::LinkPlayer(Player& p)
{
	if (p.GetX() == this->x && p.GetY() == this->y)	this->player = &p;
	else this->player = nullptr;
}

void MovableSticky::UnlinkPlayer() { if (this->player != nullptr) this->player = nullptr; }

// A variation of the function inherited by Movable, however this time
// it checks to see if there is a player linked. If so, move the player with it.
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
