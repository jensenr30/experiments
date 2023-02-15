
/// this sets's a pixel's data (color and alpha)
void set_pixel(SDL_Surface *surf, int x, int y, Uint32 pixel){
    Uint32 *p = (Uint32 *)( surf->pixels + (surf->pitch * y) + x*surf->format->BytesPerPixel );
	*p = pixel;
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
		draw_line(theSurface,y1,x1,y2,x2,thickness,lineColor);
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


SDL_Surface *load_image( char *filename )
{
    //Temporary storage for the image that is loaded
    SDL_Surface* loadedImage = NULL;
    
    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;
    
    //Load the image with either SDL_image or LoadBMP. comment-out the one you are not using
    loadedImage = IMG_Load( filename );
    //loadedImage = SDL_LoadBMP( filename );
    
    //If the image was loaded correctly
    if( loadedImage != NULL )
    {
        // Create an optimized image
        optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
        //Free the old image
        SDL_FreeSurface( loadedImage );
    }
    
    //Return the optimized image
    return optimizedImage;
}

void apply_surface( int x, int y,  SDL_Surface* source, SDL_Surface* destination )
{
    //make a temporary rectangle to hold offsets
    SDL_Rect offset;
    
    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;
    
    //Blit surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}

bool init()
{
	//Initialize all subsystems
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
	{
		exit(9);
	}
	
	//Initialize SDL_ttf
	if( TTF_Init() == -1 )
	{
		exit(10);
	}
	
	font = TTF_OpenFont("ttf\\FreeMonoBold.ttf", font_size);
	if(font == NULL){
		MessageBox(NULL, "Could not load ttf\\FreeMonoBold.ttf file.", "Error loading font", MB_OK);
		return false;
	}
	//Set up the screen
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
	
	//If there was an error setting up the screen
	if(screen == NULL )
	{
		exit(11);
	}
	
	//Set the window caption
	SDL_WM_SetCaption( "Charge Movement v1.1", NULL );
	
	//If everything initialized fine
	return true;
}

bool load_files()
{
	//Load the image
	pro = load_image( "images\\pro.png" );
	ele = load_image( "images\\ele.png" );
	clicked = load_image( "images\\clicked.png" );
	nue = load_image( "images\\nue.png" );
	grid_section = load_image( "images\\grid_section.png" );
	
	//if there was an error in loading the image
	if( pro == NULL || ele == NULL || nue == NULL || grid_section == NULL || clicked == NULL )
	{
		return false;
	}
	
	//If everthing loaded fine
	return true;
}


void clean_up()
{
	//free the image
	SDL_FreeSurface( screen );
	SDL_FreeSurface( text );
	SDL_FreeSurface( pro );
	SDL_FreeSurface( ele );
	SDL_FreeSurface( nue );
	SDL_FreeSurface( grid_section );
	SDL_FreeSurface( clicked );
	//Quit SDL
	SDL_Quit();
}



void white_screen()
{
	int a, b;
	int i, j;
	//it is necessary to know which of the two (screen_height or screen_width) is bigger.
	//that will determine the way in which we make the background.
	if(SCREEN_HEIGHT > SCREEN_WIDTH)
	{
		a = SCREEN_HEIGHT;
		b = SCREEN_WIDTH;
	}
	else
	{
		a = SCREEN_WIDTH;
		b = SCREEN_HEIGHT;
	}
	//blit the entire background
	for(i = 0; i < a; i += 50)
	{
		for(j = 0; j < b; j += 50)
			apply_surface(i, j, grid_section, screen);
	}
}
