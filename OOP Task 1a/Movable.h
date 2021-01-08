#pragma once
#include "Tile.h"

class Movable : public Tile
{
public:
	// constructors
	Movable();

	void CalculateMove();

	//Getters
	bool IsReadyToMove() const; // Returns whether the tile is ready to move or not

	//Setters
	void SetReadyToMove(bool value); // sets whether the tile is ready to move to a specific boolean value

	//Other Functions
	void UpdateMoveTimer(int amount); // Decrements the move cooldown timer of the tile. If the hits 0, the timer resets
	void UpdateX(int value); //Moves the tile a specified amount of spaces horizontally

	void ResetMoveTimer();

protected:
	int moveTimerMax = 60;
	int moveTimer = 0;
	bool isReadyToMove = false;

private:
};

