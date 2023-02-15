//title of window
#define WINDOW_TITLE_PREFIX "De_Flux 5.0 "

//total number of tiles that could possibly be on the tileset
#define MAX_NUMBER_OF_TILES 0x10000
//total number of items that could possibly be on the itemset
#define MAX_NUMBER_OF_ITEMS 0x10000
// number of tiles wide and tall
#define TILE_SET_WIDTH 0x100
#define TILE_SET_HEIGHT 0x100
// this is the width and height of each tile in pixels
int TILE_SIZE = 32;
// maximum buttons in one buttonSet structure
#define MAX_BUTTONS_IN_A_SET 32

#define MAX_TILES_PER_MAP 0x10000
#define MAX_ITEMS_PER_MAP 0x10000
#define MAX_MAP_NAME_LENGTH 0x80
// maximum number of portals or links to other maps on a single map.
#define MAX_PORTALS_PER_MAP 0x40
#define ZOOM_IN 0 // defines ZOOM_IN
#define ZOOM_OUT 1 // defines ZOOM_OUT

#define UP 0		// W
#define LEFT 2		// A
#define DOWN 1		// S
#define RIGHT 3		// D

#define OVER 4     // for buttons (see butten structure)

//fade in/out time for music (in milliseconds)
#define MUSIC_FADE_TIME 20000

// this is the amount color-wise that a lot of things vary from their backgrounds.
#define contrast 0x202020

// this is the number of pixels that the player changes the screen resolution by in options.
//for example, when the user increases the size of the .00, he/she increases it by PIXELS_PER_SCREEN_DIVISION number of pixels.
#define PIXELS_PER_SCREEN_DIVISION 0x80 // 128
//The attributes of the screen.
//try to make the screen width and heigh a multiple of 0x80. (a multiple of 128)
int SCREEN_WIDTH = 0x400;
int SCREEN_HEIGHT = 0x280;
const int SCREEN_BPP = 0x20;
// this is the camera offset. this allow the "camera" to be moved to see different areas of the map.
int cameraPos[2] = {0,0};


//the event structure that will be used.
SDL_Event event;
//The surfaces that will be used
SDL_Surface *screen = 	NULL;	// this is the screen. this is what gets displayed.
SDL_Surface *icon	=	NULL;	// this is the window icon
SDL_Surface *splash =	NULL;	// this is for the splash screen upon startup
SDL_Surface *pressH = 	NULL;	// this is the for "press 'h' at any time for help" message at the title screen.
SDL_Surface *title_image = NULL;// this is for the title screen
SDL_Surface *text = 	NULL;	// surface used to render text on
SDL_Surface *black512 = NULL;	// 512x512 of black.
SDL_Surface *grid512  = NULL;	// a 512x512 grid.

//tiles
SDL_Surface *tile_set = NULL;		// this is where the game's tile set is loaded into
SDL_Surface *tile_set_8		= NULL; // 8x8 res tile texture set
SDL_Surface *tile_set_16	= NULL; // 16x16 res tile texture set
SDL_Surface *tile_set_32	= NULL; // 32x32 res tile texture set
SDL_Surface *tile_set_64	= NULL; // 64x64 res tile texture set
SDL_Surface *tile_set_128 	= NULL; // 128x128 res tile texture set

//item_set
SDL_Surface *item_set = NULL;		// this is where the game's item set is loaded into
SDL_Surface *item_set_8		= NULL; // 8x8 res item texture set
SDL_Surface *item_set_16	= NULL; // 16x16 res item texture set
SDL_Surface *item_set_32	= NULL; // 32x32 res item texture set
SDL_Surface *item_set_64	= NULL; // 64x64 res item texture set
SDL_Surface *item_set_128 	= NULL; // 128x128 res item texture set
// inventory stuff
SDL_Surface *inv_in 		= NULL; // the texture for the inventory button when it is IN
SDL_Surface *inv_out 		= NULL; // the texture for the inventory button when it is OUT

//beings
SDL_Surface *being_set		= NULL; // this is the image that consists of 256x256 enemy sprites.


SDL_Surface *inventory_background = NULL; // this is what the inventory's back ground will look like.
SDL_Surface *inventory_border   = NULL; // this is an 8x8 pice of the inventory boreder.
#define INVENTORY_WIDTH 8
#define INVENTORY_HEIGHT 16
#define INVENTORY_TILE_SIZE 32

SDL_Surface *playerAvatar = NULL;		// this is the player's avatar. the size of this will go along with the size of the tiles.
SDL_Surface *playerAvatar128 = NULL;	//thie is the player's avatar as well. however, this will always be size 128x128.
SDL_Surface *playerAvatarInventory = NULL; // this is the player's avatar for the inventory.


//the fonts that will be used
TTF_Font *courierFontInfo = NULL;
TTF_Font *courierFont = NULL;
TTF_Font *sansFont = NULL;
TTF_Font *sansFont2;
int courierFontSize = 15;
static short courierFontInfoSize = 11;
int sansFontSize = 24;
int sansFont2Size = 16;

//The color of the text
SDL_Color textColor = { 0x22, 0x5c, 0x0a };
SDL_Color brightGreen = { 0x3d, 0xf5, 0x5b };
SDL_Color colorLightBlue = { 0x12, 0x56, 0xec };
#define DF_COLOR_RED   0xb74848
#define DF_COLOR_BLUE  0x3d63a8
#define DF_COLOR_GREEN 0x7cb748
#define DF_COLOR_YELLOW 0xcfce5b
//SDL_Color DF_RED_SDL = {0xb7, 0x48, 0x48}; // red SDL color
//SDL_Color DF_BLUE_SDL = {0x3d, 0x63, 0xa8}; // blue SDL color

//this is how big the text is.
SDL_Surface *textBox = NULL;
SDL_Surface *msg = NULL;





//audio starts with an "a_" prefix
// audio is specifically .wav format sound files.
Mix_Chunk *a_button_click = NULL;
Mix_Chunk *a_error =		NULL;
Mix_Chunk *a_find =			NULL;
Mix_Chunk *a_teleport =		NULL;
Mix_Chunk *a_footstep = 	NULL;
Mix_Chunk *a_box_open = 	NULL;
Mix_Chunk *a_blast = 		NULL;

// music starts with an "m_" prefix.
// music is sound that has any extention. (i.e. mp3, flac, wav, ogg, etc...)
Mix_Music *m_Learn_by_Doing		= NULL; // a happy, easy-going song






