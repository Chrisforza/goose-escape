#ifndef GOOSE_ESCAPE_ACTORS
#define GOOSE_ESCAPE_ACTORS
#include <cmath>
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"
#include <cstdlib>

using namespace std;

/*
    Modify this class to contain more characteristics of the "actor".  Add
    functions that will be useful for playing the game that are specific to
    the Actor.
    
    Feel free to add additional Classes to your program.
*/

/* 
    Going further:  Learn the other syntax for implementing a class that is
    more appropriate for working with multiple files, and improve the class code.
*/

class Actor
{
  private:
    int actorChar;      
    int location_x, location_y;

  public:
    Actor()
    {
        actorChar = int('A');
        location_x = MIN_SCREEN_X;
        location_y = MIN_SCREEN_Y;
        put_actor();
    }

    Actor(char initPlayerChar, int x0, int y0)
    {
        change_char(initPlayerChar);
        location_x = MIN_SCREEN_X;
        location_y = MIN_SCREEN_Y;
        update_location(x0,y0);
        put_actor();
        terminal_refresh();
    }
    
    int get_x() const
    {
        return location_x;
    }
    
    int get_y() const
    {
        return location_y;
    }
    
    /*
	string get_location_string() const
    {
        char buffer[80];
        itoa(location_x,buffer,10);
        string formatted_location = "(" + string(buffer) + ",";
        itoa(location_y,buffer,10);
        formatted_location += string(buffer) + ")";
        return formatted_location;
    }
    */
    
    void change_char(char new_actor_char)
    {
        actorChar = min(int('~'), max(int(new_actor_char), int(' ')));
    }

    bool can_move(int delta_x, int delta_y) const
    {
        int new_x = location_x + delta_x;
        int new_y = location_y + delta_y;

        return new_x >= MIN_BOARD_X && new_x <= MAX_BOARD_X
          && new_y >= MIN_BOARD_Y && new_y <= MAX_BOARD_Y;
    }

    void update_location(int delta_x, int delta_y)
    {
        if (can_move(delta_x, delta_y))
        {
            terminal_clear_area(location_x, location_y, 1, 1);
            location_x += delta_x;
            location_y += delta_y;
            put_actor();
        }
    }
    
    void put_actor() const
    {
        terminal_put(location_x, location_y, actorChar);
        terminal_refresh();
    }
    
    // goose chasing A.I. - this is programmed as part of the class function so
    // that in the future we can possibly implement multiple geese. More on that
    // in week 2!
    void chasePlayer(Actor & player)
    {
    	int delta_x = (*this).get_x() - player.get_x();
    	int delta_y = (*this).get_y() - player.get_y();
    	
    	if(delta_y < 0 && delta_x < 0)
    	{
    		update_location(1,1);
		}
		else if(delta_y < 0 && delta_x > 0)
		{
			update_location(-1,1);
		}
		else if(delta_y > 0 && delta_x < 0)
		{
			update_location(1,-1);
		}
		else if(delta_y > 0 && delta_x > 0)
		{
			update_location(-1,-1);
		}
		else if(delta_y < 0 && delta_x == 0)
		{
			update_location(0,1);
		}
		else if(delta_y == 0 && delta_x > 0)
		{
			update_location(-1,1);
		}
		else if(delta_y > 0 && delta_x == 0)
		{
			update_location(0,-1);
		}
		else if(delta_y == 0 && delta_x < 0)
		{
			update_location(1,0);
		}
	}
    
};
#endif
