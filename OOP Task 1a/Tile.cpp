#include "Tile.h"
Tile::Tile() : symbol('x')
{}

const int Tile::GetX() const
{
    return x;
}

const int Tile::GetY() const
{
    return y;
}

const char Tile::GetSymbol() const
{
    return symbol;
}

const bool Tile::IsAtPosition(int x, int y) const
{
    return this->x == x && this->y == y;
}
