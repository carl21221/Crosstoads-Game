#include "Player.h"

Player::Player()
    : x(0), y(0), dx(0), dy(0), currentLives(5), maxLives(5), direction('U')
{
    PositionAtStart();
}

const int Player::GetX() const {  return x; }

const int Player::GetY() const { return y; }

const char Player::GetSymbol() const { return symbol; }

const char Player::GetDirection() const { return this->direction; }

const bool Player::IsAtPosition(int x, int y) const {  return this->x == x && this->y == y; }

int Player::GetCurrentLives() const { return currentLives; }

int Player::GetMaxLives() const { return maxLives; }

// Move player along the X axis. Used when linked to a MovableSticky object
// Positive number for Left, Negative for Right
void Player::MoveX(int amt) 
{
    this->x = this->x - amt;
    if (this->x < 1) { this->x = 1; }
    else if (this->x > 15) this->x = 15;
}

// Move player dependant on the keycode passed in
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
    this->currentLives--;
    PositionAtStart();
}

void Player::ResetLives() { this->currentLives = this->maxLives; }

bool Player::IsOnLog() const { return this->isOnLog; }

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