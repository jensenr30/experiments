
/* Ryan Jensen * <date> * <title>
 * <purpose>
 */
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"


//The attributes of the screen
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The surfaces that will be used
SDL_Surface* screen = 	NULL;
SDL_Surface* text = 	NULL;
SDL_Surface* image = 	NULL;

//The event structure that will be used
SDL_Event event;

//the fint that will be used
TTF_Font *font = NULL;

//The color of the text
SDL_Color textColor = { 0, 0, 0 };

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
    
    //Apply the surface to the screen
    apply_surface( 0, 0, image, screen );
    
    //Update the screen
    if( SDL_Flip( screen ) == -1 )
    {
    	return 3;
    }
    
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
    	}
    }
    
    //Free the surface and quit SDL
    clean_up();
    
    return 0;
}
