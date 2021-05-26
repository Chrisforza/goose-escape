// Goose Escape Game Week 2 Submission
// BY: Alexander Zona and Christian Sforza

// sound code and libraries from this adress: 
// https://www.youtube.com/watch?v=7pTUeSPFhIM&ab_channel=The8-BitGuy

#include <BearLibTerminal.h>
#include <cmath>
#include <windows.h>
#include "mmsystem.h"
#include <iostream>
#include <string>
#include <ctime>
using namespace std;
#include "gooseEscapeGamePlay.hpp"
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"

//set up the console.   Don't modify this line!
Console out;

int main()
{
	// Declare the array that will hold the game board "map" 
	int map[NUM_ROW][NUM_COL] = {0};
	//populates array with 0's
	for (int i = 0; i < NUM_ROW; i++)
	{
		for (int i = 0; i < NUM_COL; i++)
		{
			map[NUM_ROW][NUM_COL]= EMPTY;
		}
	}
	
	//Set up the window.  Don't edit these two lines
    terminal_open();
	terminal_set(SETUP_MESSAGE);

/*
    The code below provides a skeleton of the game play.  You will need to
    write code for setting up the game board, and playing the game itself.
    You can modify the code given as needed.
    
    Call the functions that you have written in the game play file, and that
    you have added to the Actor class.
*/

	
// inserts wall into map by replacing the data at the wall location with 1, randomly places 3 walls
	srand(time(0));
	for (int i = 0; i < NUM_WALLS; i++)
	{
		int wall_x = 0;
		int wall_y = 0;
		int wall_length = 0;
		wall_x = rand()%(NUM_COL-MAX_WALL_LENGTH);
		wall_y = rand()%(NUM_ROW-MAX_WALL_LENGTH);
		wall_length = rand()%(MAX_WALL_LENGTH+2);
		
		place_wall(map, wall_y, wall_x, wall_length);
	}
	
 	// Call the function to print the game board
	print_board(map);
	
    //make the player - starts at a randomized location
	Actor player(PLAYER_CHAR, (rand()%NUM_COL), (rand()%NUM_ROW));  
	
	//make the monster - starts at a randomized loacation
	Actor goose(GOOSE_CHAR, (rand()%NUM_COL), (rand()%NUM_ROW));
	// safe zones are fixed actors and do not move, we do this so we can use 
	// the class values to detect when the player reaches a safe zone
	Actor safe_zone(WIN_CHAR, rand()%NUM_COL, rand()%NUM_ROW);
	
	//place four portals for easy transit across the screen
	//later in the code, overlapping with the player and any of these portals 
	//will transport them to the related portal (top to bottom & left to right)
	Actor top_portal(PORTAL_CHAR, (NUM_COL / 2), 0);
	Actor bottom_portal(PORTAL_CHAR, (NUM_COL / 2), NUM_ROW-1);
	Actor left_portal(PORTAL_CHAR, 0, (NUM_ROW / 2));
	Actor right_portal(PORTAL_CHAR, NUM_COL-1, (NUM_ROW / 2));
/*
    Initiallize locations in the game board to have game features.  What if you
    have many things to add to the game board?  Should you use a loop?  Does it
    make sense to store this information in a file?  Should this code be a
    function as well?
*/
	// Printing the instructions
    out.writeLine("Escape the Goose! Use the portals (P) to teleport across the map!");
	out.writeLine("Use Q,W,E,A,D,Z,X,C to move diagonally, up, left, right, or down");
	out.writeLine("If the goose catches you, you lose!");
	out.writeLine("Be careful! The goose can bust down walls, but you can't!");

/*
    This is the main game loop.  It continues to let the player give input
    as long as they do not press escape or close, they are not captured by
    the goose, and they didn't reach the win tile
*/
/*
    All key presses start with "TK_" then the character.  So "TK_A" is the "a"
    key being pressed.
*/
    int keyEntered = TK_A;  
	// can be any valid value that is not ESCAPE or CLOSE
    
    bool goose_can_move = true;
    
    while(keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE 
                    && !overlap(player,goose) && !overlap(player, safe_zone))
	{
	    // get player key press
	    keyEntered = terminal_read();

        if (keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE)
        {
            // move the player, you can modify this function
    	    movePlayer(keyEntered, player, map);
    	    if(overlap(player, top_portal))
			{
				PlaySound(TEXT("PORTAL.wav"),NULL,SND_SYNC);
				player.update_location(0,VERT_PORTAL_MOVE);
				top_portal.put_actor();
			}
			else if(overlap(player, bottom_portal))
			{
				PlaySound(TEXT("PORTAL.wav"),NULL,SND_SYNC);
				player.update_location(0,-VERT_PORTAL_MOVE);
				bottom_portal.put_actor();
			}
			else if(overlap(player, left_portal))
			{
				PlaySound(TEXT("PORTAL.wav"),NULL,SND_SYNC);
				player.update_location(HOR_PORTAL_MOVE,0);
				left_portal.put_actor();
			}
			else if(overlap(player, right_portal))
			{
				PlaySound(TEXT("PORTAL.wav"),NULL,SND_SYNC);
				player.update_location(-HOR_PORTAL_MOVE,0);
				right_portal.put_actor();
			}
			terminal_refresh();

            // this allows toggling the "g" key to turn on and off the goose 
			// chasing functionality. (If the game is too hard for your liking)
            if (keyEntered == TK_G)
            {
            	goose_can_move = !goose_can_move;
			}
			// calls the goose's chase function unless the 
			// goose is disabled (for testing or if the game is too hard)
			if (goose_can_move)
			{
				//the code for the chasing A.I. is found in the actor class.
				PlaySound(TEXT("HONK.wav"),NULL,SND_SYNC);
				goose.chasePlayer(player);
			}

            // After the goose "busts" down a section of the wall, the 
			// corresponding array location is changed back to empty
            // This allows the player to then travel through the hole created 
			// as per the player.can_move class function
		    if (map[goose.get_y()][goose.get_x()] == SHALL_NOT_PASS)
			{
				map[goose.get_y()][goose.get_x()] = EMPTY;
			}
            
			// refresh the terminal
			terminal_refresh();
        }
  	}

    if (keyEntered != TK_CLOSE)
    {
      	//once we're out of the loop, the game is over
    	out.writeLine("Game has ended");
        // output why:  did the goose get us, or did we get to the win location?
		
		//if the gooses x and y coordinates match the players x and y
		// coordinates at the end of the game, then player lost cuz of the goose
		if (goose.get_x() == player.get_x() && goose.get_y() == player.get_y())
		{
			out.writeLine("The goose caught you, you have perished :(");
			// Plays losing game sound effects
			PlaySound(TEXT("SCREAM.wav"),NULL,SND_SYNC);
			PlaySound(TEXT("CRASH.wav"),NULL,SND_SYNC);
		}
		// if the safe zone's x and y coordinates match the players x and y
		// coordinates at the end of the game, then the player has won!
		else if (safe_zone.get_x() == player.get_x() && safe_zone.get_y() == 
		player.get_y())
		{
			out.writeLine("You have escaped the goose.. for now...");
			PlaySound(TEXT("TITANIC.wav"),NULL,SND_SYNC);
		}

    	// Wait until user closes the window
        while (terminal_read() != TK_CLOSE)
        {
        	// do nothing, wait for the player to press escape, 
			// then exit the game
		}
	
    }

	//game is done, close the terminal and game  
    terminal_close();
}
