#include "bool.h"
#include <SDL\SDL.h>
/// this is how large the cell grid is INSIDE OF THE USER'S WINDOW
#define GRID_WIDTH (SCREEN_WIDTH/CELL_SIZE)
#define GRID_HEIGHT (SCREEN_HEIGHT/CELL_SIZE)

// these are the maximum dimensions inside of the user's window.
#define MAX_GRID_WIDTH  1000
#define MAX_GRID_HEIGHT 1000
// this is the max size the grid[][] material array can be. this should definitely be larger than MAX_GRID_WIDTH and MAX_GRID_HEIGHT.
#define GRID_WIDTH_ELEMENTS 1000
#define GRID_HEIGHT_ELEMENTS 1000




// this is a handy little definition to check to see if the some x and y values are within the grid boundaries
#define within_grid_elements(x,y) (x>=0 && x<GRID_WIDTH_ELEMENTS-1 && y>=0 && y<GRID_HEIGHT_ELEMENTS)
#define within_grid_screen(x,y) (x>=cameraX && x<cameraX+GRID_WIDTH && y>=cameraY && y<cameraY+GRID_HEIGHT)
struct cellData{
	short mat; // the material in a cell. 	// default to m_air
};
//this is the array of structures that the data for the grid is stored in.
// your entire map exists in here.
struct cellData grid[GRID_HEIGHT_ELEMENTS][GRID_WIDTH_ELEMENTS];



//this is how many different types of materials there can be in the game.
#define MAX_NUMBER_OF_UNIQUE_MATERIALS 100 // the materials (i.e. m_earth, m_spring) can have values from 0-99

struct matData {
	
	char* name;	// name of the mat
	char* desc; // description of the mat
	
	Uint32 color;	// the color of the material
	
	bool solid;	// true = walk through this material		false = cannot walk through
	
};
struct matData mats[MAX_NUMBER_OF_UNIQUE_MATERIALS];


//this defines the material types. a material type is a
//		signed short
//negative values are not actual materials, but rather flags for conditions used in evaluating the grid.
//for instance, you can use mats[5] to get gunpowder data, or you can use mats[m_gunpowder] to get gunpowder data.
//this is just for ease of code writing.
#define m_dont_care			-3  // this is used to show that we don't care what the material is.
#define m_no_change 		-1	// this material is more of a flag. It is used by the cell_engine in checking the changes to the cells in the grid.
#define m_air			0



/// material definitions

#define m_earth			1

#define m_rock			3
#define m_rubble		4
#define m_sand			5
#define m_water			6
#define m_plant			7

#define m_fire			9
#define m_log			10
#define m_leaves		11

#define m_test			23
#define m_test2			24


void mat_erase(struct matData *mat);
void init_mats();





