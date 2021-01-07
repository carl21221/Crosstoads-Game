#pragma once

#include <assert.h>
#include "constants.h"
#include "Tile.h"

using namespace std;

class Safezone : public Tile
{
    public:
        // constructors
        Safezone();
        Safezone(int x, int y);
};
