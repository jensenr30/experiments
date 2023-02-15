
/* Ryan Jensen * <date> * <title>
 * <purpose>
 */
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <Windows.h>
#include "stdlib.h"
#include "conio.h"
#include <math.h>
#include <string.h>

#define MAX_CHARGES 200
int number_of_used_charges;

#define false 0
#define true  1

typedef int bool;

//The attributes of the screen
int SCREEN_WIDTH = 1000;
int SCREEN_HEIGHT = 700;
int SCREEN_BPP = 32;

//The surfaces that will be used
SDL_Surface* screen =		NULL;
SDL_Surface* text = 		NULL;
SDL_Surface* pro = 			NULL;
SDL_Surface* ele = 			NULL;
SDL_Surface* nue =			NULL;
SDL_Surface* grid_section = NULL;
SDL_Surface* clicked = 		NULL;

//The event structure that will be used
SDL_Event event;

//the font that will be used
TTF_Font *font = NULL;
int font_size = 15;

//The color of the text
SDL_Color textColor = { 255, 32, 32 };

//this is the user-selected charge
int current_charge;
//this tells if the sim is paused or not. 0 = simulating, 1 = paused
short int paused = 1;
//this is used to tell time;
double time_el = 0.00;
//this is how much time each increment is.
double time_inc = 0.0005; // one millisecond of simulation

void create_new_charge(int, int);
void frame( int );

#include "keys.h"
#include "functions.h"
//#include "console_stuff.h"
#include "charges.h"


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
    
    //tell the user where he/she can find more instructions 
    text = TTF_RenderText_Blended( font, "Ctrl + Left Click to place a charge!", textColor );
    apply_surface( SCREEN_WIDTH/2 - 200 , SCREEN_HEIGHT/2 - 100, text, screen);
    text = TTF_RenderText_Blended( font, "Ctrl + Right Click to delete it!", textColor );
    apply_surface( SCREEN_WIDTH/2 - 200 , SCREEN_HEIGHT/2 - 75, text, screen);
    text = TTF_RenderText_Blended( font, "Check out the Read Me.txt file for", textColor );
    apply_surface( SCREEN_WIDTH/2 - 200 , SCREEN_HEIGHT/2 - 50, text, screen);
    text = TTF_RenderText_Blended( font, "a brief guide to this program!", textColor );
    apply_surface( SCREEN_WIDTH/2 - 200 , SCREEN_HEIGHT/2 - 25, text, screen);
    SDL_Flip(screen);
	//make sure the program waits for a quit
	bool quit = false;
    int x, y;
    
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
			//If a key was released
			if( event.type == SDL_KEYUP )
			{
				short int k = event.key.keysym.sym;
				if(k == SDLK_LCTRL || k == SDLK_RCTRL) key_control_pressed = 0;
				if(k == SDLK_LSHIFT || k == SDLK_RSHIFT) key_shift_pressed = 0;
			}
			//If space a key was pressed
			else if( event.type == SDL_KEYDOWN )
			{
				short int k = event.key.keysym.sym;
				if(k == SDLK_SPACE)
				{
					if(paused)
						paused = 0;
					else
						paused = 1;
				}
				else if(k == SDLK_LCTRL || k == SDLK_RCTRL)
					key_control_pressed = 1;
				else if(k == SDLK_RETURN)
				{
					if(paused)
					{
						if(current_charge+1)
						{
							//edit_charge(current_charge);
						}
					}
				}
				else if(k == SDLK_ESCAPE)
				{
					time_el = 0;
					setup_charges();
					paused = 1;
				}
				else if(k == SDLK_TAB)
				{
					paused = 1;
					frame(10);
				}
				else if(k == SDLK_LSHIFT || k == SDLK_RSHIFT)
					key_shift_pressed = 1;
				else if(k == SDLK_DELETE)
				{
					delete_charge(-1,-1);
					frame(0);
				}
			}
			//If a mouse button was pressed
			else if( event.type == SDL_MOUSEBUTTONDOWN )
			{
				int modifier;
				int mouse = event.button.button;
				x = event.button.x;
				y = event.button.y;
				if(key_shift_pressed) 	modifier = 20;
				else 				modifier = 1;
				
				if(mouse == 1) // left click
				{
					mouse_button_1 = 1;
					get_current_charge(x, y);
					if(key_control_pressed)
						create_new_charge(x, y);
				}
				else if(mouse == 2) //middle click
				{
					if(key_control_pressed) break;
						toggle_charge(x, y);
				}
				else if(mouse == 3) //right click
				{
					if(key_control_pressed)
						delete_charge(x, y);
				}
				else if(mouse == 4) //scroll up
				{
						modify_charge_charge(10*modifier);
				}
				else if(mouse == 5) //scroll down
				{
						modify_charge_charge(-10*modifier);
				}
			}
			else if( event.type == SDL_MOUSEBUTTONUP )
			{
				int mouse = event.button.button;
				if(mouse == 1)
					mouse_button_1 = 0;
			}
			else if( event.type == SDL_MOUSEMOTION)
			{
				x = event.motion.x;
				y = event.motion.y;
				if(current_charge >= 0 && current_charge < MAX_CHARGES && mouse_button_1)
				{
					charges[current_charge].position[0] = x;
					charges[current_charge].position[1] = y;
					frame(0);
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

//if you send frame a zero, it doesn't calculate physics behavior. just updates the screen.
void frame( int itterations )
{
	int i;
	if( itterations == 0 )
	{
		white_screen(1);
		update_charges();
		SDL_Flip(screen);
		return;
	}
	
	for(i = 0; i < itterations; i++)
	{
		time_el += time_inc;
		calc_charge_physics();
		white_screen(1);
		update_charges();
		SDL_Flip(screen);
		Sleep(1);
	}
}
