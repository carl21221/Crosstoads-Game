#include "Player.h"

Player::Player() : symbol(PLAYER), x(0), y(0), alive(true), escaped(false), dx(0), dy(0)
{
    PositionInMiddleOfGrid();
}

int Player::GetX()
{
    return x;
}

int Player::GetY()
{
    return y;
}

char Player::GetSymbol() const
{
    return symbol;
}

bool Player::IsAtPosition(int x, int y)
{
    return this->x == x && this->y == y;
}

void Player::Move(int key)
{
    switch (key)
    {
    case KEY_LEFT:
        dx = -1;
        dy = 0;
        break;
    case KEY_RIGHT:
        dx = +1;
        dy = 0;
        break;
    case KEY_UP:
        dx = 0;
        dy = -1;
        break;
    case KEY_DOWN:
        dx = 0;
        dy = +1;
        break;
    default:
        // not a key we care about, so do nothing
        break;
    }

    // update mouse coordinates if move is possible
    if (((x + dx) >= 1) && ((x + dx) <= SIZE) && ((y + dy) >= 1) && ((y + dy) <= SIZE))
    {
        UpdatePosition(dx, dy);
    }
}

void Player::UpdatePosition(int dx, int dy)
{
    x += dx;
    y += dy;
}

void Player::PositionInMiddleOfGrid()
{
    x = SIZE / 2;
    y = SIZE / 2;
}