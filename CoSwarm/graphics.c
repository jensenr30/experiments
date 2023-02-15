#include "graphics.h"
#include "general_functions.h"
#include "materials_and_cells.h"
#include "beast.h"
#include <SDL\SDL_image.h>



void init_graphics(){
	
	CELL_SIZE = DEFAULT_CELL_SIZE;
	
	SCREEN_WIDTH = DEFAULT_SCREEN_WIDTH;
	SCREEN_HEIGHT = DEFAULT_SCREEN_HEIGHT;
	
	FPS = 0;
	
	screen=	NULL;
	text =	NULL;
	icon =	NULL;
	
	font = NULL;
	font16 = NULL;
	
	cameraX = cameraY = 0;
	
}

//verify the current camera position
void camera_verify(){
	// forces camera within bounds of screen.
	if(cameraX < 0) cameraX = 0;
	if(cameraY < 0) cameraY = 0;
	if(cameraX + GRID_WIDTH >= GRID_WIDTH_ELEMENTS) cameraX = GRID_WIDTH_ELEMENTS - GRID_WIDTH - 1;
	if(cameraY + GRID_HEIGHT>= GRID_HEIGHT_ELEMENTS)cameraY = GRID_HEIGHT_ELEMENTS- GRID_HEIGHT- 1;
}

// pan the camera in some direction
void camera_pan(int direction){
	int panAmount = 100/CELL_SIZE;
	switch(direction){
		case d_up:    cameraY-=panAmount; break;
		case d_down:  cameraY+=panAmount; break;
		case d_left:  cameraX-=panAmount; break;
		case d_right: cameraX+=panAmount; break;
		default: break;
	}
	camera_verify();
}


 
SDL_Surface *load_image( char* filename ){
    //Temporary storage for the image that is loaded
    SDL_Surface* loadedImage = NULL;
    
    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;
    
    //Load the image with either SDL_image or LoadBMP. comment-out the one you are not using
    loadedImage = IMG_Load( filename );
    //loadedImage = SDL_LoadBMP( filename );
    
    //If the image was loaded correctly
    if( loadedImage != NULL ){
        // Create an optimized image
        optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
        //Free the old image
        SDL_FreeSurface( loadedImage );
    }
    
    //Return the optimized image
    return optimizedImage;
}





//this returns a pointer to an SDL_Surface
SDL_Surface *create_surface(int width, int height){
	
	// try to create surface
	SDL_Surface *retSurf = SDL_CreateRGBSurface(SDL_HWSURFACE, width, height, 32, 0xFF0000, 0x00FF00, 0x0000FF, 0xff000000);
	
	// check to see if the surface creation went well
	if(retSurf == NULL){
		quit_game(quit_surface_error, "Could not create surface.");
		return NULL;
	}
	
	SDL_Surface *retSurfAlpha = SDL_DisplayFormatAlpha(retSurf);
	// delete old surface
	SDL_FreeSurface(retSurf);
	return retSurfAlpha;
}

void apply_surface( int x, int y,  SDL_Surface* source, SDL_Surface* destination ){
    //make a temporary rectangle to hold offsets
    SDL_Rect offset;
    
    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;
    
    //Blit surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}






///this function produces a gradient on datsurface.
// the gradient will only be printed inside of the gradClip rectangle.
// at point 1 (x1,y1) there will be color1.
// at ponit 2 (x2,y2) there will be color2.
///horizontal gradients (y1=y2) and verticle gradients (x1=x2) are very fast compared to gradients at different slopes (where neither x1=x2 or y1=y2)
///if you are looking for speed, verticle/horizontal gradients are the way to go.
void gradient(SDL_Surface *datsurface, SDL_Rect *gradClip, int x1, int y1, int x2, int y2, Uint32 color1, Uint32 color2, unsigned int gradientType){
	
	// there is no point in printing a gradient with only a single point
	if(x1 == x2 && y1 == y2){
		return;
	}
	
	// this is the integer used for the color of (i,j) pixel in the gradient
	long unsigned int color;
	// these are all one-time calculations. these values will be used in the loop.
	unsigned int alp1 = color1/0x1000000;
	unsigned int red1 = (color1/0x10000)%0x100;
	unsigned int gre1 =(color1/0x100)%0x100;
	unsigned int blu1 = color1%0x100;
	unsigned int alp2 = color2/0x1000000;
	unsigned int red2 = (color2/0x10000)%0x100;
	unsigned int gre2 =(color2/0x100)%0x100;
	unsigned int blu2 = color2%0x100;
	
	// this is for displaying the pixel at (i,j)
	SDL_Rect pixelRect;
	pixelRect.w = 1;
	pixelRect.h = 1;
	
	
	
	float m, b1,b2,diff,b,x,y;
	
	int i,j; // variables used to loop through the columns and row respectively.
	
	// if the gradient has no slope
	if(x1 == x2){
		diff = (y2-y1);
		pixelRect.x = gradClip->x;
		pixelRect.w = gradClip->w;
		// we will print rectangles that are 1-pixel tall horizontal line segments
		for(j=gradClip->y; j<gradClip->y+gradClip->h; j++){	// loop through the rows    of the gradient clip
			y = (float)j;	// calculate y-intercept for this point (i,j)
			if(y < y1) 					// the pixel is not between the two points
				color = color1;			// choose color1
			else if( y > y2) 			// the pixel is not between the two points
				color = color2; 		// choose color2
			else{
				color = (int)((alp1*(y2-y) + alp2*(y-y1))/diff)*0x1000000;	// calculate alpha color component
				color+= (int)((red1*(y2-y) + red2*(y-y1))/diff)*0x10000;	// calculate red   color component
				color+= (int)((gre1*(y2-y) + gre2*(y-y1))/diff)*0x100;		// calculate green color component
				color+= (int)((blu1*(y2-y) + blu2*(y-y1))/diff);			// calculate blue  color component
			}
			pixelRect.y = y;
			SDL_FillRect(datsurface, &pixelRect, color);
		}
	}
	// if the gradient has infinite(very large slope
	else if(y1 == y2){
		// we will print rectangels that are 1-pixel wide verticle line segments
		diff = (x2-x1);
		pixelRect.y = gradClip->y;
		pixelRect.h = gradClip->h;
		// we will print rectangles that are 1-pixel tall horizontal line segments
		for(i=gradClip->x; i<gradClip->x+gradClip->w; i++){	// loop through the rows    of the gradient clip
			x = (float)i;	// calculate y-intercept for this point (i,j)
			if(x < x1) 					// the pixel is not between the two points
				color = color1;			// choose color1
			else if( x > x2) 			// the pixel is not between the two points
				color = color2; 		// choose color2
			else{
				color = (int)((alp1*(x2-x) + alp2*(x-x1))/diff)*0x1000000;	// calculate alpha color component
				color+= (int)((red1*(x2-x) + red2*(x-x1))/diff)*0x10000;	// calculate red   color component
				color+= (int)((gre1*(x2-x) + gre2*(x-x1))/diff)*0x100;		// calculate green color component
				color+= (int)((blu1*(x2-x) + blu2*(x-x1))/diff);			// calculate blue  color component
			}
			pixelRect.x = x;
			SDL_FillRect(datsurface, &pixelRect, color);
		}
	}
	// if the slope is a non-zero finite value
	else{
		//this is for the lines perpendicular to the original line. it is -1/original_line_slope.
		//this is the slope that will be used when calculating the color of each pixel
		m = ((float)(x1-x2))/((float)(y2-y1));	// calculate slope of the line perpendicular to the gradient line
		b1 = y1 - m*x1;							// rearranged form of  y = mx + b  to calculate the the y-intercept for b1 
		b2 = y2 - m*x2;							// similar shenanigans for b2
		diff = b2 - b1;						// calculate the difference in the y-intercept terms
	
		for(i=gradClip->x; i<gradClip->x+gradClip->w; i++){			// loop through the columns of the gradient clip
			for(j=gradClip->y; j<gradClip->y+gradClip->h; j++){		// loop through the rows    of the gradient clip
				pixelRect.x = i;
				pixelRect.y = j;
				b = (float)j - m*(float)i;	// calculate y-intercept for this point (i,j)
				if(b < b1) 					// the pixel is not between the two points
					color = color1;			// choose color1
				else if( b > b2) 			// the pixel is not between the two points
					color = color2; 		// choose color2
				else{
					color = (int)((alp1*(b2-b) + alp2*(b-b1))/diff)*0x1000000;	// calculate alpha color component
					color+= (int)((red1*(b2-b) + red2*(b-b1))/diff)*0x10000;	// calculate red   color component
					color+= (int)((gre1*(b2-b) + gre2*(b-b1))/diff)*0x100;		// calculate green color component
					color+= (int)((blu1*(b2-b) + blu2*(b-b1))/diff);			// calculate blue  color component
				}
				SDL_FillRect(datsurface, &pixelRect, color);
				
			}
		}
	}
}



void print_debugging_information(SDL_Surface *dest){
	//----------------------------------------------------
	// PRINT PLAYER POSITION INFORMATION
	//----------------------------------------------------
	static char textMessage[100]; // this holds the string that tells you what the player's position is.
	static char textDummy[100]; // this holds misc text values generated by the itoa() function.
	
	static SDL_Surface *textSurface;
	static SDL_Color white;
	white.r = white.g = white.b = 0xff; // set white color
	/*
	strcpy(textMessage,"x_pos=");						// "x_pos="
	itoa((int)player.x_pos,textDummy,10);				// generate integer portion of x pos in string form
	strcat(textMessage,textDummy);						// "x_pos=1234"
	strcat(textMessage,".");								// "x_pos=1234."
	itoa(((int)(player.x_pos*1000))%1000,textDummy,10);	// generate the first three decimal places of x_pos
	strcat(textMessage,textDummy);						// "x_pos=1234.567"
	
	textSurface = TTF_RenderText_Blended(font16,textMessage, white);	// render text
	apply_surface(3, -7, textSurface, dest);							// apply text
	SDL_FreeSurface(textSurface);
	
	strcpy(textMessage," y_pos=");						// "y_pos="
	itoa((int)player.y_pos,textDummy,10);				// generate integer portion of y_pos in string form
	strcat(textMessage,textDummy);						// "y_pos=1234"
	strcat(textMessage,".");								// "y_pos=1234."
	itoa(((int)(player.y_pos*1000))%1000,textDummy,10);	// generate the first three decimal places of y_pos
	strcat(textMessage,textDummy);						// "y_pos=1234.567"
	
	
	textSurface = TTF_RenderText_Blended(font16,textMessage, white);	// render text
	apply_surface(145, -7, textSurface, dest);							// apply text
	SDL_FreeSurface(textSurface);
	*/
	strcpy(textMessage,"#beasts=");						// "x_pos="
	itoa(beastsNumberOf,textDummy,10);				// generate integer portion of x pos in string form
	strcat(textMessage,textDummy);						// "#beasts=256"
	textSurface = TTF_RenderText_Blended(font16,textMessage, white);	// render text
	apply_surface(3, -7, textSurface, dest);							// apply text
	SDL_FreeSurface(textSurface);
	
	//----------------------------------------------------
	// PRINT MOUSE LOCATION INFO
	//----------------------------------------------------
	strcpy(textMessage, "x=");							// "x="
	itoa(cameraX, textDummy, 10);						// generate string of the cameraX value
	strcat(textMessage, textDummy);						// "x=1920"
	
	textSurface = TTF_RenderText_Blended(font16,textMessage, white);	// render text
	apply_surface(300, -7, textSurface, dest);						// apply text
	SDL_FreeSurface(textSurface);
	
	strcpy(textMessage, "y=");							// "y="
	itoa(cameraY, textDummy, 10);						// generate string of the cameraY value
	strcat(textMessage, textDummy);						// "y=1080"
	
	textSurface = TTF_RenderText_Blended(font16,textMessage, white);	// render text
	apply_surface(372, -7, textSurface, dest);						// apply text
	SDL_FreeSurface(textSurface);
	
	//----------------------------------------------------
	// PRINT TICKS and FPS INFORMATION
	//----------------------------------------------------
	strcpy(textMessage, "Ticks=");						// "Ticks="
	itoa(SDL_GetTicks(), textDummy, 10);				// generate string of the number of ticks
	strcat(textMessage, textDummy);						// "Ticks=123456789"
	textSurface = TTF_RenderText_Blended(font16,textMessage, white);	// render text
	apply_surface(100, 13, textSurface, dest);						// apply text
	SDL_FreeSurface(textSurface);
	
	strcpy(textMessage, "FPS=");									// "FPS="
	itoa(FPS, textDummy, 10);										// generate string of the current FPS
	strcat(textMessage, textDummy);									// "FPS=31"
	textSurface = TTF_RenderText_Blended(font16,textMessage, white);// render text
	apply_surface(3, 13, textSurface, dest);						// apply text
	SDL_FreeSurface(textSurface);
	/*
	//----------------------------------------------------
	// PRINT onCollMat value of the player
	//----------------------------------------------------
	strcpy(textMessage,"onCollMat=");
	if(player.onCollMat)
		strcat(textMessage,"1");
	else
		strcat(textMessage,"0");
	textSurface = TTF_RenderText_Blended(font16,textMessage, white);	// render text
	apply_surface(3, 33, textSurface, dest);						// apply text
	SDL_FreeSurface(textSurface);
	*/
}





//this draws a line on the screen from point (x1,y1) to point (x2,y2)
// this draws the line (mathematically) from the centers of the two pixels.
void draw_line(SDL_Surface *theSurface, int x1, int y1, int x2, int y2, int thickness, int lineColor){
	//this is the rectangle describing the pixel to color in.
	SDL_Rect myPixel;
	myPixel.w = 1;
	myPixel.h = 1;
	
	//handle lines with no x-difference
	if(x1 == x2){
		// this handles the special case that the line is a point
		if(y1 == y2){
			// draw a point
			myPixel.x = x1;
			myPixel.y = y1;
			SDL_FillRect(theSurface, &myPixel, lineColor);
			// done drawing a point. that's all folks!
			return;
		}
		//this handles the special case the the line is a verticle line (slope infinity)
		// this swaps the x and y values so that the function draws a line with a finite slope (zero)
		// the myPixel rectangle is no longer a pixel. it is now being used as a vertical line
		myPixel.w = 1;
		myPixel.x = x1;
		if(y2-y1 >= 0){
			myPixel.h = y2-y1;
			myPixel.y = y1;
		}
		else{
			myPixel.h = y1-y2;
			myPixel.y = y2;
		}
		
		SDL_FillRect(theSurface, &myPixel, lineColor);
		return;
	}
	
	float slope = (float)(y2-y1)/(float)(x2-x1);
	//generate an absolute value of the slope
	float absval_slope = slope;
	if(slope < 1) absval_slope *= -1;
	float x,y;
	//this is used to mathematically determine where the line should be.
	float line_value;
	
	// if the absolute value of the slope is less than 1, index through the x values
	if(absval_slope < 1){
		//all of this assumes that x1 <= x2
		float pixel_offset = 0.5;
		//x2 is greater than x1
		int low_x = x1;
		int high_x = x2;
		int ref_y = y1;		// this is the reference y. this is where we start
		
		// this takes care of the special case of x1 being bigger than x2.
		if(x1 > x2){
			pixel_offset *= -1;
			//x2 is less than x1
			low_x = x2;
			high_x = x1;
			ref_y = y2;
		}
		
		
		for(x=low_x+pixel_offset,myPixel.x=low_x; x<high_x; x+=1,myPixel.x++){
			line_value = (x-low_x)*slope + ref_y;
			myPixel.y = line_value; // integer assignment. truncate decimal places
			// if the line_value has decimal place value greater than or equal to 0.5, then round up.
			if(line_value-(int)line_value > 0.5) myPixel.y++;
			// only print the pixel if it is within the screen bounds
			if(myPixel.x>=0 && myPixel.x<SCREEN_WIDTH && myPixel.y>=0 && myPixel.y<SCREEN_HEIGHT)
				SDL_FillRect(theSurface, &myPixel, lineColor);
		}
	}
	// otherwise, the absolute value of the slope is greater to or equal to one, so index through the y values
	else{
				
		//all of this assumes that y1 <= y2
		float pixel_offset = 0.5;
		//y2 is greater than y1
		int low_y = y1;
		int high_y = y2;
		int ref_x = x1;		// this is the reference x. this is where we start
		
		// this takes care of the special case of y1 being bigger than y2.
		if(y1 > y2){
			pixel_offset *= -1;
			//y2 is less than y1
			low_y = y2;
			high_y = y1;
			ref_x = x2;
		}
		
		
		for(y=low_y+pixel_offset,myPixel.y=low_y; y<high_y; y+=1,myPixel.y++){
			line_value = (y-low_y)/slope + ref_x;
			myPixel.x = line_value; // integer assignment. truncate decimal places
			// if the line_value has decimal place value greater than or equal to 0.5, then round up.
			if(line_value-(int)line_value > 0.5) myPixel.x++;
			// only print the pixel if it is within the screen bounds
			if(myPixel.x>=0 && myPixel.x<SCREEN_WIDTH && myPixel.y>=0 && myPixel.y<SCREEN_HEIGHT)
				SDL_FillRect(theSurface, &myPixel, lineColor);
		}
	}
	
}


void print_grid(SDL_Surface *dest){
	int i,j;
	SDL_Rect cell;
	cell.w = cell.h = CELL_SIZE;
	
	for(j=0; j<GRID_HEIGHT && j<cameraY+GRID_HEIGHT_ELEMENTS; j++){
		for(i=0; i<GRID_WIDTH && i<cameraX+GRID_WIDTH_ELEMENTS; i++){
			cell.x = i*CELL_SIZE;
			cell.y = j*CELL_SIZE;
			SDL_FillRect(dest, &cell, mats[grid[j+cameraY][i+cameraX].mat].color);
		}
	}
}

// this prints all of the beasts to the screen
void print_beasts(SDL_Surface *dest){
	int i;
	SDL_Rect cell;
	cell.w = cell.h = CELL_SIZE;
	
	/// this part of the code does not YET support the linked list architecture of the beast block list.
	for(i=0; i<BEASTS_BLOCK_SIZE; i++){
		if(beasts.bp[i] != NULL){			// if the beast at this index in the beast list is valid...
			if(within_grid_screen(beasts.bp[i]->x, beasts.bp[i]->y)){ // if the beast is inside the screen in grid terms
				cell.x = (beasts.bp[i]->x-cameraX)*CELL_SIZE;
				cell.y = (beasts.bp[i]->y-cameraY)*CELL_SIZE;
				SDL_FillRect(dest, &cell, 0xffffff00);//beasts.bp[i]->color);
			}
		}
	}
}


//prints each beast's target with a line (if it has one)
void print_beasts_targets(SDL_Surface *dest){
	int b;
	for(b=0; b<BEASTS_BLOCK_SIZE; b++){
		if(beasts.bp[b] != NULL){
			if(beasts.bp[b]->targetActive == true){
				draw_line(screen, (beasts.bp[b]->x-cameraX)*CELL_SIZE+CELL_SIZE/2, (beasts.bp[b]->y-cameraY)*CELL_SIZE+CELL_SIZE/2, (beasts.bp[b]->target[0]-cameraX)*CELL_SIZE+CELL_SIZE/2, (beasts.bp[b]->target[1]-cameraY)*CELL_SIZE+CELL_SIZE/2, 1, 0xffff00ff);
			}
		}
	}
}

