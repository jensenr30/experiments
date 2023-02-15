#include "SDL/SDL.h"
#include "functions.h"

//The attributes of the screen
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The surfaces that will be used
SDL_Surface* message = NULL;
SDL_Surface* background = NULL;
SDL_Surface* screen = NULL;

int main( int argc, char* args[] )
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) return -1;

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    //If there was an error in setting up the screen
    if( screen == NULL ) return -1;

    //Set the window caption
    SDL_WM_SetCaption( "Ryan's Program", NULL );

    //Load the images
    message = load_image( "hello.bmp" );
    background = load_image( "background.bmp" );

    //Apply the background to the screen
    apply_surface( 0, 0, background, screen );
    apply_surface( 320, 0, background, screen );
    apply_surface( 0, 240, background, screen );
    apply_surface( 320, 240, background, screen );

    //Apply the message to the screen
    apply_surface( 180, 140, message, screen );

    //Update the screen
    if( SDL_Flip( screen ) == -1 ) return -1;

    //wait 2 sec
    SDL_Delay( 2000 );

    //Free the surfaces
    SDL_FreeSurface( message );
    SDL_FreeSurface( background );

    //Quit SDL
    SDL_Quit();

    //Return
    return 0;
}
