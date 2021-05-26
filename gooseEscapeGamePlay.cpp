#include <iostream>
#include <cmath>
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"

extern Console out;
/*
With graphics, screens are given an x,y coordinate system with the origin
in the upper left corner.  So it means the coordinate axes are:
---------------->   x direction
|
|
|
|
|
V

y direction 
*/
	
/*
    Print the game world
    
    The functions should draw characters to present features of the game
    board, e.g. win location, obstacles, power ups
*/

// print the game board function
void print_board(int map[NUM_ROW][NUM_COL])
{
	for (int y = 0; y < NUM_ROW; y++)
	{
    	for (int x = 0; x < NUM_COL; x++)
    	{	
    		int outChar = EMPTY;
			
			if (map[y][x] == 1)
    		{
    			outChar = WALL_CHAR;
			}
			
			terminal_put(x, y, outChar);
		}
	}
}
/*
    Do something when the goose captures the player
    
    If you want to attack or something else, this is the function you 
    need to change.  For example, maybe the two touch each other and
    then fight.  You could add a health to the Actor class that is
    updated.  Run, use weapons, it's up to you!
*/

bool overlap(Actor const & player, Actor const & other_thing)
{
    return (player.get_x() == other_thing.get_x() 
         && player.get_y() == other_thing.get_y());
}

/*
    Move the player to a new location based on the user input.  You may want
    to modify this if there are extra controls you want to add.
    
    All key presses start with "TK_" then the character.  So "TK_A" is the a
    key being pressed.
    
    A look-up table might be useful.
    You could decide to learn about switch statements and use them here.
*/

// We reprogrammed the movePlayer function to respond to the Q,W,E,A,D,Z,X,C
// keys to allow the player to move diagonally. This is given in the game
// instructions
void movePlayer(int key, Actor & player, int map[NUM_ROW][NUM_COL])
{
    int yMove = 0, xMove = 0;
    if (key == TK_Z)
    {
        yMove = 1;
        xMove = -1;
	}
    else if (key == TK_X)
        yMove = 1;
    else if (key == TK_C)
    {
        yMove = 1;
		xMove = 1;
	}
    else if (key == TK_A)
		xMove = -1;
    else if (key == TK_D)
    	xMove = 1;
    else if (key == TK_Q)
    {
    	yMove = -1;
    	xMove = -1;
    }
    else if (key == TK_W)
    	yMove = -1;
    else if (key == TK_E)
    {
        yMove = -1;
        xMove = 1;
    }
        
    if(player.can_move(xMove, yMove))
    /*checks the .can_move conditions as well as if the player is trying to move
    towards a wall. If the movement the player requests is out of the terminal
    bounds or is going to bump into a wall, the location will not update. 
    if(player.can_move(xMove, yMove))
    */
	{
		if ((map[player.get_y() + yMove][player.get_x() + xMove] != SHALL_NOT_PASS))
		{
			player.update_location(xMove, yMove);
		}
	}
}

// places DIAGONAL wall (in array) of specified length at a specified location
void place_wall(int map[NUM_ROW][NUM_COL], int y_cord, int x_cord, int length)
{
	for (int i = 0; i < length; i++)
	{
		map[y_cord + i][x_cord + i] = SHALL_NOT_PASS;
	}
}

/*
    What other functions do you need to make the game work?  What can you
    add to the basic functionality to make it more fun to play?
*/
