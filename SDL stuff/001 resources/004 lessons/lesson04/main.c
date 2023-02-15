/* Ryan Jensen * <date> * <title>
 * <purpose>
 */
#include "functions.h"

//The attributes of the screen
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The surfaces that will be used
SDL_Surface* screen = NULL;
SDL_Surface* pixel = NULL;

int main( int argc, char* args[] )
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) return -1;
    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    //If there was an error in setting up the screen, return -1
    if( screen == NULL ) return -1;
    //Set the window caption
    SDL_WM_SetCaption( "Ryan's SDL Program", NULL );
    
    
    
    
    
    //wait 2 sec
    SDL_Delay( 2000 );
    //Free the surfaces
    
    //Quit SDL
    SDL_Quit();
    return 0;
}

