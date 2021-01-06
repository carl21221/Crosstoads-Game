#pragma once
class Movable
{
public:
	// constructors
	Movable();

	//Getters
	int GetX() const; // Returns the x coordinate of the tile
	int GetY() const; // Returns the y coordinate of the tile
	bool IsReadyToMove() const; // Returns whether the tile is ready to move or not

	//Setters
	void SetReadyToMove(bool value); // sets whether the tile is ready to move to a specific boolean value
	void SetX(int newX); // Sets a new X coordinate
	void SetY(int newY); // Sets a new Y coordinate

	//Other Functions
	void DecrementMoveTimer(int amount); // Decrements the the move cooldown timer of the tile. If the hits 0, the timer resets
	void MoveX(int value); //Moves the tile a specified amount of spaces left

private:
	int x = 0;
	int y = 0;
	int moveTimerMax = 60;
	int moveTimer = 0;
	bool isReadyToMove = false;
};

