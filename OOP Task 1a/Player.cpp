#include "Player.h"
#include <iostream>

Player::Player() 
    : symbol(PLAYER), x(0), y(0), alive(true), escaped(false), dx(0), dy(0), currentLives(5), maxLives(5)
{
    PositionAtStart();
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

void Player::Die()
{
    //lose life
    this->currentLives--;
    PositionAtStart();

    //DEBUGGING
    std::cout << "Player Died\n";
    std::cout << "Current Lives: " << this->currentLives;
}

int Player::GetCurrentLives() { return currentLives; }
int Player::GetMaxLives() { return maxLives; }
void Player::ResetLives() { this->currentLives = this->maxLives; }

void Player::UpdatePosition(int dx, int dy)
{
    x += dx;
    y += dy;
}

void Player::PositionAtStart()
{
    x = (SIZE / 2) + 1;
    y = SIZE - 1;
}