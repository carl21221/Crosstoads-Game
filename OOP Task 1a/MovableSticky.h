#pragma once
#include "Movable.h"
#include "Player.h"

class MovableSticky :  public Movable
{
public:
	void LinkPlayer(Player& p);
	void UnlinkPlayer();
	void CalculateMove();
protected:
	Player* player;
};

