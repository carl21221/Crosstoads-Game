#pragma once
#include "Movable.h"
class Van : public Movable
{
public:
    Van(int newX, int newY, int moveDelay);
    Van(int x, int y, int moveDelay, std::string direction);
};

