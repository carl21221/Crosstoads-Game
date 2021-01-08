#pragma once
#include "Movable.h"

class Car : public Movable
{
    public:
        Car(int newX, int newY, int moveDelay);
};
