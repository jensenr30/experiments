#include <SDL\SDL_ttf.h>



///------------IMPORTANT TERMS----------------------------------------------
/// a CELL refers to a space in the GRID.
/// the GRID is the collection of cells in the application window.
/// a MATERIAL refers to what thing is occupying a certain cell.
/// for instance, you might fill a CELL with a MATERIAL.
/// you do NOT fill a METERIAL with a CELL. that just doesn't make any sense.
/// if you want to make a cell empty, that means you are filling it with AIR.


// this is how big each square cell is
#define DEFAULT_CELL_SIZE 10
int CELL_SIZE;
#define MAX_CELL_SIZE 32
#define MIN_CELL_SIZE 1






//The CONSTANT initial size of the screen
#define DEFAULT_SCREEN_WIDTH 800
#define DEFAULT_SCREEN_HEIGHT 450
#define SCREEN_BPP 32

//this is for panning the screen (in milliseconds
#define MIN_PAN_INTERVAL 50

//The DYNAMIC  initial size of the screen
unsigned int SCREEN_WIDTH;
unsigned int SCREEN_HEIGHT;


// this is where the camera is looking (this tells us where in the grid the user is looking)
// these two numbers represent the upper-left corner of the screen.
// these numbers are in units of grid cells (NOT pixels)
int cameraX;
int cameraY;

// these are some enumerated direction definitions. used for panning and such.
#define d_up	0
#define d_down	1
#define d_left	2
#define d_right	3

// global variable that tells you the FPS of the game.
int FPS;

// The surfaces that will be used
SDL_Surface *screen;
SDL_Surface *text;
SDL_Surface *icon;

// the fint that will be used
TTF_Font *font;
TTF_Font *font16;

#define grad_linear 0
#define grad_radial 1




void init_graphics();

void camera_verify();
void camera_pan(int direction);
 
SDL_Surface *load_image( char* filename );
SDL_Surface *create_surface(int width, int height);
void apply_surface( int x, int y,  SDL_Surface* source, SDL_Surface* destination );

void gradient(SDL_Surface *datsurface, SDL_Rect *gradClip, int x1, int y1, int x2, int y2, Uint32 color1, Uint32 color2, unsigned int gradientType);
void draw_line(SDL_Surface *theSurface, int x1, int y1, int x2, int y2, int thickness, int lineColor);

void print_grid(SDL_Surface *dest);
void print_beasts(SDL_Surface *dest);
void print_beasts_targets(SDL_Surface *dest);
