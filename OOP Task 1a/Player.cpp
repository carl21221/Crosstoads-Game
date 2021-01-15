#include "Player.h"
#include <iostream>

Player::Player()
    : symbol(PLAYER), x(0), y(0), alive(true), escaped(false), dx(0), dy(0), currentLives(5), maxLives(5), direction('U')
{
    PositionAtStart();
}

int Player::GetX() const {  return x; }
int Player::GetY() const { return y; }
char Player::GetSymbol() const { return symbol; }
char Player::GetDirection() const { return this->direction; }
bool Player::IsAtPosition(int x, int y) const {  return this->x == x && this->y == y; }
int Player::GetCurrentLives() { return currentLives; }
int Player::GetMaxLives() { return maxLives; }

void Player::MoveX(int amt) // Positive number for Left, Negative for Right
{
    this->x = this->x - amt;
}

void Player::Move(int key)
{
    switch (key)
    {
    case KEY_LEFT:
        dx = -1;
        dy = 0;
        this->direction = 'L';
        break;
    case KEY_RIGHT:
        dx = +1;
        dy = 0;
        this->direction = 'R';
        break;
    case KEY_UP:
        dx = 0;
        dy = -1;
        this->direction = 'U';
        break;
    case KEY_DOWN:
        dx = 0;
        dy = +1;
        this->direction = 'D';
        break;
    default:
        // not a key we care about, so do nothing
        break;
    }

    // update mouse coordinates if move is possible
    if (((x + dx) >= 1) && ((x + dx) <= SIZE) && ((y + dy) >= 1) && ((y + dy) <= SIZE))
    {
        //CHECK FOR WALL HERE
        UpdatePosition(dx, dy);
    }
}

void Player::Die()
{
    //lose life
    this->currentLives--;
    PositionAtStart();
    std::cout << "Player Died\n";
    std::cout << "Current Lives:" << this->currentLives << "\n";
}

void Player::ResetLives() { this->currentLives = this->maxLives; }
bool Player::IsOnLog() { return this->isOnLog; }
void Player::IsOnLog(bool val) { this->isOnLog = val; }

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