#pragma once

#include "constants.h"

class Player
{
    public:
        // constructor
        Player();

        // assessors
        int GetX();
        int GetY();
        char GetSymbol() const;
        bool IsAtPosition(int x, int y);

        // mutators
        void Move(int key);

        char symbol;
        int  x, y;

    private:
        // data members
        bool isAlive;
        bool escaped;
        bool alive;
        int maxLives;
        int currentLives;
        int dx;
        int dy;

        // supporting functions 
        void PositionAtStart();
        void UpdatePosition(int dx, int dy);
};