#pragma once
#include "MovableSticky.h"
class Turtle : public MovableSticky
{
public:	
	Turtle(int newX, int newY, int moveDelay, std::string direction, int sinkDelay);
	bool IsSubmerged();
	bool IsInTransition();
	void Update();
	void ToggleState();

private:
	
	int sinkDelay = 60;
	int transitionDelay = 360;
	int transitionCounter = 60;
	bool isUnderwater = false;
	bool inTransition = false;
	
};

