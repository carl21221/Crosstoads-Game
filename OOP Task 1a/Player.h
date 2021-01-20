#pragma once

#include "constants.h"

class Player
{
    public:
        // constructor
        Player();

        // assessors
        const int GetX() const;
        const int GetY() const;
        const char GetSymbol() const;
        const char GetDirection() const;
        const bool IsAtPosition(int x, int y) const;
        int GetCurrentLives() const;
        int GetMaxLives() const;
        bool IsOnLog() const;

        // mutators
        void Move(int key);
        void MoveX(int amt);
        void Die();
        void ResetLives();
        void PositionAtStart();

    private:
        int maxLives;
        int currentLives;
        int dx;
        int dy;
        char symbol;
        int  x, y;
        bool isOnLog = false;
        char direction = 'U';

        void IsOnLog(bool val);
        void UpdatePosition(int dx, int dy);
};