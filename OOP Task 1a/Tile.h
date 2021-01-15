#pragma once
#include "Constants.h"
#include <string>

using namespace std;

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
    std::string GetTexturePath();

protected:
    char symbol;
    int x = 0;
    int y = 0;
    string texturePath = "";

private:

};

