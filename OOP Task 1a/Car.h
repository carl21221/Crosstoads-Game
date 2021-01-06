#pragma once
class Car
{
    public:
        Car();

        int GetX();
        int GetY();
        char GetSymbol() const;
        bool IsAtPosition(int x, int y);

        void Move();    //as parameter, use ticks to move
        

    private: 
        int x = 0;
        int y = 0;
};
