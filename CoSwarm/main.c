#include "bool.h"
#include "main.h"
#include "graphics.h"
#include "game_time.h"
#include "time.h"
#include "general_functions.h"
#include "gen_world.h"
#include "controls.h"
#include "materials_and_cells.h"
#include "beast.h"

int main( int argc, char* args[] ) 
{
	
	// this is the last time (SDL_Getticks()) that beasts were evaluated
	int beastLastEval=0;
	// this is how many times per second the beasts should be evaluated
	int beastEvalsPerSec = 30;
	
	paused = 0;
	//get a random seed.
	sgenrand(time(NULL));
	
    //mouse variables and cell types
    int x, y, sleepTime = 0, countVar = 0;
	
    //mouse is held variables
    int mouseStatusLeft = 0, mouseStatusRight = 0;
    
    // these keep track of the position of the right mouse button when it was clicked down
    int mouseRDx;
	int mouseRDy;
	
	//make sure the program waits for a quit
	int quit = false;
	
	init_mats();
	init_graphics();
	init_controls();
	
    //Initialize
    if( init() == false ) return 1;
	
    //Load the files
    if( load_files() == false ) return 2;
	
    //Update the screen
    if( SDL_Flip( screen ) == -1 ) return 3;
    
    gen_world();
	
	// these keep track of the WASD keys.
	int keyw=0, keya=0, keys=0, keyd=0;
	int key; // used as a stand-int for the verbose event.key.keysym.sym
	bool keyF3=true;
	
	//these are used to calculating and keeping track of the FPS
	int ticksSinceLastFPSUpdate = 0;
	int cumulativeFrames = 0;
	int currentTicks = 0;
	
	SDL_Rect screenRect;
	screenRect.x = screenRect.y = 0;
	screenRect.w = SCREEN_WIDTH;
	screenRect.h = SCREEN_HEIGHT;
	
	
    //While the user hasn't quit
    while(1){
		
    	//While there's an event to handle
    	while( SDL_PollEvent( &event ) ){
			
    		//If the user has Xed out the window
    		if( event.type == SDL_QUIT || quit == true ){
				//Quit the program
				clean_up();
				return 0;
			}
			
            if( event.type == SDL_MOUSEBUTTONDOWN ){						/// mouse down
				x = event.motion.x;
				y = event.motion.y;
                if( event.button.button == SDL_BUTTON_LEFT ){
                    mouseStatusLeft = 1;
                }
                else if( event.button.button == SDL_BUTTON_RIGHT ){
                    mouseStatusRight = 1;
                    mouseRDx = x;
                    mouseRDy = y;
                }
                
                else if( event.button.button == SDL_BUTTON_WHEELUP )
					;//zoom_in(x,y);
				else if( event.button.button == SDL_BUTTON_WHEELDOWN )
					;//zoom_out(x,y);
				
            }
            else if(event.type == SDL_MOUSEBUTTONUP){						/// mouse up
				x = event.motion.x;
				y = event.motion.y;
                if( event.button.button == SDL_BUTTON_LEFT ){
                    mouseStatusLeft = 0;
                }
                else if( event.button.button == SDL_BUTTON_RIGHT ){
                    mouseStatusRight = 0;
                }
            }
            else if( event.type == SDL_MOUSEMOTION ){						/// mouse motion
				x = event.motion.x;
				y = event.motion.y;
				/*
				// if the alt key (camera panning key) is down and the coordinates have changed, then let the screen be panned!
				if(alt && x != mouse_x_when_pan && y != mouse_y_when_pan){
					// this adjusts the x-axis camera (this scales with the CELL_SIZE)
					camera_x += (x-mouse_x_when_pan+remainder_panning_motion_x)/CELL_SIZE;
					camera_y += (y-mouse_y_when_pan+remainder_panning_motion_y)/CELL_SIZE;
					//calculate the remainders of the mouse motion.
					// these values represent the motion of the mouse that is not utilized by the discrete nature of the operation on the camera_x and camera_y values.
					remainder_panning_motion_x = (x-mouse_x_when_pan+remainder_panning_motion_x) - (int)((x-mouse_x_when_pan+remainder_panning_motion_x)/CELL_SIZE)*CELL_SIZE;
					remainder_panning_motion_y = (y-mouse_y_when_pan+remainder_panning_motion_y) - (int)((y-mouse_y_when_pan+remainder_panning_motion_y)/CELL_SIZE)*CELL_SIZE;
					// make sure the camera is not out of bounds.
					verify_camera();
					
					//reset the user's curcor position to the original position the curcor was in when the user started panning the camera
					SDL_WarpMouse(mouse_x_when_pan, mouse_y_when_pan);
				}
				*/
            }
            else if(event.type == SDL_VIDEORESIZE){							/// window resize
				// don't resize the grid.
				//float new_cell_size = CELL_SIZE * event.resize.h/((float)SCREEN_HEIGHT); // adjust the pixel size.
				//if(new_cell_size - ((int)new_cell_size) >= 0.5f) CELL_SIZE = new_cell_size + 1;
				//else CELL_SIZE = new_cell_size;
				screenRect.w = SCREEN_WIDTH = event.resize.w;
				screenRect.h = SCREEN_HEIGHT = event.resize.h;
				set_window_size(event.resize.w, event.resize.h);		// set window to correct dimensions
			}
			
            if( event.type == SDL_KEYDOWN ){		///keyboard event
                key = event.key.keysym.sym;
				if     (key == controlsGame.pan[d_up])		camera_pan(d_up);		// pan up
				else if(key == controlsGame.pan[d_down])	camera_pan(d_down);		// pan down
				else if(key == controlsGame.pan[d_left])	camera_pan(d_left);		// pan left
				else if(key == controlsGame.pan[d_right])	camera_pan(d_right);	// pan right
				else if(key == controlsGame.debug)			keyF3 ^= 1;				// toggle the keyF3 state
				
			}
			if( event.type == SDL_KEYUP ){								///keyboard event
                // nothing here yet
			}
                
		
    	} // end while(event)
		//no more events to handle at the moment.
		if(mouseStatusLeft==true && beast_find_at_cell(x/CELL_SIZE+cameraX,y/CELL_SIZE+cameraY) == NULL){
			// add beast function
			struct beastData *myBeast;
			myBeast = beast_create(NULL);
			if(myBeast != NULL ){
				myBeast->x = x/CELL_SIZE + cameraX;
				myBeast->y = y/CELL_SIZE + cameraY;
			}
		}
		
		if(SDL_GetTicks()-beastLastEval > 1000/beastEvalsPerSec){
			// evaluate all beasts
			beasts_evaluate();
			beastLastEval = SDL_GetTicks();
		}
		
        // print the grid data
        print_grid(screen);
        print_beasts(screen);
        print_beasts_targets(screen);
        
        // print debugging information
        if(keyF3) print_debugging_information(screen);
        //updates the screen
        SDL_Flip( screen );
        SDL_FillRect(screen, &screenRect, 0);
        //----------------------------------------------------
		// FPS calculation and variable handling
		//----------------------------------------------------
        currentTicks = SDL_GetTicks();
        // it is officially the next second
        if(currentTicks >= ticksSinceLastFPSUpdate + 1000){
			// calculate the FPS
			FPS = cumulativeFrames;//(cumulativeFrames*1000 ) / (currentTicks-ticksSinceLastFPSUpdate);
			cumulativeFrames=0;				// reset cumulative amount of frames
			ticksSinceLastFPSUpdate = currentTicks;	// reset the last FPS update to the number of ticks now.
        }
        cumulativeFrames++;
		
    }// end while(quit == false)


    //Free the surface and quit SDL
    clean_up();

    return 0;
}

