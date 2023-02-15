
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
		return false;
	}
	
	//Initialize SDL_ttf
	if( TTF_Init() == -1 )
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
	SDL_WM_SetCaption( "Charge Movement v0.1", NULL );
	
	//If everything initialized fine
	return true;
}

bool load_files()
{
	//Load the image
	pro = load_image( "CM resources\\pro.png" );
	ele = load_image( "CM resources\\ele.png" );
	white = load_image( "CM resources\\white.png" );
	clicked = load_image( "CM resources\\clicked.png" );
	nue = load_image( "CM resources\\nue.png" );
	
	//if there was an error in loading the image
	if( pro == NULL || ele == NULL || nue == NULL || white == NULL || clicked == NULL )
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
	SDL_FreeSurface( white );
	SDL_FreeSurface( clicked );
	//Quit SDL
	SDL_Quit();
}



void white_screen()
{
	int i, j;
	for(i = 0; i < SCREEN_HEIGHT; i += 50)
	{
		for(j = 0; j < SCREEN_WIDTH; j += 50)
			apply_surface(i, j, white, screen);
	}
}
