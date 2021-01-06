#pragma once

#include <assert.h>
#include "constants.h"
#include "Tile.h"

using namespace std;

class Safezone : public Tile
{
    public:
        // constructors
        Safezone(int x, int y);

    private:
        // data members
        char symbol;
        int x, y;
};
