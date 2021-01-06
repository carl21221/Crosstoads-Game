#pragma once
#include "Movable.h"

class Car : public Movable
{
    public:
        Car();
        
    private: 
        int x = 0;
        int y = 0;
};
