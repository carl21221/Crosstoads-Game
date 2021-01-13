#include "Log.h"

Log::Log(int x, int y, int moveDelay)
{
	this->x = x;
	this->y = y;
	this->symbol = LOG;
	this->moveTimerMax = moveDelay;
	this->moveTimer = moveTimerMax;
	this->direction = "left";
	this->player = nullptr;
}
Log::Log(int x, int y, int moveDelay, std::string direction)
{
	this->x = x;
	this->y = y;
	this->symbol = LOG;
	this->moveTimerMax = moveDelay;
	this->moveTimer = moveTimerMax;
	this->player = nullptr;

	if (IsDirectionValid(direction)) this->direction = direction;
	else this->direction = "left";
}

void Log::LinkPlayer(Player& p)
{
	if (p.GetX() == this->x && p.GetY() == this->y)
	{
		std::cout << "Player linked to log";
		this->player = &p;
	}
	else this->player = nullptr;
}

void Log::UnlinkPlayer() 
{ 
	std::cout << "unlinked from log";
	this->player = nullptr;
}

void Log::CalculateMove()
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