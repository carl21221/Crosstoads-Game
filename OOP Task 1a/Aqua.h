#pragma once

#include "Tile.h"

class Aqua : public Tile
{
public:
    // constructors
    Aqua(int x, int y);

private:
    // data members
    char symbol;
    int x, y;
};

