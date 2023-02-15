#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"
#include "graphics.h"
#include "globals.h"
#include <time.h>
#include "seizesv.h"
#include "seizesv_plot.h"

#define MOUSE_BUTTONS 5


int main(int argc, char *argv[]){
	
	
	
	error("\n\n\n\n== PROGRAM START ======================================================\n\n\n\n");
	
	//--------------------------------------------------
	// initial gamelog write
	//--------------------------------------------------
	ssvlog_startup(argc, argv);
	int i;
	windW = 1300;
	windH = 731;
	
	//--------------------------------------------------
	// set up surfaces, textures, renderers, windows,
	//--------------------------------------------------
	SDL_Window *myWindow = NULL;
	SDL_Renderer *myRenderer = NULL;
	SDL_Texture *myTexture = NULL;
	SDL_Surface *mySurface = create_surface(windW, windH);
	
	// get a random seed at the beinning of the program based on what time it is
	srand(time(NULL));
	
	
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1) return -99;
	
		// set network window
	myWindow = SDL_CreateWindow("seizesv 0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windW, windH, SDL_WINDOW_RESIZABLE);
	myRenderer = SDL_CreateRenderer(myWindow, -1, 0);
	
	if(myWindow == NULL){
		error("main() could not create myWindow using SDL_CreateWindow");
		return -1;
	}
	if(myRenderer == NULL){
		error("main() could not create myRenderer using SDL_CreateRenderer");
		return -2;
	}
	
	SDL_SetRenderDrawColor(myRenderer, 0, 0, 0, 255);
	SDL_RenderClear(myRenderer);
	SDL_RenderPresent(myRenderer);
	
	SDL_SetRenderDrawColor(myRenderer, 0, 0, 0, 255);
	SDL_RenderClear(myRenderer);
	SDL_RenderPresent(myRenderer);
	
	
	//--------------------------------------------------
	// event handling
	//--------------------------------------------------
	
	// this records if the user wants to quit
	byte quit = 0;
	const int keysSize = 256;
	// this array keeps track of what variables were JUST pushed.
	// A value of 1 will be set to keys that were just stroked.
	// after an iteration through the loop, all keys are reset to 0.
	byte keys[keysSize];
	// this keeps track of which keys are HELD DOWN
	int_fast8_t keysHeld[keysSize];
	// these keep track of where the mouse is
	float x=0, y=0;
	// these keep track of where the mouse was just moments ago.
	float xlast=0, ylast=0;
	
	// this keeps track of when it is necessary o refresh the plot
	// we only want to re-plot the data when we NEED to. Otherwise, we
	// will hog CPU cycles. By default, the screen needs to be refreshed at startup.
	// Or, "freshed" because it is the first time.
	char refreshPlot = 1;
	
	// these two 2-element arrays keep the data concerning the state of the right and left mouse buttons.
	// EX:
		// mouse[SDL_BUTTON_LEFT][0] is the CURRENT state of the LEFT mouse button
		// mouse[SDL_BUTTON_LEFT][1] is the LAST    state of the LEFT mouse button
		// mouse[SDL_BUTTON_RIGHT][0] is the CURRENT state of the RIGHT mouse button
		// mouse[SDL_BUTTON_RIGHT][1] is the LAST    state of the RIGHT mouse button
	int mouse[MOUSE_BUTTONS][2] = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0} };
	
	// this is similar to mouse. however, this is used to store where the user clicked when a particular mouse button was clicked.
		// mouseClick[SDL_BUTTON_LEFT][0] is the x position where the user clicked the left  mouse button.
		// mouseClick[SDL_BUTTON_LEFT][1] is the y position where the user clicked the left  mouse button.
		// mouseClick[SDL_BUTTON_RIGHT][0] is the x position where the user clicked the RIGHT mouse button.
	// etc...
	int mouseClick[MOUSE_BUTTONS][2] = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0} };
	
	
	//--------------------------------------------------
	// these variables keep track of time and FPS
	//--------------------------------------------------
	uint32_t ticksLast_FPS_calc = 0;
	uint32_t ticksLast = 0;
	uint32_t ticksNow = 0;
	uint32_t frames = 0;
	uint32_t FPS = 0;
	
	
	//--------------------------------------------------
	// these variables are for panning / fractal part modification
	//--------------------------------------------------
	// these keep track of the mouse position when panning/part modification began
	float pan_orig_x;
	float pan_orig_y;
	// these two keep track of the original <x,y> values of the fractal when panning
	float orig_x;
	float orig_y;
	// keeps track of whether or not we are panning
	char panning = 0;
	
	
	//--------------------------------------------------------------------------
	// ssv test stuff
	//--------------------------------------------------------------------------
	
	ssvlog_d("length of \\0 is: ", strlen("\0"));
	ssvlog_d("length of NULL is :", strlen("\0"));
	ssvlog_d("The result of (NULL==NULL) is:",(NULL==NULL));
	ssvlog_d("The result of ( 1 < (0.0/0.0) ) is:", ( 1 < (0.0/0.0) ) );
	ssvlog_d("The result of ( 1 > (0.0/0.0) ) is:", ( 1 > (0.0/0.0) ) );
	ssvlog_d("The result of ( -1 < (0.0/0.0) ) is:", ( -1 < (0.0/0.0) ) );
	ssvlog_d("The result of ( -1 > (0.0/0.0) ) is:", ( -1 > (0.0/0.0) ) );
	
	// create a ssv_file to store csv data
	struct ssv_file f;
	// read a csv file into memory
	ssv_file_read(argv[1],&f);
	// print information
	ssvlog_d("columns found = ",f.columns);
	ssvlog_d("rows found    = ",f.rows);
	struct ssv_block *b = &(f.origin);
	unsigned long long int ii;
	for (ii = 0; ii < f.columns; ii++) {
		// only move to the next block after the first one
		if (ii != 0) {
			b = b->blockRight;
		}
		ssvlog_s("column title = ",b->title);
		if(b == NULL)
		{
			error("main() bad block when printing column headers!");
			break;
		}
		
	}
	
	char file_name_mode[1000];
	strcpy(file_name_mode,f.file_name);
	strcat(file_name_mode,"-writeout.csv");
	// write the file back to file
	ssv_file_write(&f,file_name_mode);
	
	ssvlog("Done writing back to file");
	
	// create a ssv_plot
	struct ssv_plot p;
	// init your plot structure
	ssv_plot_init(&p);
	// point the plot at the data that was read into memory
	p.data = &f;
	// the x variable is the first column
	p.x[0] = 8;
	// the y variable is the second column
	p.y = 7;
	double fit = 0.9;
	// zoom the plot to fit the data
	ssv_plot_zoom_fit(&p,mySurface,fit);
	
	//--------------------------------------------------
	// this is the fabled "main while() loop"
	// This is where the user input is interpreted.
	// mouse motion, mouse clicks, keystrokes, etc...
	//--------------------------------------------------
	
	while(quit == 0){
		
		// check to see which fractal structure will be operated on.
		// this depends on whether or not the user is modifying a part or panning.
		if(panning)
		{
			// do some panning operation here
		}
		else
		{
			// do something else? WHAT!!1?
		}
		
		// reset all keystroke values
		for(i=0; i<keysSize; i++){
			keys[i] = 0;
		}
		while(SDL_PollEvent(&event)){
			
			//--------------------------------------------------
			// if the user drags and drops a file into the screen
			//--------------------------------------------------
			if(event.type == SDL_DROPFILE){
				// save the name of the file.
				// event.drop
				// free the file when you are done with it.
			}
			
			
			//--------------------------------------------------
			// if a mouse button is pressed,
			//--------------------------------------------------
			else if(event.type == SDL_MOUSEBUTTONDOWN){
				
				x = event.button.x;
				y = event.button.y;
				
				// set mouse button states
				if(event.button.button == SDL_BUTTON_LEFT){
					// record that the left mouse button is down
					mouse[SDL_BUTTON_LEFT][0] = 1;
					// record where the left mouse button was clicked
					mouseClick[SDL_BUTTON_LEFT][0] = x;
					mouseClick[SDL_BUTTON_LEFT][1] = y;
					//ssvlog("LeftDown!");
				}
				
				else if(event.button.button == SDL_BUTTON_RIGHT){
					// record that the right mouse button is down
					mouse[SDL_BUTTON_RIGHT][0] = 1;
					// record where the right mouse button was clicked
					mouseClick[SDL_BUTTON_RIGHT][0] = x;
					mouseClick[SDL_BUTTON_RIGHT][1] = y;
					//ssvlog("RightDown!");
				}
				
				else if(event.button.button == SDL_BUTTON_MIDDLE){
					// record that the middle mouse button is down
					mouse[SDL_BUTTON_MIDDLE][0] = 1;
					// record where the middle mouse button was clicked
					mouseClick[SDL_BUTTON_MIDDLE][0] = x;
					mouseClick[SDL_BUTTON_MIDDLE][1] = y;
					//ssvlog("Middleown!");
				}
			}
			
			
			//--------------------------------------------------
			// if a mouse button has been released,
			//--------------------------------------------------
			else if(event.type == SDL_MOUSEBUTTONUP){
				// set mouse button states
				if(event.button.button == SDL_BUTTON_LEFT) mouse[SDL_BUTTON_LEFT][0] = 0;
				if(event.button.button == SDL_BUTTON_RIGHT) mouse[SDL_BUTTON_RIGHT][0] = 0;
				if(event.button.button == SDL_BUTTON_MIDDLE) mouse[SDL_BUTTON_MIDDLE][0] = 0;
			}
			
			
			//--------------------------------------------------
			// if the mouse wheel is turned,
			//--------------------------------------------------
			else if(event.type == SDL_MOUSEWHEEL){
				// do a shitt little zoom
				p.x_pixels_per_x[0] *= pow(1.05,event.wheel.y);
				p.y_pixels_per_y    *= pow(1.05,event.wheel.y);
				// the user probably wants to change the scale of the plot which will require replotting
				refreshPlot = 1;
			}
			
			
			//--------------------------------------------------
			// if the mouse has moved,
			//--------------------------------------------------
			else if(event.type == SDL_MOUSEMOTION){
				x = event.motion.x;
				y = event.motion.y;
				
				// if the user is currently panning,
				if(panning)
				{
					// we will need to re-render the plot
					refreshPlot = 1;
				}
			}
			
			
			//--------------------------------------------------
			// if a key has been pressed,
			//--------------------------------------------------
			else if(event.type == SDL_KEYDOWN){
				if(event.key.keysym.sym >= 0){
					// set that character, number, or letter to 1.
					keys[(event.key.keysym.sym)%keysSize] = 1;
					keysHeld[(event.key.keysym.sym)%keysSize] = 1;
				}
				// check out which keys were pressed
				switch(event.key.keysym.sym){
					case SDLK_DOWN:
						break;
					case SDLK_UP:
						break;
					default:
						break;
				}
			}
			
			
			//--------------------------------------------------
			// if a key has been released,
			//--------------------------------------------------
			else if(event.type == SDL_KEYUP){
				if(event.key.keysym.sym >= 0){
					// set that character, number, or letter to 0.
					keysHeld[(event.key.keysym.sym)%keysSize] = 0;
				}
			}
			
			
			//--------------------------------------------------
			// if there has been a window event
			//--------------------------------------------------
			else if(event.type == SDL_WINDOWEVENT ){
				// if the window has been closed,
				switch(event.window.event){
					case SDL_WINDOWEVENT_CLOSE:
						quit = 1;
						break;
					case SDL_WINDOWEVENT_RESIZED:
						// the new window width and height need to be recorded
						windW = event.window.data1;
						windH = event.window.data2;
						// also the surface needs to be changed right away
						if(mySurface != NULL)SDL_FreeSurface(mySurface);
						mySurface = create_surface(windW, windH);
						// for some reason (probably my own stupidity is to blame)
						// I need to refresh the plot TWICE after the window is resized
						refreshPlot = 2;
						ssv_plot_zoom_fit(&p,mySurface,fit);
						break;
				}
			}
			
			
			//--------------------------------------------------
			// if there has been a quit event,
			//--------------------------------------------------
			else if(event.type == SDL_QUIT){
				quit = 1;
			}
		}
		
		// if the user just clicked the left mouse button
		if(mouse[SDL_BUTTON_LEFT][0] && !mouse[SDL_BUTTON_LEFT][1])
		{
			// the user has begun panning
			panning = 1;
		}
		// otherwise, if the user just LET OFF the left mouse button
		else if(!mouse[SDL_BUTTON_LEFT][0] && mouse[SDL_BUTTON_LEFT][1])
		{
			// the user has chosen to stop panning
			panning = 0;
		}
		
		// if the user is currently panning,
		if(panning)
		{
			// move the plot position
		}
		
		if (refreshPlot > 0) {
			//--------------------------------------------------
			// render a plot and throw it on the main viewer
			//--------------------------------------------------
			
			ssv_plot(&p, mySurface);
			
			
			//--------------------------------------------------
			// this area of the code puts whatever was rendered
			// into mySurface onto the screen for the user to see
			//--------------------------------------------------
			
			// generate texture for the block network
			myTexture = SDL_CreateTextureFromSurface(myRenderer, mySurface);
			
			// clear the old texture if it exists
			if(mySurface != NULL)SDL_FreeSurface(mySurface);
			mySurface = create_surface(windW, windH);
			// render the mySurface to the myWindow
			SDL_RenderCopy(myRenderer, myTexture, NULL, NULL);
			if(myTexture != NULL)SDL_DestroyTexture(myTexture);
			// display the renderer's result on the screen and clear it when done
			SDL_RenderPresent(myRenderer);
			SDL_RenderClear(myRenderer);
			
			// keep track of how many frames have been printed. This is to regulate and log FPS
			frames++;
			// stop rendering the plot. This variable will be set true if the user
			// changes the plot in any way.
			refreshPlot--;
		}
		
		//----------------------------------------------------------------------
		// records mouse position and button states
		//----------------------------------------------------------------------
		
		// store the current x and y values and use them as the "last" values in the next iteration of the loop
		xlast = x;
		ylast = y;
		// save all current mouse states.
		for(i=0; i<MOUSE_BUTTONS; i++){
			// set the last state of this mouse button to the current state (for the next loop iteration)
			mouse[i][1] = mouse[i][0];
		}
		
		//----------------------------------------------------------------------
		// regulate and log the FPS of the main window
		//----------------------------------------------------------------------
			
		
		// get the current value of ticks
		ticksNow = SDL_GetTicks();
		
		// if more than a second has passed since the last FPS calculation,
		if(ticksNow - ticksLast_FPS_calc >= 1000){
			FPS = (int)( ((float)frames)/( ( ((float)(ticksNow-ticksLast))/1000.0f ) + 0.5f ) );
			// reset frame counter
			frames = 0;
			// set the last tick time to the current time (this will make the program wait 1 second until recalculating the FPS)
			ticksLast_FPS_calc = ticksNow;
			ssvlog_d("FPS =", FPS);
		}
		
		// if you created a frame faster than you thought you would have,
		if (ticksNow - ticksLast < SSV_PLOT_TARGET_FRAME_PERIOD_MS) {
			// wait for the remaining time of this cycle in order to achieve the
			// target frame rate
			SDL_Delay( SSV_PLOT_TARGET_FRAME_PERIOD_MS - (ticksNow - ticksLast) );
			//SDL_Delay(100);
		}
		
		// save the time at which you last blew through here
		ticksLast = SDL_GetTicks();
		
	}
	
	
	//--------------------------------------------------
	// clean up
	//--------------------------------------------------
	if(myRenderer != NULL) SDL_DestroyRenderer(myRenderer);
	if(myTexture  != NULL) SDL_DestroyTexture (myTexture);
	if(myWindow   != NULL) SDL_DestroyWindow  (myWindow);
	
	// clean up all SDL subsystems and other non-SDL systems and global memory.
	clean_up();
	
	
	return 0;
}





