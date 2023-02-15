
/* Ryan Jensen * <date> * <title>
 * <purpose>
 */
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "Windows.h"
#include "stdlib.h"
#include "conio.h"
#include <math.h>
#include <string.h>

#define MAX_CHARGES 20
int number_of_used_charges;

#define false 0
#define true  1

typedef int bool;

//The attributes of the screen
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 900;
const int SCREEN_BPP = 32;

//The surfaces that will be used
SDL_Surface* screen =	NULL;
SDL_Surface* text = 	NULL;
SDL_Surface* pro = 		NULL;
SDL_Surface* ele = 		NULL;
SDL_Surface* nue =		NULL;
SDL_Surface* white = 	NULL;
SDL_Surface* clicked = 	NULL;

//The event structure that will be used
SDL_Event event;

//the fint that will be used
TTF_Font *font = NULL;

//The color of the text
SDL_Color textColor = { 0, 0, 0 };




#include "functions.h"
#include "console_stuff.h"
#include "charges.h"


void frame( int );

int main( int argc, char* args[] )
{
	
    //Initialize
    if( init() == false )
    {
    	return 1;
    }
    
    //Load the files
    if( load_files() == false )
    {
    	return 2;
    }
    //set up all the charge values and display them on the screen.
    setup_charges();
    
	//make sure the program waits for a quit
	bool quit = false;
	
    int paused = 1, current_charge = -1;
    
    //While the user hasn't quit
    while( quit == false )
    {
    	//While there's an event to handle
    	while( SDL_PollEvent( &event ) )
    	{
    		//If the user has Xed out the window
    		if( event.type == SDL_QUIT )
			{
				//Quit the program
				quit = true;
			}
			//If space was pressed
			else if( event.type == SDL_KEYDOWN )
			{
				if(event.key.keysym.sym == SDLK_SPACE)
				{
					if(paused)
						paused = 0;
					else
						paused = 1;
				}
				else if(event.key.keysym.sym == SDLK_RETURN)
				{
					if(paused)
					{
						if(current_charge+1)
						{
							//edit_charge(current_charge);
						}
					}
				}
				else if(event.key.keysym.sym == SDLK_r)
					setup_charges();
				else if(event.key.keysym.sym == SDLK_TAB)
				{
					frame(10);
					paused = 1;
				}
			}
			//If a mouse button was pressed
			else if( event.type == SDL_MOUSEBUTTONDOWN )
			{
				int x, y;
				x = event.button.x;
				y = event.button.y;
				if(paused)
				{
					current_charge = check_mouse_click(current_charge, x, y);
				}
			}
    	}
    	if( paused == 0)
    	{
    		frame(1);
		}
    }
    
    //Free the surface and quit SDL
    clean_up();
    
    return 0;
}


void frame( int itterations )
{
	int i;
	for(i = 0; i < itterations; i++)
	{
		calc_charge_physics();
		white_screen();
		update_charges();
		SDL_Flip(screen);
		Sleep(1);
	}
}
