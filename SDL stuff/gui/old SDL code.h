
SDL_Surface* spritesheet = NULL;

//The portions of the sprite map to be blitted
SDL_Rect clip[ 4 ];

//Clip range for "play" button
clip[ 0 ].x = 0;
clip[ 0 ].y = 0;
clip[ 0 ].w = 200;
clip[ 0 ].h = 50;

//Clip range for "quit" button
clip[ 1 ].x = 0;
clip[ 1 ].y = 50;
clip[ 1 ].w = 200;
clip[ 1 ].h = 50;

	//Display images
    apply_surface( 50, 300, spritesheet, screen, &clip[0] );
    apply_surface( 350, 300, spritesheet, screen, &clip[1] );
    
    //The color of the font
	SDL_Color textColor = { 255, 255, 255 };
    
    //Render the text
	message = TTF_RenderText_Solid( font, "New                    Load                     Quit", textColor );
	apply_surface(40, 325, message, screen );

spritesheet = load_image("spritesheet.png");
//if there was an error in loading spritesheet.png
if( spritesheet == NULL ) return false;
SDL_FreeSurface( spritesheet );
