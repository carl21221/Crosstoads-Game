#pragma once
#include "Movable.h"
class Van : public Movable
{
public:
    Van(int x, int y, int moveDelay, std::string direction);
};

