
/* Ryan Jensen * <date> * <title>
 * <purpose>
 */
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

//The attributes of the screen
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 400;
const int SCREEN_BPP = 32;

//The surfaces that will be used
SDL_Surface* screen = NULL;
SDL_Surface* backdrop = NULL;
SDL_Surface* message = NULL;
SDL_Surface* upMessage = NULL;
SDL_Surface* downMessage = NULL;
SDL_Surface* leftMessage = NULL;
SDL_Surface* rightMessage = NULL;

//The font that is going to be used
TTF_Font *font = NULL;
//The color of the font
SDL_Color textColor = { 255, 255, 255 };

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
    
    //Generate the message surfaces
    upMessage    = TTF_RenderText_Solid( font, "Up was perssed.",    textColor );
    downMessage  = TTF_RenderText_Solid( font, "Down was perssed.",  textColor );
    leftMessage  = TTF_RenderText_Solid( font, "Left was perssed.",  textColor );
    rightMessage = TTF_RenderText_Solid( font, "Right was perssed.", textColor );
    
    
    //Apply the surface to the screen
    apply_surface( 0, 0, backdrop, screen );
    
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
    		//If a key was pressed
    		if( event.type == SDL_KEYDOWN )
    		{
    			//Set the proper message surface
    			switch( event.key.keysym.sym )
    			{
    				case SDLK_w:
    				case SDLK_UP: message = upMessage; break;
    				case SDLK_s:
    				case SDLK_DOWN: message = downMessage; break;
    				case SDLK_a:
    				case SDLK_LEFT: message = leftMessage; break;
    				case SDLK_d:
    				case SDLK_RIGHT: message = rightMessage; break;
					default: ;
    			}
    		}
    		//If the user has Xed out the window
    		if( event.type == SDL_QUIT )
			{
				//Quit the program
				quit = true;
			}
    	}
    	if( message != NULL )
    	{
    		//Apply the images to the screen
    		apply_surface( 0, 0, backdrop, screen );
    		apply_surface( ( SCREEN_WIDTH - message->w ) / 2, ( SCREEN_HEIGHT - message->h ) / 2, message, screen );
    		
    		//Null the surface pointer
    		message = NULL;
    	}
    	
    	//Update the screen
    	if( SDL_Flip( screen ) == -1 ) return 1;
    }
    
    //Free the surface and quit SDL
    clean_up();
    
    return 0;
}
