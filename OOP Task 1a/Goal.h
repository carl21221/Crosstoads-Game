#pragma once
#include "Tile.h"
class Goal : public Tile
{
public:
	Goal(int x, int y);
	Goal(int x, int y, bool takenVal);

	bool IsTaken();
	void SetIsTaken(bool val);

protected:
	bool isTaken = false;

private:
};

