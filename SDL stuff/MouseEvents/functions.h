SDL_Rect clips[4];

SDL_Surface *load_image( char* filename )
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;
    
    //Load the image with either SDL_image or LoadBMP. NOT both.
    loadedImage = IMG_Load( filename );
    //loadedImage = SDL_LoadBMP( filename );
    
    //If the image was loaded correctly
    if( loadedImage != NULL )
    {
        // Create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );
        //Free the old image
        SDL_FreeSurface( loadedImage );
    }
    
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
		return false;
	}
	
	//Set up the screen
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
	
	//If there was an error setting up the screen
	if(screen == NULL )
	{
		return false;
	}
	
	//Set the window caption
	SDL_WM_SetCaption( "Jen's SDL Program", NULL );
	
	//If everything initialized fine
	return true;
}

bool load_files()
{
	//Load the image
	buttonSheet = load_image( "buttonSheet.png" );
	
	//if there was an error in loading the image
	if( buttonSheet == NULL )
	{
		return false;
	}
	
	//If everthing loaded fine
	return true;
}


void clean_up()
{
	//free the image
	SDL_FreeSurface( buttonSheet );
	
	//Quit SDL
	SDL_Quit();
}

class Button
{
	private:
	//The attributes of the box
	SDL_Rect box;
	
	//The part of the button sprite sheet that will be shown
	SDL_Rect* clip;
	
	public:
	//Initializes the variables
	Button( int x, int y, int w, int h );
	
	//Handles events and set the buttons sprite region
	void handle_events();
	
	//Shows the button on the screen
	void show();
};

void set_clips()
{
	clips[ CLIP_MOUSEOVER ].x = 0;
	clips[ CLIP_MOUSEOVER ].y = 0;
	clips[ CLIP_MOUSEOVER ].w = 320;
	clips[ CLIP_MOUSEOVER ].h = 240;
	
	clips[ CLIP_MOUSEOUT ].x = 320;
	clips[ CLIP_MOUSEOUT ].y = 0;
	clips[ CLIP_MOUSEOUT ].w = 320;
	clips[ CLIP_MOUSEOUT ].h = 240;
	
	clips[ CLIP_MOUSEDOWN ].x = 0;
	clips[ CLIP_MOUSEDOWN ].y = 240;
	clips[ CLIP_MOUSEDOWN ].w = 320;
	clips[ CLIP_MOUSEDOWN ].h = 240;
	
	clips[ CLIP_MOUSEUP ].x = 320;
	clips[ CLIP_MOUSEUP ].y = 240;
	clips[ CLIP_MOUSEUP ].w = 320;
	clips[ CLIP_MOUSEUP ].h = 240;
}

Button::Button( int x, int y, int w, int h )
{
	//Set attributes of the Button
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
	
	//Set the default sprite
	clip = &clips[ CLIP_MOUSEOUT ];
}

void Button::handle_events()
{
	//The mouse offsets
	int x = 0, y = 0;
	
	//If the mouse moved
	if( event.type == SDL_MOUSEMOTION )
	{
		//Get the mouse offsets
		x = event.motion.x;
		y = event.motion.y;
		
		//If the mouse is over the button
		if(  (x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h) );
			//Set the button sprite
			clip = &clips[ CLIP_MOUSE_OVER ];
		else
			clip = &clips[ CLIP_MOUSEOUT ];
	}
	//If a mouse button was pressed
	if(event.type == SDL_MOUSEBUTTONDOWN )
	{
		//If the left mouse button was pressed
		if( event.button.button == SDL_BUTTON_LEFT )
		{
			//Get the mouse offsets
			x = event.button.x;
			y = event.button.y;
			
			//If the mouse is over the button
			if(  (x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h) );
			clip = &clips[ CLIP_MOUSEDOWN ];
		}
	}
	//If a mouse button was released
	if( event.type == SDL_MOUSEBUTTONUP )
	{
		//IF the left mouse button was released
		if( event.button.button == SDL_BUTTON_LEFT )
		{
			//get mouse offsets
			x = event.button.x;
			y = event.button.y;
			
			//If the mouse is over the button
			if(  (x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h) );
				clip = &clips[ CLIP_MOUSEUP ];
		}
	}
}

void Button::show()
{
	apply_surface( box.x, box.y, buttonSheet, screen, clip );
}
