#include <stdio.h>

#include "tile_and_item_definitions.h"

// C++ to C adaptions
#define bool int
#define true 1
#define false 0
//test
/*
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
*/
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <Shlobj.h>



#include "globals_and_headers.h"




// necessary right-away function definitions:
// these function prototypes are necessary for the program to compile.
SDL_Surface *load_image( char *filename );
void apply_surface_clips( int, int,  SDL_Surface *, SDL_Surface *, SDL_Rect * );
void blank_map();
void apply_surface(int, int, SDL_Surface *, SDL_Surface *);
int apply_text(int, int, TTF_Font *, char *, SDL_Color );
int within_rect(int, int, SDL_Rect *);

#include "buttons.h"
#include "functions.h"
#include "graphics_functions.h"
#include "map_functions.h"
#include "mapmaker.h"
#include "gameplay_functions.h"
#include "main_menu.h"
#include "options.h"
#include "tile_and_item_functions.h" 



int main( int argc, char* args[] ){
	//PlaySound("resources\\_spin_on.wav", NULL, SND_ASYNC);



    //Initialize
    if( init() == false ) return 1;
    //Load the files
    if( load_files() == false) return 2;
    //initialize the buttons and buttons sets
    init_buttons();
    init_map_maker_inventory();
	init_tile_attributes(); // sets the tile attributes (see "tile_and_item_functions.h")

    //apply the splash screen
    apply_surface(SCREEN_WIDTH/2 - 180/2, SCREEN_HEIGHT/2 - 180/2, splash, screen);
    if( SDL_Flip( screen ) == -1 ) return 4;
    Sleep(1500); // wait for a sec
    while(SDL_PollEvent(&event)) if(event.type == SDL_QUIT) quit_game(); // clear events before moving on from the splash screen. quit if the user tries to press the exit button during the loading screen.

    while(1){
    	// go to the title screen
    	char game_function = title_screen();
    	if     (game_function == -1 || game_function == 2){ // quit game
    		quit_game();
    	}
    	else if(game_function == 0) // play game
    		new_game();
    	else if(game_function == 1) // mapmaker
    		map_maker_environment();
		else if(game_function == 3) // options
			options();
	}


    //Free the surface and quit SDL
    clean_up();
    // quit
    return 0;
}
