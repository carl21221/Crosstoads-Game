#pragma once

// the size of the grid
#define SIZE      15

// symbols used for storing where things are
//Player piece
//#define PLAYER    'P'

// Safe Tiles
#define ROAD	  'R'
#define SAFEZONE  'S'
#define FLOOR     'F'

#define LOG		  'L'

// Death Tiles
#define AQUA      'A'
#define CAR		  'C'
#define VAN		  'V'
#define TRUCK     'T'

// Other Tiles
#define GOAL      'G'
#define GOALTAKEN 'W' //not needed for our game, but keep it in to prevent errors during development

#define CAR_SPEED   30; 
#define VAN_SPEED   25;
#define TRUCK_SPEED 45;
#define LOG_SPEED 25;
#define LILLYPAD    'P'

// the command letters to move the mouse on the maze
#define KEY_RIGHT 262
#define KEY_LEFT  263
#define KEY_DOWN  264
#define KEY_UP    265
#define SPACEBAR  32
#define ESCAPE    27

//Size and Position values
#define GAMEOVER_FONTSIZE 40;
#define GAMEOVER_TEXT "Game Over"