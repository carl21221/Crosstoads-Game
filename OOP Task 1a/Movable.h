#pragma once
#include "Tile.h"
#include <string>

class Movable : public Tile
{
public:
	// constructors
	Movable();

	//Getters
	bool IsReadyToMove() const;
	std::string GetDirection() const;

	//Setters
	void SetReadyToMove(bool value); 
	void SetDirection(std::string direction);

	//Mutators
	void CalculateMove();
	void UpdateMoveTimer(int amount);
	void UpdateX(int value);
	void Update();

protected:
	int moveTimerMax = 60;
	int moveTimer = 0;
	bool isReadyToMove = false;
	std::string direction = "left";

	void ResetMoveTimer();
	const bool IsDirectionValid(const std::string& direction) const;

};

