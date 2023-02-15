
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


void blit_glider(){
	apply_surface(posx - 24, posy - 24, glider, screen);
}

void init_trail(){
	int i;
	for(i=0; i<TRAIL_LENGTH; i++)
		trail[i][0] = trail[i][1] = -1;
}

void blit_trail(){
	int i;
	for(i=0; i<TRAIL_LENGTH; i++)
		if(trail[i][0] >= 0 && trail[i][1] >= 0) set_pixel(screen,trail[i][0],trail[i][1],TRAIL_COLOR);
}


void blit_background(void){
	int i, j;

	for(i = 0; i < SCREEN_WIDTH; i+=500){
		for(j = 0; j < SCREEN_HEIGHT; j+=500){
			apply_surface(i,j,background, screen);
		}
	}
	
}
