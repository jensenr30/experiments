#define false 0
#define true  1
/* Ryan Jensen * <date> * <title>
 * <purpose>
 */
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "Windows.h"


//The attributes of the screen
const int SCREEN_WIDTH = 550;
const int SCREEN_HEIGHT = 550;
const int SCREEN_BPP = 32;

//The surfaces that will be used
SDL_Surface* screen 	= NULL;
SDL_Surface* text 		= NULL;
SDL_Surface* background = NULL;
SDL_Surface* LED 		= NULL;
SDL_Surface* SaveUP 	= NULL;
SDL_Surface* SaveDOWN	= NULL;

//The event structure that will be used
SDL_Event event;

//the fint that will be used
TTF_Font *font = NULL;

//The color of the text
SDL_Color textColor = { 0, 0, 0 };
char *saved_sound = "saved.wav";

int LEDs[9][9] = 
{
	{0, 0, 0, 0, 0, 0, 0, 0, 0},	// 0
	{0, 0, 0, 0, 0, 0, 0, 0, 0},	// 1
	{0, 0, 0, 0, 0, 0, 0, 0, 0},	// 2
	{0, 0, 0, 0, 0, 0, 0, 0, 0},	// 3
	{0, 0, 0, 0, 0, 0, 0, 0, 0},	// 4
	{0, 0, 0, 0, 0, 0, 0, 0, 0},	// 5
	{0, 0, 0, 0, 0, 0, 0, 0, 0},	// 6
	{0, 0, 0, 0, 0, 0, 0, 0, 0},	// 7
	{0, 0, 0, 0, 0, 0, 0, 0, 0}		// 8
};

#include "functions.h"
#include "led_functions.h"






int main( int argc, char* args[] )
{
	//make sure the program waits for a quit
	int quit = false;
	
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
    
    //Apply the surface to the screen
    apply_surface( 0, 0, background, screen );
    
    //Update the screen
    if( SDL_Flip( screen ) == -1 )
    {
    	return 3;
    }
    
    int mouse, mousedown = 0; // these are used ot detect if the user has the mouse button pressed.
    int SaveButtonUP = 1;
    
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
			else if( event.type == SDL_MOUSEBUTTONUP)
			{
				mousedown = 0;
				if( withing_region(event.motion.x, event.motion.y, 75, 5, 175, 55) )
				{
					print_to_file();
					PlaySound(saved_sound, NULL, SND_ASYNC);
				}
			}
			else if( event.type == SDL_MOUSEBUTTONDOWN)
			{
				mouse = event.button.button;
				if(mouse == 2)
				{
					print_to_file();
					PlaySound(saved_sound, NULL, SND_ASYNC);
				}
				else if(mouse == 1 || mouse == 3) // left mouse button or right mouse button
				{
					LED_press_check( event.motion.x, event.motion.y, mouse );
					mousedown = mouse;
				}
				else if(mouse == 4 || mouse == 5)
				{
					invert_LEDs(); // inverts all LED data
				}
			}
			if(mousedown == 1 || mousedown == 3)
				LED_press_check(event.motion.x, event.motion.y, mousedown); // this allows the user to click and drag to turn on LEDs
			
			if(mousedown == 1 && withing_region(event.motion.x, event.motion.y, 75, 5, 175, 55) )
				SaveButtonUP = 0;
			else
				SaveButtonUP = 1;
			
			
			apply_surface(0, 0, background, screen );
			print_LEDs();
			print_save_button( SaveButtonUP );
			SDL_Flip( screen );
    	}
    }
    
    //Free the surface and quit SDL
    clean_up();
    
    return 0;
}
