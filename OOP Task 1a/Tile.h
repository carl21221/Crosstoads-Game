#pragma once
#include "Constants.h"
class Tile
{
public:
    // constructors
    Tile();
    Tile(int x, int y);

    // assessors
    int GetX() const;
    int GetY() const;
    char GetSymbol() const;
    bool IsAtPosition(int x, int y) const;

protected:
    char symbol;
    int x = 0;
    int y = 0;

private:

};

