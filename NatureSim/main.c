#include "headers_and_globals.h"

int main( int argc, char* args[] )
{
	//get a random seed.
	srand(time(NULL));

    //mouse variables and cell types
    int x, y, d = M_water, sleepTime = 64, countVar = 0;

    //mouse is held variables
    int mouseStatusLeft = 0, mouseStatusRight = 0;

    //cursor rectangle
    SDL_Rect cursorRectangle;
	cursorRectangle.x = 0;
	cursorRectangle.y = 0;
	cursorRectangle.w = CELL_SIZE;
	cursorRectangle.h = CELL_SIZE;

	//make sure the program waits for a quit
	int quit = false;

    //Initialize
    if( init() == false ) return 1;

    //Load the files
    if( load_files() == false ) return 2;

    //Update the screen
    if( SDL_Flip( screen ) == -1 ) return 3;

    //initialize the cell stuff. This gets the cell system up and running. This also sets all cells to air
    init_cell_stuff();



///-------------------------------------
///putting test materials into grid
    int i;
    //for(i=0 ; i<GRID_WIDTH ; i++){
	//	for(j=0 ; j<GRID_HEIGHT ; j++){
	//		cellData[i][j] = M_water;
	//	}
    //}
    for(i=0 ; i<20 ; i++){
		cellData[i+13][16] = M_rock;
	}
///--------------------------------------

    //While the user hasn't quit
    while( quit == false ){

    	//While there's an event to handle
    	while( SDL_PollEvent( &event ) ){

    		//If the user has Xed out the window
    		if( event.type == SDL_QUIT ){
				//Quit the program
				quit = true;
			}
			

            if( event.type == SDL_MOUSEBUTTONDOWN ){
				x = event.motion.x;
				y = event.motion.y;
                if( event.button.button == SDL_BUTTON_LEFT ){
                    mouseStatusLeft = 1;
                }

                else if( event.button.button == SDL_BUTTON_RIGHT ){
                    mouseStatusRight = 1;
                }
            }

            if(event.type == SDL_MOUSEBUTTONUP){
				x = event.motion.x;
				y = event.motion.y;
                if( event.button.button == SDL_BUTTON_LEFT ){
                    mouseStatusLeft = 0;
                }
                else if( event.button.button == SDL_BUTTON_RIGHT ){
                    mouseStatusRight = 0;
                }
            }
            if( event.type == SDL_MOUSEMOTION ){
				x = event.motion.x;
				y = event.motion.y;
            }

            if( event.type == SDL_KEYDOWN ){
                switch( event.key.keysym.sym ){
                    case SDLK_UP: d++; break;
                    case SDLK_DOWN: d--; break;
                    case SDLK_c: reset_cells();  break;
                    case SDLK_LEFT: sleepTime /= 2; break;
                    case SDLK_RIGHT: sleepTime *= 2; if(sleepTime == 0){sleepTime = 1;} break;
                    case SDLK_ESCAPE: quit = true; // quit with escape
                    case SDLK_EQUALS: zoomplus(); break;
                    case SDLK_MINUS: zoomminus(); break;
                    default: break;
                    }
                }

    	} // end while(event)
		//no more events to handle at the moment.
        if(mouseStatusLeft == 1){
            setcell(x, y, d);
            }

        else if(mouseStatusRight == 1){
            deletecell(x, y, d);
        }

        countVar++;
        //speed of gameplay
        if(sleepTime <= 0)
        {
            sleepTime = 0;
        }

        //evealuate cells
        if(countVar >= sleepTime){
            evaluate_cells();
            countVar = 0;
        }

        //updates screen with cells
        print_cells();

        //print recagle for cursor
        cursorRectangle.x = x - CELL_SIZE/2;
        cursorRectangle.y = y - CELL_SIZE/2;
        cursorRectangle.w = cursorRectangle.h = CELL_SIZE;
        SDL_FillRect( screen , &cursorRectangle , mats[d].color);

        //updates the screen
        SDL_Flip( screen );

        //Sleep(sleepTime);
    }// end while(quit == false)


    //Free the surface and quit SDL
    clean_up();

    return 0;
}
