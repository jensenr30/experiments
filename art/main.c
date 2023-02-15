
/* Ryan Jensen * <date> * <title>
 * <purpose>
 */

#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include <string.h>
#include <time.h>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
//#include "SDL_ttf.h"


#include <Windows.h>

#define bool char
#define false 0
#define true  1

//do i really want to debug?
#define debug 0

//The attributes of the screen 
int SCREEN_WIDTH = 948;
int SCREEN_HEIGHT = 488;
int SCREEN_BPP = 32;

//The surfaces that will be used
SDL_Surface* screen = NULL;

//The event structure that will be used
SDL_Event event;

//the max size of the rects.
int maxSize = 5;

//how many rectangles are written to the screen each itteration?
int rectanglesPerCycle = 10;

//how much random variance from the original color is the rectangle?
int colorVar = 24;

//this is how slow the game goes
int slowness = 2;

//color[0] is the previous color. color[1] is the current color. color[2] is the next color
int color[3] = {0,0}; //= {0xffffff, 0xffffff};
//this is used to keep track of specific color components
SDL_Color clr[3];

//the difference between each rgb part of color[0] and color[2].
//diff[0] = red diff
//diff[1] = green diff
//diff[2] = blue diff
int diff[3] = {0,0,0};

//this is a number either 0, 1, or 2 that can index into the diff array. it tells you which one has the largest magnitude.
short bigD = 0;
//this is how many itter you have gone 
int itter = 0;

//general functions
#include "functions.h"

// general purpose rectangle
SDL_Rect myrect;

int main(int argc, char *argv[])
{
	int i;
	
	int negmult[3];
	#if debug
	char negchar[3];
	#endif // debug
	
	//int mult[3] = {0x10000, 0x100, 0x1};
	unsigned long randomtimes;
	
	srand(time(NULL));
	
	if( load_settings() == false) return 404; //error. settings not found.
	
    //Initialize
    if( init() == false )
    {
    	return 100;
    }
    
    //Load the files
    load_files();
    
    
	//make sure the program waits for a quit
	bool quit = false;
    
    
    //While the user hasn't quit
    while( quit == false )
    {
    	//While there's an event to handle
    	while( SDL_PollEvent( &event ) )
    	{
    		while(rand()%randomtimes); // randomize
    		srand( time(NULL) ^ rand() ); // get new seed
    		while(rand()%randomtimes); // randomize further
    		randomtimes = rand()%41 + 1;
    		if(randomtimes<0) randomtimes*=-1;
    		//printf("%d\n", randomtimes);
    		
    		//If the user has Xed out the window
    		if( event.type == SDL_QUIT )
			{
				//Quit the program
				quit = true;
			}
			else if(event.type == SDL_VIDEORESIZE){
				SCREEN_WIDTH = event.resize.w;
				SCREEN_HEIGHT = event.resize.h;
				set_window_size(event.resize.w, event.resize.h);
			}
			//If a key was released
			if( event.type == SDL_KEYUP )
			{
				//nothing
			}
			//If space a key was pressed
			else if( event.type == SDL_KEYDOWN )
			{
				//if the user presses anything, reload the settings.
				load_settings();
			}
			//If a mouse button was pressed
			else if( event.type == SDL_MOUSEBUTTONDOWN )
			{
				//if the user presses anything, reload the settings.
				load_settings();
			}
			else if( event.type == SDL_MOUSEBUTTONUP )
			{
				//nothing
			}
			else if( event.type == SDL_MOUSEMOTION)
			{
				myrect.x = event.motion.x;
				myrect.y = event.motion.y;
			}
    	} // end while(poll event)
    	
    	//if you have reached the target color
    	if(itter == negmult[bigD]*diff[bigD]){
    		//set color[0] to color[2].
			color[0] = color[2];
			//randomize next color
			color[2] = (rand()%0x100)*0x10000 + (rand()%0x100)*0x100 + rand()%0x100;
			
			//used to index into the diff array.
			int r=0,g=1,b=2;
			//generate color component differences.
			diff[r] =  color[2]/0x10000 - color[0]/0x10000;
			diff[g] = (color[2]%0x10000)/0x100 - (color[0]%0x10000)/0x100;
			diff[b] =  color[2]%0x100 - color[0]%0x100;
			
			//find out which of the three differences are the most sever in magnitude
			bigD = magnitude(diff, 3);
			itter = 0;
			
			#if debug//generate negmults and negchars
			for(i=0; i<3; i++){
				if(diff[i] <0){
					negchar[i] = '-';
					negmult[i] = -1;
				}
				else{
					negchar[i] = ' ';
					negmult[i] = 1;
				}
			}
			#else //generate negmults
			for(i=0; i<3; i++){
				if(diff[i] <0){
					negmult[i] = -1;
				}
				else{
					negmult[i] = 1;
				}
			}
			#endif // debug
			
			
			//print debugging info
			#if debug
			//print colors [0] and [2]
			printf("\n\nstarting:  color[0] = %6.6x\n", color[0]);
			printf("target:    color[2] = %6.6x\n", color[2]);
			
			//print diffs
			for(i=0; i<3; i++) printf("\ndiff[%d] = %c%2.2x\n", i, negchar[i], diff[i]*negmult[i]);
			printf("\n");
			#endif // debug
			
			//get components of the previous color (color[0])
			clr[0].r = (color[0]%0x1000000) / 0x10000;
			clr[0].g = (color[0]%0x10000  ) /   0x100;
			clr[0].b = (color[0]%0x100    ) /     0x1;
			//get components of the new color (color[2])
			clr[2].r = (color[2]%0x1000000) / 0x10000;
			clr[2].g = (color[2]%0x10000  ) /   0x100;
			clr[2].b = (color[2]%0x100    ) /     0x1;
    	}
    	//if you are still trying to get to the target color
    	else{
			//generate current color (color[1])
			clr[1].r = negmult[bigD]*(  (itter)*clr[2].r + (negmult[bigD]*diff[bigD] - itter)*clr[0].r  ) / diff[bigD];
			clr[1].g = negmult[bigD]*(  (itter)*clr[2].g + (negmult[bigD]*diff[bigD] - itter)*clr[0].g  ) / diff[bigD];
			clr[1].b = negmult[bigD]*(  (itter)*clr[2].b + (negmult[bigD]*diff[bigD] - itter)*clr[0].b  ) / diff[bigD];
			
			//put current color into color[1]
			color[1] = clr[1].r*0x10000
					 + clr[1].g*0x100
					 + clr[1].b*0x1;
			itter++;
			#if debug
			for(i=1; i<2; i++)printf("clr[%d].r= %2.2x  clr[%d].g= %2.2x  clr[%d].b= %2.2x\n", i, clr[i].r, i, clr[i].g, i, clr[i].b);
			//printf("\n");
			#endif // debug
    	}
    	
    	
    	
    	int i;
    	for(i=0; i<rectanglesPerCycle; i++){
			myrect.x = rand()%SCREEN_WIDTH;
			myrect.y = rand()%SCREEN_HEIGHT;
			
			myrect.h = rand()%maxSize;
			myrect.w = rand()%maxSize; 
			
			SDL_FillRect(screen, &myrect, color[1]);
		}
    	
    	
    	SDL_Flip(screen);
    	
    	if(slowness)
			Sleep(slowness);
    }
    
    
    //Free the surface and quit SDL
    clean_up();
    return 0;
}

