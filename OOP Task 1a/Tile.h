#pragma once
#include "Constants.h"
#include <string>

using namespace std;

class Tile
{
public:
    // constructors
    Tile();

    // assessors
    const int GetX() const;
    const int GetY() const;
    const char GetSymbol() const;
    const bool IsAtPosition(int x, int y) const;

protected:
    char symbol;
    int x = 0;
    int y = 0;
};

