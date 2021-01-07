#pragma once
#include "Tile.h"
class Goal : public Tile
{
public:
	Goal(int x, int y);
private:
	bool isTaken = false;
};

