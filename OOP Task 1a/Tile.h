#pragma once
class Tile
{
public:
    // constructors
    Tile(int x, int y);

    // assessors
    int GetX() const;
    int GetY() const;
    char GetSymbol() const;
    bool IsAtPosition(int x, int y) const;

private:
    // data members
    char symbol;
    int x, y;
};

