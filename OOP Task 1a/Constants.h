#pragma once

// the size of the grid
#define SIZE      15

// symbols used for storing where things are
//Player piece
#define PLAYER    'P'

// Safe Tiles
#define FLOOR     'F'
#define LOG		  'L'
#define SAFEZONE  'S'
#define ROAD	  'R'

// Death Tiles
#define AQUA      'A'
#define CAR		  'C'
#define VAN		  'V'
// Others
#define WALL      'W' //not needed for our game, but keep it in to prevent errors at the moment

// the command letters to move the mouse on the maze
#define KEY_RIGHT 262
#define KEY_LEFT  263
#define KEY_DOWN  264
#define KEY_UP    265