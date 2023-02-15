#include "graphics.h"
#include "math.h"
#include "plot.h"
#include "globals.h"



/// this returns the pixel data of a pixel at a certain point on a surface (color and alpha in an Uint32)
Uint32 get_pixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	
    switch(bpp) {
    case 1:
        return *p;
        break;
	
    case 2:
        return *(Uint16 *)p;
        break;
	
    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;
	
    case 4:
        return *(Uint32 *)p;
        break;
	
    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}
/// this sets's a pixel's data (color and alpha)
void set_pixel(SDL_Surface *surf, int x, int y, Uint32 pixel){
    Uint32 *p = (Uint32 *)( surf->pixels + (surf->pitch * y) + x*surf->format->BytesPerPixel );
	*p = pixel;
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

// return 1 if applied surface
// returns 0 otherwise
/// this applies text at point (x,y) using the given font, message, and color.
int apply_text(SDL_Surface *datsurface, int x, int y, TTF_Font *theFont, char *theString, SDL_Color theColor){
	SDL_Surface *theSurface = NULL;
	if(strcmp(theString, " ") != 0)
		theSurface = TTF_RenderText_Blended(theFont, theString, theColor); // attempt rendering text
	if(theSurface == NULL){
		SDL_FreeSurface(theSurface); // clean the surface
		return 0; // rendering text didn't work. return 0
	}
	apply_surface(x, y, theSurface, datsurface); // apply surface at x, y
	SDL_FreeSurface(theSurface); // clean the surface
	return 1;
}


/// this applies a source surface (with a clipping rectangle) to a destination at point (x,y)
void apply_surface_clips( int x, int y,  SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip ){
    //make a temporary rectangle to hold offsets
    SDL_Rect offset;
    
    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;
    
    //Blit surface
    SDL_BlitSurface( source, clip, destination, &offset );
}



// this will apply an outline to a box area described by an input SDL_Rectangle
void apply_outline(SDL_Surface *dest, SDL_Rect *box, unsigned short thickness, Uint32 fillColor){
	SDL_Rect border;
	
	// print top border
	border.x = box->x;
	border.y = box->y;
	border.w = box->w;
	border.h = thickness;
	SDL_FillRect(dest, &border, fillColor);
	
	// print bottom border
	border.y = box->y + box->w - thickness;
	SDL_FillRect(dest, &border, fillColor);
	
	// print right border
	border.x = box->x;
	border.y = box->y;
	border.w = thickness;
	border.h = box->h;
	SDL_FillRect(dest, &border, fillColor);
	
	// print left border
	border.x = box->x + box->w - thickness;
	SDL_FillRect(dest, &border, fillColor);
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
		SDL_Rect myRect;
		myRect.w = thickness;
		myRect.h = y1-y2;
		myRect.x = x1 - ((int)0.5*thickness);
		if(y1 < y2)
			myRect.y = y1;
		else
			myRect.y = y2;
		SDL_FillRect(theSurface, &myRect ,lineColor);
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
		/* OLD CODE FOR GRADUAL SLOPE LINES
		// swap the points around if x1 > x2
		if(x1 > x2){
			
			int tempval=x1;	// store x1
			x1 = x2;		// put x2 into x1
			x2 = tempval;	// put the value that used to be in x1 into x2.
			tempval = y1;	// store y1
			y1 = y2;		// put y2 into y1
			y2 = tempval;	// put the value that used to be in y1 into y2.
		}
		
		for(x=x1+0.5,myPixel.x=x1; x<x2; x+=1.0,myPixel.x++){
			line_value = slope*x +y1;
			myPixel.y = line_value; // integer assignment. truncate decimal places
			// if the line_value has decimal place value greater than or equal to 0.5, then round up.
			if(line_value-(int)line_value >= 0.5) myPixel.y++;
				
			SDL_FillRect(theSurface, &myPixel, lineColor);
		}
		*/
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
				
			SDL_FillRect(theSurface, &myPixel, lineColor);
		}
	}
	// otherwise, the absolute value of the slope is greater to or equal to one, so index through the y values
	else{
		/*
		// swap the points around if y1 > y2
		if(x1 > x2){
			int tempval=x1;	// store x1
			x1 = x2;		// put x2 into x1
			x2 = tempval;	// put the value that used to be in x1 into x2.
			tempval = y1;	// store y1
			y1 = y2;		// put y2 into y1
			y2 = tempval;	// put the value that used to be in y1 into y2.
		}
		*/
		
		
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
				
			SDL_FillRect(theSurface, &myPixel, lineColor);
		}
	}
}

// this draws a circle with radius and color at point (x,y)
void draw_circle(SDL_Surface *dest, float x, float y, float radius, Uint32 color){
	if(dest == NULL) return;
	
	float xLowBound = x - radius;
	float xHighBound= x + radius;
	float yLowBound = y - radius;
	float yHighBound= y + radius;
	int i,j;
	float dist;
	for(i=(int)xLowBound; i<=(int)(xHighBound+1); i++){
		for(j=(int)yLowBound; j<=(int)(yHighBound+1); j++){
			dist = sqrtf((i-x)*(i-x) + (j-y)*(j-y) );
			if(dist <= radius && i>=0 && j>=0 && i<SCREEN_WIDTH && j<SCREEN_HEIGHT)
				set_pixel(dest, i, j, color);
		}
	}
	
}








