



//total number of tiles that could possibly be on the tileset
#define MAX_NUMBER_OF_TILES 0x10000
//total number of items that could possibly be on the itemset
#define MAX_NUMBER_OF_ITEMS 0x10000
// number of tiles wide and tall
#define TILE_SET_WIDTH 0x100
#define TILE_SET_HEIGHT 0x100
// this is the width and height of each tile in pixels
int TILE_SIZE = 32;
// maximum number of portals or links to other maps
#define MAX_PORTALS 0x40
// maximum buttons in one buttonSet structure
#define MAX_BUTTONS_IN_A_SET 32

#define MAX_TILES_PER_MAP 0x10000
#define MAX_ITEMS_PER_MAP 0x10000
#define MAX_MAP_NAME_LENGTH 0x80
#define ZOOM_IN 0 // defines ZOOM_IN
#define ZOOM_OUT 1 // defines ZOOM_OUT

#define UP 0		// W
#define LEFT 1		// A
#define DOWN 2		// S
#define RIGHT 3		// D

#define OVER 4     // for buttons (see butten structure)

// this is the number of pixels that the player changes the screen resolution by in options.
//for example, when the user increases the size of the window, he/she increases it by PIXELS_PER_SCREEN_DIVISION number of pixels.
#define PIXELS_PER_SCREEN_DIVISION 0x80 // 128
//The attributes of the screen
int SCREEN_WIDTH = 0x400;
int SCREEN_HEIGHT = 0x280;
int SCREEN_BPP = 0x20;
// this is the camera offset. this allow the "camera" to be moved to see different areas of the map.
int cameraPos[2] = {0,0};


//the event structure that will be used.
SDL_Event event;
//The surfaces that will be used
SDL_Surface *screen = 	NULL;	// this is the screen. this is what gets displayed.
SDL_Surface *icon	=	NULL;	// this is the window icon
SDL_Surface *splash =	NULL;	// this is for the splash screen upon startup
SDL_Surface *title_image = NULL;// this is for the title screen
SDL_Surface *text = 	NULL;	// surface used to render text on
SDL_Surface *black512 = NULL;	// 512x512 of black.
SDL_Surface *grid512  = NULL;	// a 512x512 grid.

SDL_Surface *tile_set = NULL;		// this is where the game's tile set is loaded into
SDL_Surface *item_set = NULL;		// this is where the game's item set is loaded into
// inventory stuff
SDL_Surface *tile_set_inventory = NULL;	// this is where the inventory's tile set is loaded into
SDL_Surface *item_set_inventory = NULL;	// this is where the inventory's item set is loaded into
SDL_Surface *inventory_background = NULL; // this is what the inventory's back ground will look like.
SDL_Surface *inventory_border   = NULL; // this is an 8x8 pice of the inventory boreder.
#define INVENTORY_WIDTH 8
#define INVENTORY_HEIGHT 16
#define INVENTORY_TILE_SIZE 32

SDL_Surface *player = NULL;		// this is the player's avatar
int playerPosition[2] = {0, 0};	// this holds where the player is located.



//text stuff

//the font that will be used
TTF_Font *courierFont = NULL; 
TTF_Font *sansFont = NULL;
int sansFontSize = 24;
TTF_Font *sansFont2;
int sansFont2Size = 16;
//The color of the text
SDL_Color textColor = { 0x22, 0x5c, 0x0a };
SDL_Color brightGreen = { 0x3d, 0xf5, 0x5b };
SDL_Color colorLightBlue = { 0x12, 0x56, 0xec };
//this is how big the text is.
int textSize = 24;
SDL_Surface *textBox = NULL;
SDL_Surface *msg = NULL;


struct mapPortal{
	// these are the coordinates that you come from
	int oldCoor[2];
	// these are the coordinates that you go to
	int newCoor[2];
	// this is the name of the map you go to when you teleport. the map is loaded upon entry into that map.
	// initially undefined.
	char nextMapName[MAX_MAP_NAME_LENGTH];
};

struct oneTile {
	int x;
	int y;
	unsigned short type;
};

struct oneItem {
	int x;
	int y;
	unsigned short type;
};

//try to only have a few maps open at a time to conserve memory.
struct map{
	//name of the current map
	char currentMap[MAX_MAP_NAME_LENGTH];
	// these are portals to other maps
	struct mapPortal portals[MAX_PORTALS];
	// this is sort of like a tile stack pointer (hence tsp)
	// it is normally on the next available spot in the tiles[][] array. to add a tile into this array, simply modify the data and then currentMap.tsp++
	int tsp;
	int isp; // this is like the tile stack pointer but for the items on the map
	int msp; // this is the map's stack pointer
	
	// this holds the data for the tiles. this array must end with a t_EOT tile.
	struct oneTile tiles[MAX_TILES_PER_MAP];
	//this holds the data for the items on the map this array must end with a i_EOI item.
	struct oneTile items[MAX_ITEMS_PER_MAP];
	
	//these are the default spawn coordinates for someone entering the map under normal, non-teleportation conditions.
	int spawnx;
	int spawny;
	
} currentMap;





struct tileAttributes {
	//walkOn: 1 = can walk 0 = cannot walk on
	char walkOn;
} tileAtt[MAX_NUMBER_OF_TILES]; // this holds all of the tile attributes that will be used in the game.






