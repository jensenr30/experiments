#include <stdio.h>

// C++ to C adaptions
#define bool char
#define true 1
#define false 0

//#include "lualib.h"
//#include "lauxlib.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <math.h>

//super low level things.
//ths stuff contained in these headers is basic is used pretty much everywhere.
#include "globals_headers.h"

#include "tile_item_def.h"
#include "being_def.h"
#include "party_def.h"
#include "map_def.h"

// necessary right-away function definitions:
// these function prototypes are necessary for the program to compile.
//some of these are here to keep the compiler quiet.
SDL_Surface *load_image( char *filename );
void apply_surface_clips( int, int,  SDL_Surface *, SDL_Surface *, SDL_Rect * );
void map_erase(struct map *);
void apply_surface(int, int, SDL_Surface *, SDL_Surface *);
int apply_text(int, int, TTF_Font *, char *, SDL_Color );
int within_rect(int, int, SDL_Rect *);
int handle_error(int, char*);
int get_tile( int , int  );
void zoom(int);
void apply_item_coor( int, int, int);
int new_game(char*);
void portal_copy(struct mapPortal *, struct mapPortal *);


//low level things. these contain mostly programming utilities for De_Flux developers. lots of functions.
#include "buttons.h"
#include "functs.h"

#include "tile_item_functs.h"
#include "being_functs.h"
#include "player_inv.h"
#include "player_inv_functs.h"
#include "graphics_functs.h"
#include "party_functs.h"
#include "map_functs.h"

//higher-level things. these things use the previous things.
#include "options.h"
#include "inv.h"
#include "battle.h"
#include "gameplay_functs.h"
#include "mapmaker.h"
#include "main_menu.h"


int main( int argc, char* args[] ){
	
	//handle_error(1234, NULL); // pointless box
	
	reset_playerVariables(&player);

    //Initialize
    if( init() == false ) return 1;
    //Load the files
    if( load_files() == false) return 2;

    //startUpScreen();
    while(SDL_PollEvent(&event)) if(event.type == SDL_QUIT) quit_game(); // clear events before moving on from the splash screen. quit if the user tries to press the exit button during the loading screen.

    //initialize the buttons and buttons sets
    init_buttons();
    init_map_maker_inventory();
	init_tile_attributes(); // sets the tile attributes (see "tile_and_item_functions.h")
	init_item_attributes(); // sets the item attributes (see "tile_and_item_functions.h")


    while(1){
    	// go to the title screen
    	char game_function = main_menu();
    	if     (game_function == -1 || game_function == 2){ // quit game
    		quit_game();
    	}
    	else if(game_function == 0) // play game
    		new_game(NULL);
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
