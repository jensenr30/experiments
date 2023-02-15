#include <stdio.h>
#include "Windows.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "time.h"
#include <math.h>

//definitions
#define MAX_COUNT  150
#define false 0 // c++ adaption
#define true 1  // c++ adaption

///--------------------------------------------------------------------------------------------------------
/// the following variables are all for debugging/error output.
///--------------------------------------------------------------------------------------------------------
// all debugging/error output will (or, at least, SHOULD) go to the "debug.txt" and "error.txt" files.
// print all error and debugging information to those files with fprintf.
// the FILE pointers are debugFile and errorFile respectively.
#define DEBUG 1 // general debug output.
#define DEBUG_QUIT_INFO 1 // this will print to the 
#define DEBUG_IS_EMPTY_FILE 0 // this debugs specifically the is_empty_file() function.

#define DEBUG_ORGANIZE_INVENTORIES 0// this is for debugging the organize_inventories() function
#define DEBUG_EVALUATE_INVENTORIES 0// debugs the evaluate_inventories() function

#define DEBUG_EVALUATE_PLAYER_MOVEMENT 0// this is for debug output from the evaluate_player_movement() function

#define PARAGRAPH_DEBUG_OUTPUT 0 // this is for debugging output for the paragraph_to_lines() function
#define PARAGRAPH_ERROR_OUTPUT 1 // this is for error output for the paragraph_to_lines() function


//allowing us to use the bool type. you might want to remove this definition if you are going to try to compile this project as a C++
#define bool char
#define false 0
#define FALSE 0
#define true 1
#define TRUE 1

//The CONSTANT initial size of the screen
#define DEFAULT_SCREEN_WIDTH 896
#define DEFAULT_SCREEN_HEIGHT 576
//The DYNAMIC  initial size of the screen
unsigned int SCREEN_WIDTH = DEFAULT_SCREEN_WIDTH;
unsigned int SCREEN_HEIGHT = DEFAULT_SCREEN_HEIGHT;


#define NUMBER_OF_GUI_SIZES 3
// this is the native image size (32x32 pixels)
#define ITEM_SIZE_BASE 0x20
// this is the gui size. it corresponds to how large the item sizes will be. 1=32, 2=64, 3=96, etc...
// this number indexes into the item_set[] array.
unsigned short GUI_SIZE = 2;
#define ITEM_SIZE (GUI_SIZE*ITEM_SIZE_BASE)
//unsigned short ITEM_SIZE[NUMBER_OF_GUI_SIZES] = {0x20, 0x40, 0x80, 0x100}; // 13,32,48, and 64
// item_set[0] is null. it is not inteneded to be used.
// ietm_set[1] is the normal size
// item_set[2] is twice the size
// item_set[3] is three times the size
// etc...
SDL_Surface *item_set[NUMBER_OF_GUI_SIZES+1] = 	{NULL,NULL,NULL,NULL};	// this is what holds all of the item sprites

#define SCREEN_BPP 32

//global variable that tells us if the game is paused or not
int paused = 0;
// global variable that tells you the FPS of the game.
int FPS = 404; // arbitrary initial value

// The surfaces that will be used
SDL_Window *window = 		NULL;	// this is the window that will be used.
SDL_Renderer *renderer =	NULL;	// this is the renderer that will be used.
SDL_Surface *screen = 		NULL;	// this is the surface the player sees.
SDL_Surface *gridSurface =	NULL;	// this holds the printout of the world grid.
SDL_Surface *skySurface =	NULL;	// this holds the gradient for the sky.
SDL_Surface *text = 		NULL;	// this is a general purpose text surface.
SDL_Surface *icon = 		NULL;	// this holds the icon for the game.
// The event structure that will be used
SDL_Event event;

// this is the file that all error messages get written to
FILE *errorFile = NULL;
// this is what gets debugging information printed to it.
FILE *debugFile = NULL;

// the fint that will be used
TTF_Font *font = NULL;
TTF_Font *font16=NULL;
TTF_Font *font_tooltip=NULL; // this is the font for the tooltips.
#define FONT_SIZE_TOOLTIP 14

//The color of the text
SDL_Color textColor = { 255, 255, 255 };

// id for changing materials
int currentMat = 1;

// mouse moddifier used for brushes
short mouseModifier = 0;

// necessary function prototypes.
// this is so that functions that use THESE functions can be compiled before THESE functions are implemented.
void setcell(int , int, int);
void apply_surface( int x, int y,  SDL_Surface* source, SDL_Surface* destination );
void apply_surface_clips( int x, int y,  SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip );
Uint32 get_pixel(SDL_Surface *surface, int x, int y);
void scale_surface(SDL_Surface *sour, SDL_Surface *dest, short scalingFactor);
void clean_up();
//void inventory_display(struct inventoryData *inv, SDL_Surface *dest);

// include all of the other header files that have proprietary functions and variables that will be used throughout the program.
#include "game_time.h"
#include "words.h"

#include "general_functions.h"
#include "materials_and_cells.h"
#include "items.h"
#include "inventory.h"

#include "npc.h"
#include "quests.h"
#include "player.h"
#include "player_movement.h"

#include "cell_engine.h"
#include "graphics.h"
#include "map_editor.h"
#include "world_gen.h"



