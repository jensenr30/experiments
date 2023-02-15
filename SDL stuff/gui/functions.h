
SDL_Surface *load_image( char* filename )
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


void apply_surface( int x, int y,  SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
	//Initialize all subsystems
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) return false;
	
	//Set up the screen
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
	
	//If there was an error setting up the screen, return false
	if(screen == NULL ) return false;
	
	//Initialize SDL_ttf
	if( TTF_Init() == -1 ) { return false; }
	
	//Set the window caption
	SDL_WM_SetCaption( "Ryan's SDL Program", NULL );
	
	/*If everything initialized fine */ return true;
}

bool load_files()
{
	//Load the image
	backdrop = load_image( "backdrop.png" );
	font = TTF_OpenFont( "FreeSansBold.ttf", 28 );
	
	
	//if there was an error in loading backdrop.png
	if( backdrop == NULL )return false;
	//If there was an error loading the font
	if( font == NULL ) return false;
	
	//If everthing loaded fine
	return true;
}


void clean_up()
{
	//free the IMAGES
	SDL_FreeSurface( backdrop );
	
	//Quit SDL
	SDL_Quit();
}


