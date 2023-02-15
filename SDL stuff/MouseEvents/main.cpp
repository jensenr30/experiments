
/* Ryan Jensen * <date> * <title>
 * <purpose>
 */
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"


//The attributes of the screen
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The surfaces that will be used
SDL_Surface* screen = NULL;
SDL_Surface* buttonSheet = NULL;

//The event structure that will be used
SDL_Event event;



#include "functions.h"



int main( int argc, char* args[] )
{
	//make sure the program waits for a quit
	bool quit = false;
	
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
    
    //Clips the sprite sheet
    set_clips();
    
    //Make the button
    Button myButton( 170, 120, 320, 240 );
    
    //While the user hasn't quit
    while( quit == false )
    {
    	//While there's an event to handle
    	while( SDL_PollEvent( &event ) )
    	{
    		//Handle button events
    		myButton.handle_events();
    		
    		//If the user has Xed out the window
    		if( event.type == SDL_QUIT )
			{
				//Quit the program
				quit = true;
			}
    	}
    	//Fill the screen with a white rectangle
    	SDL_FillRect( screen, &screen-clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF) );
		
		//show the button
		myButton.show();
		
		//Update the screen
		if( SDL_Flip(screen) == -1 ) return 1;
    }
    
    //Free the surface and quit SDL
    clean_up();
    
    return 0;
}
