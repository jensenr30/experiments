#include <SDL2/SDL.h>

/// block definitions
// someday I should really clean this up and remove all of the WIDTH/HEIGHT specifications and make everything SIZE.
// Because x and y are going to be the same scale for everything anyway.

// block neighbors needs  to be signed because of the "block_neighbor_all" flag
// BLOCK_NEIGHBOR definitions are NOT COMPATABILE with BLOCK_CHILD definitions.
#define BLOCK_NEIGHBORS					4
#define BLOCK_NEIGHBOR_ALL				-1
#define BLOCK_NEIGHBOR_UP				0
#define BLOCK_NEIGHBOR_DOWN				1
#define BLOCK_NEIGHBOR_LEFT				2
#define BLOCK_NEIGHBOR_RIGHT			3

// this describes how much a line is scaled when you go from one level to another.
// this is a LINEAR scale factor, meaning, the same distance looks three times as long when you zoom in once.
#define BLOCK_LINEAR_SCALE_FACTOR		3.0f
// this describes the size of each block (the size of the elevation[][] array)
#define BLOCK_WIDTH						243
#define BLOCK_HEIGHT					243
#define BLOCK_WIDTH_1_2					(BLOCK_WIDTH/2)		// integer division
#define BLOCK_HEIGHT_1_2				(BLOCK_HEIGHT/2)	// integer division
#define BLOCK_WIDTH_1_3					81
#define BLOCK_WIDTH_2_3					162
#define BLOCK_HEIGHT_1_3				81
#define BLOCK_HEIGHT_2_3				162

// this is the default elevation for all blocks. This shouldn't even be necessary. Eventually, every block will be generated with terrain specific to its zoom level and position on the map.
#define BLOCK_DEFAULT_ELEVATION			0.0f
// this is the starting level of the world (the origin block starts at level = 0.
// the children of the origin have levels -1. The children of the children of the origin have levels -2. (etc...)
// the parent of the origin has a level of 1. The parent  of the parent  of the origin has a level of 2. (etc...)
#define BLOCK_ORIGIN_LEVEL				0

// this is how many children each block will have.
// these are arranged into a square layout (3x3)
#define BLOCK_CHILDREN					9

// these describe various child locations
#define BLOCK_CHILD_TOP_LEFT			0
#define BLOCK_CHILD_TOP_CENTER			1
#define BLOCK_CHILD_TOP_RIGHT			2
#define BLOCK_CHILD_CENTER_LEFT			3
#define BLOCK_CHILD_CENTER_CENTER		4
#define BLOCK_CHILD_CENTER_RIGHT		5
#define BLOCK_CHILD_BOTTOM_LEFT			6
#define BLOCK_CHILD_BOTTOM_CENTER		7
#define BLOCK_CHILD_BOTTOM_RIGHT		8
// I don't know when I will ever use this
#define BLOCK_CHILD_INVALID				10

//	0 1 2
//	3 4 5
//	6 7 8

#define BLOCK_ELEVATION_BOUND_LOWER 		0.0f		// this is the minimum height
#define BLOCK_ELEVATION_BOUND_UPPER			1.0f		// this is the maximum height
#define BLOCK_ELEVATION_INVALID				404.0f		// this is essentially a flag in the elevation data (used in terrain generation)
#define BLOCK_ELEVATION_SLOPE_MAX_DEFAULT	0.03f		// this is the default value of slopeMax in a block
// at the present moment, the two following colors are mixed as you go from BLOCK_ELEVATION_BOUND_LOWER to BLOCK_ELEVATION_BOUND_UPPER.
#define BLOCK_ELEVATION_COLOR_LOWER 		0xff000000	// this is the color of the map for BLOCK_ELEVATION_BOUND_LOWER
#define BLOCK_ELEVATION_COLOR_UPPER 		0xffffffff	// this is the color of the map for BLOCK_ELEVATION_BOUND_UPPER

// each block can have 9 children.
// each block can have one parent.
// more children are generated as the player zooms in.
// more parents are generated as the player zooms out.
// the children of a single block enumeration:
// 0 1 2
// 3 4 5
// 6 7 8
// the numbers 0 through 8 correspond to a child of the current block (zooming in).
// the number 9 represents zooming out to see the parent of the current block.
/// this structure contains all the information that one block needs. The map is made up of a fractal arrangement of these blocks.
struct blockData{
	
	// this is the level that the block is on. origin is on level 0.
	// the parent of the origin will have a level 1 higher than the origin (1).
	// the child of the origin will have a level 1 less than the origin (-1).
	signed long long level;
	
	// this points to the block that this block is inside.
	// if this is NULL, a parent has not been generated yet.
	struct blockData *parent;
	// this is how the parent sees the child.
	// this is a number from 0 to BLOCK_CHILDREN-1.
	// if parentView = 3, then the parent of this block sees this block in its center left position.
	// if parentView = 8, then the parent of this block sees this block in its lower right position.
	char parentView;
	
	// these are pointers to child blocks.
	// these are pointers to other blocks inside of this main block.
	// each block will be split up into BLOCK_CHILDREN smaller ones.
	// these are indexed with 0,1,2,3,4,5,6,7,8.
	struct blockData *children[BLOCK_CHILDREN];
	
	// these are eight pointers to the four neighbors on the same level (up, down, left, and right
	// if these are NULL, the neighbor could exist, but it just might not be entered in this blocks neighbor's index (some neighbors are friendly than others :P)
	struct blockData *neighbors[BLOCK_NEIGHBORS];
	
	// this NEEDS to be set to NULL when you create a new block.
	// this is an image of the block elevation data.
	// it is rendered at 1 pixel per element in the elevation array. (so it is BLOCK_WIDTH by BLOCK_HEIGHT).
	// this is used to store rendered images of the texture's elevation.
	SDL_Texture *texture;
	
	// this is a flag that tells the graphics functions when they need to re-render the block.
	/// THIS NEEDS TO BE SET TO 1 TO TELL THE GRAPHICS FUNCTION TO RE RENDER IF YOU CHANGE ANYTHING IN THE ELEVATION DATA YOU GODDAMN BITCH.
	// also set this to 1 when you create a new block (so that it can be rendered for the first time).
	// when this is set to 1, the graphics functions will re-render the block's texture.
	// Said graphics functions will reset this flag to 0 when they have rendered it (so rendering is minimized and only done when needed).
	// the program does not need to render the same thing over and over each frame of the game.
	// just render it once, and let the hardware do the rest.
	char renderMe;
	
	// this is the two dimensional array of elevation values for each block.
	float elevation[BLOCK_WIDTH][BLOCK_HEIGHT];
	
	// this describes how fast the elevation of the map can change. the higher the number, the higher the frequencies that can exist in the map.
	// this relates to the frequency content of the map.
	// technically, this is used as such:
		// when interpolating between two elevation points, a first-order linear interpolation is done (establish a line between two points, and pick a point on the line as the new point of data).
		// once you have done this, you then add some randomness to this point's elevation.
		// the amount of randomness you add is directly proportional to this number.
		// this number dictates how much randomness you can add per shortest interpolation distance
		// for example:
			// lets say your two interpolation elevation values are 0.67 and 0.98.
			// lets say those two points are 8 cells away (8 elements in the elevation[][] array)
			// if the point you with to interpolate is 2 cells away from 0.67 and 6 cells away from 0.98.
			// lets also say your slope max is 0.1.
			// then the middle of the range of possible values of that number is (0.67/2 + 0.98/6)/(1/2 + 1/6) = (0.498333)/(0.666667) = 0.7475
			// the radius (the amount positive or negative) that the elevation can be randomly perturbed from that average is (slopeMax) * (minimum distance to known data point) = 0.1 * 2 = 0.2
			// so the interpolated elevation would be 0.7475 plus or minus 0.2
			// so it could be as low as 0.5475 or as high as 0.9475
	// quick and dirty, slopeMax should be between 0.1 and 0.0001.
	// anything in between there should be fine.
	// 0.0001 gives you really REALLY gradual slopes.
	// 0.1 gives you really jagged and crazy terrain.
	float slopeMax;
	
};


/*
	  /==================================================\
	 /|==================================================|\
	 ||==================================================||
	<|||==  RYAN'S BLOCK NETWORK GENERATION PROTOCOL  ==|||>
	 ||==================================================||
	 \|==================================================|/
	  \==================================================/

This protocol describes how the PROGRAM will navigate the fractal map.
The protocol is strict, but robust.
The user interface is going to be smooth and forgiving.
the USER INTERFACE and the PROGRAM'S BLOCK NETWORK PROTOCOL are completely different.
The user will NOT have to navigate the world in the same manor as the program does when generating blocks, and zooming in/out.

//--------------------------------------------------
// Origin Block
//--------------------------------------------------
The world will always start with an origin block.
The origin block is on level 0.
Everything else will be generated with addresses in memory relative to that block.
In other words, any block in a world is connected to origin through a series of parents, or children, or a combination of both.

//--------------------------------------------------
// Generating Child Blocks
//--------------------------------------------------
When the program wants to navigate to the a block's children, it must generate children for that block if they do not yet exist.
When generating children, all 9 will be generated at the same time to ensure that a block either:
	A. has all of its children or 
	B. has none of its children.
All 9 pointers to the 9 children are stored in the parent block.
Each child has its parent point point "up" to its parent at the moment of generation.

//--------------------------------------------------
// Parent Blocks
//--------------------------------------------------
When generating a parent block, the "initiating child" that does not yet have a parent will request a parent be generated.
The program will check to make sure the parent does NOT exist before generating a parent.
Once the parent is generated, it will immidiately generate all of its children.
So, in effect, when a block tries to generate a parent, it will automatically generate eight "sibling" blocks (the eight blocks around it on the same level).
FOR EVERY PARENT THAT IS GENERATED, IT WILL BE CONCENTRIC WITH THE ORIGIN.
The above fact is crucial to understand. It is one of the most important and useful facts about this system.


//--------------------------------------------------
// FAQ
//--------------------------------------------------
Q.	If you can only generate parents and chilrend (zooming in and out of the fractal network), how can you even generate a neighbor?
	How can the user ever pan the view horizontally on the same level?
A.	If the user wants to pan around horizontally on the same level, the program will zoom out, and then zoom back in to get to the location the user wants to go.
	This may seem convoluted, but it makes the map network much more robust, expandable, and less prone to errors when programming it.

*/


#define BLOCK_LINK_SIZE 256
/// this is a linked list of arrays of pointers to blockData structures.
// this structure is here simply to facilitate garbage collection.
// there is a function that collects pointers to all of the blocks generated.
// when this program is terminated, every block on that list will be erased and the memory is freed.
struct blockLink{
	// a pointer to the previous blockLink in the list
	struct blockLink *prev;
	struct blockData *blocks[BLOCK_LINK_SIZE];
	struct blockLink *next;
};


#define BLOCK_STEP_SIZE 256
/// this is a linked list of steps taken when ascending the network.
// this is mainly used when generating/verifying neighbors.
// although this is just a list of links that contain arrays of characters.
// it can be used for anything really, but it is intended to be used for recording the steps taken when going from child to parent.
// this allow the program to know how to get back down from parent to child.
struct blockStep{
	struct blockStep *prev;
	char steps[BLOCK_STEP_SIZE];
	struct blockStep *next;
};


/// these are definitions for the block_collector program.
// the function will either be collecting a list of all map blocks being generated (as they are generated)
// or the function will de-allocate (free) all of the data it has collected so far.
#define bc_collect		0
#define bc_clean_up		1
short block_collector(struct blockData *block, short operation);



struct blockData *block_generate_origin();
short block_generate_children(struct blockData *datParent);
short block_generate_parent(struct blockData *centerChild);
short block_generate_neighbor(struct blockData *dat, short neighbor);


short map_print(SDL_Surface *dest, struct blockData *block);
short block_print_to_file(struct blockData *block, char *fileName);

/// PNH stands for "Print Network Hierarchy"
// this is the size of the squares that represent the blocks.
#define BLOCK_PNH_SIZE 9
// this is the thickness of the borders
#define BLOCK_PNH_BORDER 2
// this is the color of the block that is the focus of the camera.
#define BLOCK_PNH_COLOR_FOCUS 0xff00ff00
// this is the color of all blocks that are NOT the focus of the camera
#define BLOCK_PNH_COLOR_NOT_FOCUS 0xff0000ff
// this is the color of the borders of the blocks
#define BLOCK_PNH_COLOR_BORDER 0x00000000


short block_print_network_hierarchy(SDL_Surface *dest, struct blockData *focus, struct blockData *highlight, unsigned int childLevelsOrig, unsigned int childLevels, int x, int y, int size, Uint32 colorTop, Uint32 colorBot, Uint32 colorHighlight);
short block_render(struct blockData *block, SDL_Renderer *blockRenderer);

short block_smooth(struct blockData *block, float smoothFactor);
float block_surrounding_average(struct blockData *block, unsigned int x, unsigned int y);

short block_generate_terrain(struct blockData *block, float slopeMax);
short block_fill_random(struct blockData *block, float range_lower, float range_higher);
int block_fill_middle(struct blockData *block, float inVal, float outVal);
short block_fill_nine_squares(struct blockData *Block, int color);
short block_fill_nine_squares_own_color(struct blockData *Block, int one, int two, int three, int four, int five, int six, int seven, int eight, int nine);
short block_fill_half_vert(struct blockData *block, float elevationLeft, float elevationRight);




