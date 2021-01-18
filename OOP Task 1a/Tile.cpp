#include "Tile.h"
Tile::Tile() : symbol('x')
{}

Tile::Tile(int x, int y) : x(x), y(y), symbol('x') // initalisation list . (the char of 'x' is just a placeholder for an invalid tile)
{
}

int Tile::GetX() const
{
    return x;
}

int Tile::GetY() const
{
    return y;
}

char Tile::GetSymbol() const
{
    return symbol;
}

bool Tile::IsAtPosition(int x, int y) const
{
    return this->x == x && this->y == y;
}
