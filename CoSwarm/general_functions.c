#include "general_functions.h"
#include <Windows.h>
#include <SDL\SDL.h>
#include "graphics.h"
#include "bool.h"
#include "materials_and_cells.h"

void quit_game(int quitFlag, char *errmsg){
	
	if(quitFlag == quit_surface_error){
		MessageBox(NULL,errmsg,"NULL surface error.", MB_OK);
	}
	
	clean_up();
	
}


 
void set_window_size(int w, int h){
	
	if(w/CELL_SIZE > MAX_GRID_WIDTH)  w = MAX_GRID_WIDTH*CELL_SIZE;
	if(h/CELL_SIZE > MAX_GRID_HEIGHT) h = MAX_GRID_HEIGHT*CELL_SIZE;
	screen = SDL_SetVideoMode( w, h, SCREEN_BPP, SDL_SWSURFACE | SDL_RESIZABLE );
	
	//If there was an error setting up the screen
	if(screen == NULL )
	{
		exit(111);
	}
	// make sure the camera is not out of bounds. if it is, force it into bounds.
	camera_verify();
}
 
 
int init(){
	//Initialize all subsystems
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ){
		return false;
	}
	
	//Set up the screen
	set_window_size(SCREEN_WIDTH, SCREEN_HEIGHT);
	
	//If there was an error setting up the screen
	if(screen == NULL ){
		return false;
	}
	
	//Set the window caption
	SDL_WM_SetCaption( "CoSwarm 0.1", NULL );
	
	//Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        MessageBox(NULL, "TTF library was not initialized correctly.", "Warning!", MB_OK);
        return false;
    }
	
	//If everything initialized fine
	return true;
}

int load_files(){
	
	icon = SDL_LoadBMP("game icon.ico");
	SDL_WM_SetIcon(icon, NULL); // sets the icon of the windows and taskbar item
	
    
    //open font file
    font = TTF_OpenFont( "FreeMonoBold.ttf", 22 );
    font16 = TTF_OpenFont( "FreeMonoBold.ttf", 16);
    
    if (font == NULL || font16 == NULL)
    {
        MessageBox(NULL, "Font FreeMonoBold was not loaded.", "Error!", MB_OK);
    }
	
	//If everything loaded fine
	return true;
}



void clean_up(){
	SDL_FreeSurface(screen);
	beasts_free_list();
	//Quit SDL
	SDL_Quit();
	TTF_Quit();
}


int get_rand(int lowBound, int highBound){
	
	// if the lowBound is higher than the highBound, then flip them around and return that.
	if(highBound < lowBound){
		return get_rand(highBound, lowBound);
	}
	
	return ( rand() % (highBound-lowBound+1) ) + lowBound;
}



/// when you call this function, it returns a 1 or a 0.
/// your chances of getting a '1' returned are chance/100,000
/// for example, if call:
/// 	roll_ht(5000);
/// then there is a 5000/100000 chance (5%) that roll_ht will return a 1.
/// "roll_ht" means, "roll hundred thousand"
int roll_ht(int chance){
	if(chance > get_rand(0,99999)) return 1; // return 1 if the number the user gave you is greater than a random number between 0 and 99999.
	return 0; // otherwise, return 0
}
