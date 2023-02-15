#include <SDL2/SDL.h>
#include "globals.h"

#define within_screen(x,y) (x>=0 && x<windW && y>=0 && y<windH)
#define VERTICAL 10000.0f
#define HORIZONTAL 0.0001f

uint32_t get_pixel(SDL_Surface *surface, int x, int y);
void set_pixel(SDL_Surface *surf, int x, int y, uint32_t pixel);

SDL_Texture *load_image_to_texture(char *filename);

int intersect_p(float x1, float y1, float slope1, float x2, float y2, float slope2, float *xr, float *yr);
void draw_line(SDL_Surface *dest, float x1, float y1, float x2, float y2, float thickness, unsigned int lineColor);
void draw_circle(SDL_Surface *dest, float x, float y, float radius, uint32_t color);
short draw_rect(SDL_Surface *dest, int x, int y, int w, int h, int borderThickness, uint32_t colorBorder, uint32_t colorFill, char doFill);
void draw_pixel(SDL_Surface *dest, int x, int y, uint32_t color);


// this returns a even mixture of color1 and color2
#define color_mix(color1, color2) ( ((((0xff000000&color1)>>1)+((0xff000000&color2)>>1))&0xff000000) | ((((0xff0000&color1)+(0xff0000&color2))>>1)&0xff0000) | ((((0xff00&color1)+(0xff00&color2))>>1)&0xff00) | ((((0xff&color1)+(0xff&color2))>>1)&0xff) )

//#define color_mix_weighted(color1, color2, weight1, weight2) (  ((((color1>>24)*weight1 + (color2>>24)*weight2)/(weight1 + weight2))<<24)  |  (((((color1>>16)&0xff)*weight1 + ((color2>>16)&0xff)*weight2)/(weight1 + weight2))<<16)  |  (((((color1>>8)&0xff)*weight1 + ((color2>>8)&0xff)*weight2)/(weight1 + weight2))<<8)  |  (((color1&0xff)*weight1 + (color2&0xff)*weight2)/(weight1 + weight2))  )
uint32_t color_mix_weighted(unsigned int color1, unsigned int color2, unsigned int weight1, unsigned int weight2);
uint32_t color_mix_weighted_f(unsigned int color1, unsigned int color2, float weight1, float weight2);

//short print_camera_view(SDL_Surface *dest, struct cameraData *cam);
