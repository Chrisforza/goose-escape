#ifndef GOOSE_ESCAPE_GAMEPLAY
#define GOOSE_ESCAPE_GAMEPLAY
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"

using namespace std;

/*This file is all about the game world.  You will modify this to add
    constants and function prototypes.  Modify gooseGamePlay.cpp to
	actually add functionality.
*/

/*
    Declare constants to indicate various game world features in the board
    array.  Modify them to fit what you would like to do in the game.  You can
    change the type if you choose to store your game board as something other
    than intengers.
*/	
// Going further:  Learn how to use an enum for these values
const int EMPTY = 0;
const int SHALL_NOT_PASS = 1;
const int WINNER = 2;
const int NUM_ROW = 21;
const int NUM_COL = 80;
const int NUM_WALLS = 3;
const int MAX_WALL_LENGTH = 10;
const int VERT_PORTAL_MOVE = 19;
const int HOR_PORTAL_MOVE = 78;
/*
    A few examples of characters both for actors and for the game board
    itself are shown.
*/	
//display characters
const int PLAYER_CHAR = int('@');
const int GOOSE_CHAR = int('G');
const int WALL_CHAR = int('o');
const int WIN_CHAR = int('%'); //% sign, a special character used in the ancient game "Rogue"
const int PORTAL_CHAR = int('P');

/*
    Game play function prototypes are give below.
*/

// print the game board function protype
void print_board(int map[NUM_ROW][NUM_COL]);

/*
    Do something when the goose captures the player
    
    If you want to attack or something else, this is the function you 
    need to change.  For example, maybe the two touch each other and
    then fight.  You could add a health to the Actor class that is
    updated.  Run, use weapons, it's up to you!
*/
bool overlap(Actor const & player, Actor const & other_thing);

/*
    Move the player to a new location based on the user input.  You may want
    to modify this if there are extra controls you want to add.
    
    All key presses start with "TK_" then the character.  So "TK_A" is the a
    key being pressed.
    
    A look-up table might be useful.
    You could decide to learn about switch statements and use them here.
*/

void movePlayer(int key, Actor & player, int map[NUM_ROW][NUM_COL]);


/*
    What other functions do you need to make the game work?  What can you
    add to the basic functionality to make it more fun to play?
*/

//prototype function for place_wall in goose escape game play
void place_wall(int map[NUM_ROW][NUM_COL], int x_cord, int y_cord, int length);

#endif
