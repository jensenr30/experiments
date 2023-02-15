/* Ryan Jensen * July 2 2012 * visual primes * this program will visually show the trend of prime numbers on a cartesian coordinate system */
#include "functions.h"

int main( int argc, char* args[] )
{
    //The attributes of the screen
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    const int SCREEN_BPP = 32;
    
    //The surfaces that will be used
    SDL_Surface* screen = NULL;
    SDL_Surface* pixel = NULL;
    
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) return -1;
    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    //If there was an error in setting up the screen, return -1
    if( screen == NULL ) return -1;
    //Set the window caption
    SDL_WM_SetCaption( "Ryan's SDL Program", NULL );
    //load the pixel
	if( ( pixel = load_image( "pixel.bmp" ) ) == NULL ) return -1;
    
    //this is where primes are calculated
    int primes[SCREEN_WIDTH]; primes[0] = 2; primes[1] = 3; primes[2] = 5; // initialize the array with 3 elements
    int nop = 3;
    int i; // used in for() loops
    short int numbaprime; // used to indicate whether or not a number is prime
    int numb2test;
    
    apply_surface( 320, 240, pixel, screen );
    SDL_Flip( screen );
    
    
    while( nop < SCREEN_WIDTH )
        {
            numbaprime = 1;
            for( i = 1; ( i < nop ); i++ )
            {
                if( primes[i] > numb2test / 2 ) break;
                if( ( numb2test % primes[i] ) == 0 ) numbaprime = 0; // if number is divisible by a prime, it is not prime
            }
            if(numbaprime)
            {
                primes[nop] = numb2test; // add the current number being checked into the primes array.
                nop++;
            }
            numb2test = numb2test + 2; // increment the number to test by 2. (move to the next odd number)
        }
	for( i = 0; i < SCREEN_WIDTH; i++ )
	{
		//draw pixel
		apply_surface( i+1, SCREEN_HEIGHT - primes[i] - 50, pixel, screen );
		//update screen
	}
	
	//update screen
	SDL_Flip( screen );
    
    
    
    //delay
    SDL_Delay( 3000 );
    //Free the surfaces
    SDL_FreeSurface( pixel );
    
    //Quit SDL
    SDL_Quit();
    return 0;
}

