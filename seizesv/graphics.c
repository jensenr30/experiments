
#include "graphics.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include "globals.h"
#include "utilities.h"
#include <math.h>


/// this returns the pixel data of a pixel at a certain point on a surface (color and alpha in an uint32_t)
uint32_t get_pixel(SDL_Surface *surface, int x, int y){
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
        return *(uint32_t *)p;
        break;
	
    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

/// this sets's a pixel's data (color and alpha)
void set_pixel(SDL_Surface *surf, int x, int y, uint32_t pixel){
    uint32_t *p = (uint32_t *)( surf->pixels + (surf->pitch * y) + x*surf->format->BytesPerPixel );
	*p = pixel;
}

/// draws a pixel to the screen BUT FIRST CHECKING that it is within the screen
// this is a bounded pixel set (it won't crash the program when it tells SDL to set a pixel outside of a surface
void draw_pixel(SDL_Surface *dest, int x, int y, uint32_t color)
{
	if(x >= 0 && y >=0 && x < dest->w && y < dest->h) set_pixel(dest, x, y, color);
}

/// this function will mix two colors (according to their respective weight) and return the resulting color.
// everything is uint32_t, 32 bits unsigned integer
uint32_t color_mix_weighted(uint32_t color1, uint32_t color2, uint32_t weight1, uint32_t weight2){
	
	// calculate total weight
	uint32_t weight = weight1 + weight2;
	
	// calculate individual values for all three color bytes (and the alpha byte)
	uint32_t alpha =		( ((color1>>24)&0xff)*weight1 + ((color2>>24)&0xff)*weight2 ) / (weight);
	uint32_t red =		( ((color1>>16)&0xff)*weight1 + ((color2>>16)&0xff)*weight2 ) / (weight);
	uint32_t green =		( ((color1>>8 )&0xff)*weight1 + ((color2>>8 )&0xff)*weight2 ) / (weight);
	uint32_t blue =		( ((color1    )&0xff)*weight1 + ((color2    )&0xff)*weight2 ) / (weight);
	
	// return the weighted, mixed color.
	return (alpha<<24) | (red<<16) | (green<<8) | blue;
}

uint32_t color_mix_weighted_f(unsigned int color1, unsigned int color2, float weight1, float weight2){
	
	// calculate total weight
	float weight = weight1 + weight2;
	
	// calculate individual values for all three color bytes (and the alpha byte)
	uint32_t alpha =		( ((color1>>24)&0xff)*weight1 + ((color2>>24)&0xff)*weight2 ) / (weight);
	uint32_t red =		( ((color1>>16)&0xff)*weight1 + ((color2>>16)&0xff)*weight2 ) / (weight);
	uint32_t green =		( ((color1>>8 )&0xff)*weight1 + ((color2>>8 )&0xff)*weight2 ) / (weight);
	uint32_t blue =		( ((color1    )&0xff)*weight1 + ((color2    )&0xff)*weight2 ) / (weight);
	
	// return the weighted, mixed color.
	return (alpha<<24) | (red<<16) | (green<<8) | blue;
	
}


/// This function returns an alpha mixed color from an original plus a new color
/* inputs:
	[color_orig]		The original color of the pixel in question
	[color_new]			The new coloring being painted over the original color.
						The alpha (first 8 bits: 0xFF000000) the alpha of [color_new]
						determines the amount 
	outputs:
		result of mixing the two colors
*/
uint32_t color_over(uint32_t color_orig, uint32_t color_new ){
	uint32_t alpha_orig = color_orig >> 24;
	uint32_t alpha_new  = color_new  >> 24;
	// calcualte the new alpha
	uint32_t alpha_out = ( 0xff - (0xff-alpha_orig)*(0xff-alpha_new) );
	
	// calculate the color mix
	uint32_t color_out = color_mix_weighted(color_orig,color_new,0xff-alpha_new,alpha_new);
	
	// add the color mix and the alpha calculation
	return (  (alpha_out<<24) | (color_out&0x00ffffff)  );
	
}


/// this function will draw a rectangle at (x,y) with width, w, and height, h.
// this function is bounded (meaning it will not accidentally draw outside of the surface).
// This function should not crash the program due to segmentation fault errors.
// dest is the destination SDL_Surface that the image will be printed to.
// colorBorder is the color of the border of the rectangle (inside the bounds of x,y w,h)
// colorFill is the color of the rectangle inside the border.
// colorBorder and colorFill are interpreted as 32-bit colors (0xAARRGGBB) where A = alpha, R = red, B = blue, G = green.
// if doFill is 0, then this function will only print the border. if doFill is any non-zero number, then the rectangle will be filled with the "colorFill" color.
// returns 0 success.
// returns 1 on invalid dest
short draw_rect(SDL_Surface *dest, int x, int y, int w, int h, int borderThickness, uint32_t colorBorder, uint32_t colorFill, char doFill){
	
	// check for a NULL destination surface pointer.
	if(dest == NULL){
		error("draw_rect() was passed an invalid dest pointer. dest = NULL");
		return 1;
	}
	
	// calculate starting/stopping positions
	int i, j, istart = x, jstart = y, istop = x+w, jstop = y+h, temp;
	// swap istart and istop if istop is less than istart
	if(istop < istart){
		temp = istop;
		istop = istart;
		istart = temp;
	}
	// swap jstart and jstop if jstop is less than jstart
	if(jstop < jstart){
		temp = jstop;
		jstop = jstart;
		jstart = temp;
	}
	// bound the 
	if(istart < 0) istart = 0;
	if(istop > dest->w) istop = dest->w;
	if(jstart < 0) jstart = 0;
	if(jstop > dest->h) jstop = dest->h;
	
	// draw the rectangle
	for(i=istart; i<istop; i++){
		for(j=jstart; j<jstop; j++){
			// at every i,j index, figure out if that pixel is part of the border.
			if(fabs(i-x) < borderThickness || fabs((x+w)-i) <= borderThickness || fabs(j-y) < borderThickness || fabs((y+h)-j) <= borderThickness){
				// if it is, set it to the color of the border.
				set_pixel(dest, i, j, colorBorder);
			}
			else{
				// otherwise, set it to the fill color, but only if we are supposed to do so.
				if(doFill)set_pixel(dest, i, j, colorFill);
			}
		}
	}
	return 0;
}


/*
/// returns a pointer to the loaded texture.
SDL_Texture *load_image_to_texture(char *filename){
	
	//attempt to load the image
	SDL_Surface *tempSurface = IMG_Load(filename);
	
	// if the image was not loaded to a surface correctly,
	if(tempSurface == NULL){
		// create an error message to write to file.
		char message[512];
		strcpy(message, "error in load_image(): could not load file to surface \"");
		strcat(message, filename);
		strcat(message, "\"");
		error(message);
		// and return NULL.
		return NULL;
	}
	
	// try to convert the surface into a texture
	SDL_Texture *tempTexture = SDL_CreateTextureFromSurface(myRenderer, tempSurface);
	
	// if the texture was not created from surface correctly,
	if(tempTexture == NULL){
		// write and error message to the error log
		error("error in load_image(): could not create texture from surface");
		// and return NULL.
		return NULL;
	}
	
	//  if the image loaded correctly, return a pointer to the texture that contains it.
	return tempTexture;
}
*/

/// intersect_p is for when you know some point on each line <x,y> and the slopes of each line.
// returns 1 (1)	 if there is a single intersection
// returns 0 (0) if the lines are parallel but they are not the same line
// returns 2		 if the lines are parallel and they are the same line (have all points in common)

// point <x1,y1> is a point on the first line
// point <x2,y2> is a point on the second line
// slope1 is the slope of the first line  (change-in-y/change-in-x)
// slope2 is the slope of the second line (change-in-y/change-in-x)
// point <xr,yr> is the resulting point where the two lines intersect.
// xr and yr are pointers to variables outside of this function.

int intersect_p(float x1, float y1, float slope1, float x2, float y2, float slope2, float *xr, float *yr){
	
	//------------------------------------------------------------
	// check to see if the lines are parallel and handle special cases
	//------------------------------------------------------------
	if(slope1 == slope2 || slope1 == -slope2){				// if the two lines share the same slope,
		if(x1==x2){											// if the two x points are the same,
			if(y1==y2){										// if the two y points are the same,
				return 2;									// the two lines share an infinite number of points
			}												//otherwise,
			return 0;										// the lines are parallel but not the same line. they share no points.
		}
		float connSlope = (y2-y1)/(x2-x1);					// calculate the slope of a third line that connects the two given data points.
		if(connSlope == slope1 || connSlope == -slope1){	// if the slope between the two points given in the same magnitude as the slopes of the lines,
			return 2;										// there are an infinite number of intersection points
		}
		else{												// otherwise,
			return 0;										// there are no intersection points
		}
	}
	//------------------------------------------------------------
	// calculate where the intersect point is
	//------------------------------------------------------------
	
	//calculate y intercepts
	float b1 = y1 - x1*slope1;
	float b2 = y2 - x2*slope2;
	
	// calculate the intersection coordinates <xr,yr>
	*xr = (b2-b1)/(slope1-slope2);
	*yr = slope1*(*xr) + b1;
	
	// a single intersection point is found.
	return 1; 
}

/// RYAN PLEASE TODO:
void draw_line(SDL_Surface *dest, float x1, float y1, float x2, float y2, float thickness, unsigned int lineColor){
	
	//-------------------------------------------------------------------------------
	// setting up variables
	//-------------------------------------------------------------------------------
	// these are the differences in x and y.
	float xdiff = x2-x1;
	float ydiff = y2-y1;
	
	// these are the slopes of x and y. This describes how fast they change with respect to a unit step in the line parameter, t.
	float xslope;
	float yslope;
	
	// this is the maximum difference (either the difference in y or the difference in y, depending on which is bigger.)
	float bigdiff;
	
	if(fabs(ydiff) > fabs(xdiff)){			// the difference in y is greater than the difference in x
		bigdiff = ydiff;
		xslope = xdiff/bigdiff;
		yslope = 1.0;
	}
	else{						// the difference in x is greater than the difference in y
		bigdiff = xdiff;
		xslope = 1;
		yslope = ydiff/bigdiff;
	}
	if(xslope == 0){				// make sure xslope is not zero. we need to divide by that!
		xslope = 1/VERTICAL;		// make xslope insanely tiny (so that y can change a lot and x will change change a VERY small amount.
	}
	//-------------------------------------------------------------------------------
	// check to see if BOTH points are out of bounds
	//-------------------------------------------------------------------------------
	if(!within_screen(x1,y1) && !within_screen(x2,y2)){
		
		// a temporary solution (this doesn't allow lines that have points outside the screen to be drawn THROUGH the screen)
		return;															
			
		// used to collect the resulting intersection points with the screen.
		float xr, yr, xr1=-1, yr1=-1, xr2=-1, yr2=-1;
		char foundOne = 0;
		
		// check top screen bound intersection
		if( intersect_p(x1,y1,yslope/xslope, 0,0,HORIZONTAL, &xr,&yr)==1){
			if(within_screen(xr,yr)){
				if(foundOne==0){
					xr1=xr;
					yr1=yr;
				}
				else{
					xr2=xr;
					yr2=yr;
				}
				foundOne = 1;
			}
		}
		// check bottom screen bound intersection
		if( intersect_p(x1,y1,yslope/xslope, 0,windH-1,HORIZONTAL, &xr,&yr)==1){
			if(within_screen(xr,yr)){
				if(foundOne==0){
					xr1=xr;
					yr1=yr;
				}
				else{
					xr2=xr;
					yr2=yr;
				}
				foundOne = 1;
			}
		}
		// check left screen bound intersection
		if( intersect_p(x1,y1,yslope/xslope, 0,0,VERTICAL, &xr,&yr)==1){
			if(within_screen(xr,yr)){
				if(foundOne==0){
					xr1=xr;
					yr1=yr;
				}
				else{
					xr2=xr;
					yr2=yr;
				}
				foundOne = 1;
			}
		}
		// check right bound intersection
		if( intersect_p(x1,y1,yslope/xslope, windW-1,0,VERTICAL, &xr,&yr)==1){
			if(within_screen(xr,yr)){
				if(foundOne==0){
					xr1=xr;
					yr1=yr;
				}
				else{
					xr2=xr;
					yr2=yr;
				}
				foundOne = 1;
			}
		}
		// if you found two spots where the line intersects (an entry and exit point)
		if(xr2 != -1 && yr2 != -1){
			// draw a line between those points (now, no part of the line is outside the screen)
			draw_line(dest, xr1, yr1, xr2, yr2, thickness, lineColor);
			return;
		}
	}
	//-------------------------------------------------------------------------------
	// check to see if ONE of the points is out of bounds
	//-------------------------------------------------------------------------------
	else if(!within_screen(x1,y1) || !within_screen(x2,y2)){
		
		// used to collect the resulting intersection points with the screen.
		float xr, yr, xr1=-1, yr1=-1;
		
		char foundOne = 0;
		
		float xin, yin; // these are the coordinates of the inside point
		float xout, yout; // these are the coordinates of the outside point
		// store the inside points in xin and yin floating point variables.
		if(within_screen(x1,y1)){
			xin = x1;
			yin = y1;
			xout = x2;
			yout = y2;
		}
		else{
			xin = x2;
			yin = y2;
			xout = x1;
			yout = y1;
		}
		
		// this records the direction that x travels when going from inside the screen to outside it. (1 or -1)
		//float xSignChange = (xin-xout);
		
		
		
		// check top screen bound intersection
		if( !foundOne && intersect_p(x1,y1,yslope/xslope, 0,0,HORIZONTAL, &xr,&yr)==1){
			if(within_screen(xr,yr)){
				if((yin-yr)*(yin-yout) >=0){
					xr1=xr;
					yr1=yr;
					foundOne = 1;
				}
			}
		}
		// check bottom screen bound intersection
		if( !foundOne && intersect_p(x1,y1,yslope/xslope, 0,windH-1,HORIZONTAL, &xr,&yr)==1){
			if(within_screen(xr,yr)){
				if((yin-yr)*(yin-yout) >=0){
					xr1=xr;
					yr1=yr;
					foundOne = 1;
				}
			}
		}
		// check left screen bound intersection
		if( !foundOne && intersect_p(x1,y1,yslope/xslope, 0,0,VERTICAL, &xr,&yr)==1){
			if(within_screen(xr,yr)){
				if((xin-xr)*(xin-xout) >=0){
					xr1=xr;
					yr1=yr;
					foundOne = 1;
				}
			}
		}
		// check right bound intersection
		if( !foundOne && intersect_p(x1,y1,yslope/xslope, windW-1,0,VERTICAL, &xr,&yr)==1){
			if(within_screen(xr,yr)){
				if((xin-xr)*(xin-xout) >=0){
					xr1=xr;
					yr1=yr;
					foundOne = 1;
				}
			}
		}
		// if you found the exit point of the line,
		if(foundOne){
			// draw a line between that exit point and the one valid point inside the screen. now no part of the line is outside the screen.
			if(within_screen(x1,y1))
				draw_line(dest, x1, y1, xr1, yr1, thickness, lineColor);
			else
				draw_line(dest, x2, y2, xr1, yr1, thickness, lineColor);
		}
		return;
	}
	//-------------------------------------------------------------------------------
	// drawing valid in-bounds line
	//-------------------------------------------------------------------------------
	// this is the arbitrary parameter than will step through the line's pixels
	
	//swap the x's if necessary to correct the sign of bigdiff.
	if(bigdiff<0){
		bigdiff*=-1.0;
		x1=x2;
		y1=y2;
	}
	float t;
	for(t=0; t<=bigdiff; t=t+1.0){
		set_pixel(dest, (int)(x1 + xslope*t), (int)(y1 + yslope*t), lineColor);
	}
	
}

/// RYAN TODO:
/// ADD DOCUMENETAION
/// ADD SOME 0.5 NUMBERS
/// limit the bounds to be withing the surface limits!! Don't bother looping through all those pixels that aren't in the surface!!!!
/// DON'T BOTHER TAKING THE SQUARE ROOT! JUST CHECK THE SQUARES! IT HAS THE SAME EFFECT! SQUARE THE RADIUS AND THEN CHECK IF ( (i-x)*(i-x)+(j-y)*(j-y) ) is less than ( radius*radius )
// this draws a circle with radius and color at point (x,y)
void draw_circle(SDL_Surface *dest, float x, float y, float radius, uint32_t color){
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
			if(dist <= radius && i>=0 && j>=0 && i<dest->w && j<dest->h)
				set_pixel(dest, i, j, color_over(get_pixel(dest,i,j),color) );
		}
	}
}



