#pragma once
#include "Tile.h"
class Goal : public Tile
{
public:
	Goal(int x, int y);
	Goal(int x, int y, bool takenVal);

	const bool IsTaken() const;
	void SetIsTaken(bool val);

private:
	bool isTaken = false;
};

