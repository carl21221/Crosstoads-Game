#pragma once
#include "Movable.h"
#include "Player.h"

class MovableSticky :  public Movable
{
public:
	void LinkPlayer(Player& p);
	void UnlinkPlayer();
	void CalculateMove(); // Overrides Movable's CalculateMove function, with added functionality
	                      // specific to the sticky object
protected:
	Player* player;
};

