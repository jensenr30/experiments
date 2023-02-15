void apply_tile( int, int, int );
void apply_item( int, int, int );
void defrag_map_v2(struct map *, struct map *);

SDL_Surface *load_image( char *filename ){
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
    else{
		handle_error(1, filename);
    }
    
    //Return the optimized image
    return optimizedImage;
}

void apply_surface( int x, int y,  SDL_Surface *source, SDL_Surface *destination ){
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
int apply_text(int x, int y, TTF_Font *theFont, char *theString, SDL_Color theColor){
	SDL_Surface *theSurface = NULL;
	if(strcmp(theString, " ") != 0)
		theSurface = TTF_RenderText_Blended(theFont, theString, theColor); // attempt rendering text
	if(theSurface == NULL){
		SDL_FreeSurface(theSurface); // clean the surface
		return 0; // rendering text didn't work. return 0
	}
	apply_surface(x, y, theSurface, screen); // apply surface at x, y
	SDL_FreeSurface(theSurface); // clean the surface
	return 1;
}


void apply_surface_clips( int x, int y,  SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip ){
    //make a temporary rectangle to hold offsets
    SDL_Rect offset;
    
    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;
    
    //Blit surface
    SDL_BlitSurface( source, clip, destination, &offset );
}




//this manipulates the player
void move_player( char direction ){
	if (direction == UP)
	playerPosition[1]--;
	else if(direction == DOWN)
	playerPosition[1]++;
	else if(direction == LEFT)
	playerPosition[0]--;
	else if(direction == RIGHT)
	playerPosition[0]++;
}




void blank_screen(){
	int i, j;
	for(j = 0; j < SCREEN_HEIGHT; j += 128){
		for(i = 0; i < SCREEN_WIDTH; i += 128){
			apply_surface(i, j, black512, screen);
		}
	}
	
	
}

void grid_screen(){
	int i, j;
	for(j = 0; j < SCREEN_HEIGHT; j += 128){
		for(i = 0; i < SCREEN_WIDTH; i += 128){
			apply_surface(i, j, grid512, screen);
		}
	}
	
	
}


void print_map(struct map *datmap){
	SDL_Rect screenRect;
	//load up the screen coordinates and the screen size (in terms of tiles. i.e. the screenRect.x is the tile position that the screen is at.)
	screenRect.x = cameraPos[0];
	screenRect.y = cameraPos[1];
	screenRect.w = SCREEN_WIDTH  / TILE_SIZE - 1;
	screenRect.h = SCREEN_HEIGHT / TILE_SIZE - 1;
	int i;
	
	//print tiles
	for(i = 0; i < MAX_TILES_PER_MAP && i < datmap->tsp; i++){
		// quit if you have found the last valid tile
		if( datmap->tiles[i].type == t_EOT  ) break;
		//if( datmap->tiles[i].type == t_SKIP ) continue;
		// only apply surface if you need to. don't do it if it lies outside the screen.
		if( within_rect( datmap->tiles[i].x, datmap->tiles[i].y, &screenRect) ){
			apply_tile( datmap->tiles[i].type, datmap->tiles[i].x - cameraPos[0], datmap->tiles[i].y - cameraPos[1] );
		}
	}
	
	//print items
	for(i = 0; i < MAX_ITEMS_PER_MAP && i < datmap->isp; i++){
		// quit if you have found the last valid item
		if( datmap->items[i].type == i_EOI  ) ;//break;
		//if( datmap->items[i].type == i_SKIP ) ;//continue;
		// only apply items if you need to. don't do it if it lies outside the screen.
		if( within_rect( datmap->items[i].x, datmap->items[i].y, &screenRect) ){
			apply_item( datmap->items[i].type, datmap->items[i].x - cameraPos[0], datmap->items[i].y - cameraPos[1] );
		}
	}
	
	//print spawn
	apply_tile( t_SPAWN, currentMap.spawnx - cameraPos[0], currentMap.spawny - cameraPos[1] );
}


void update_map(int blank_screen_first, int display_player){
	if(blank_screen_first)
		blank_screen();
	print_map(&currentMap);
	
	//apply player position
	if(display_player)
		apply_surface( (playerPosition[0]-cameraPos[0]) * TILE_SIZE, (playerPosition[1]-cameraPos[1]) * TILE_SIZE, player, screen);
}



/*
puts a tile on the screen
tile number should be input as a hexadecimal number such from 0x0000 to 0xFFFF.
the first two hex bits correspond to the x position in the tile_set.
the second two hex bits correspond to the y position in the tile_set.
*/
void apply_tile( int tile_number, int tile_x, int tile_y){
	SDL_Rect tile_clip;
	tile_clip.w = tile_clip.h = TILE_SIZE;
	tile_clip.x = TILE_SIZE * ( tile_number / (0x0100) );
	tile_clip.y = TILE_SIZE * ( tile_number % (0x0100) );
	apply_surface_clips(tile_x * TILE_SIZE, tile_y * TILE_SIZE, tile_set, screen, &tile_clip);
}

void apply_item( int item_number, int item_x, int item_y){
	SDL_Rect item_clip;
	item_clip.w = item_clip.h = TILE_SIZE;
	item_clip.x = TILE_SIZE * ( item_number / (0x0100) );
	item_clip.y = TILE_SIZE * ( item_number % (0x0100) );
	apply_surface_clips(item_x * TILE_SIZE, item_y * TILE_SIZE, item_set, screen, &item_clip);
}


//applys the texture at the PIXEL x,y coordinates
void apply_tile_coor( int tile_number, int coor_x, int coor_y){
	SDL_Rect tile_clip;
	tile_clip.h = tile_clip.w = TILE_SIZE;
	tile_clip.x = TILE_SIZE * ( tile_number / (0x0100) );
	tile_clip.y = TILE_SIZE * ( tile_number % (0x0100) );
	apply_surface_clips(coor_x, coor_y, tile_set, screen, &tile_clip);
}

//applys the texture at the PIXEL x,y coordinates
void apply_item_coor( int item_number, int coor_x, int coor_y){
	SDL_Rect item_clip;
	item_clip.h = item_clip.w = TILE_SIZE;
	item_clip.x = TILE_SIZE * ( item_number / (0x0100) );
	item_clip.y = TILE_SIZE * ( item_number % (0x0100) );
	apply_surface_clips(coor_x, coor_y, item_set, screen, &item_clip);
}

//applys the texture at the PIXEL x,y coordinates
void apply_tile_coor_inventory( int tile_number, int coor_x, int coor_y){
	SDL_Rect tile_clip;
	tile_clip.h = tile_clip.w = INVENTORY_TILE_SIZE;
	tile_clip.x = INVENTORY_TILE_SIZE * ( tile_number / (0x0100) );
	tile_clip.y = INVENTORY_TILE_SIZE * ( tile_number % (0x0100) );
	apply_surface_clips(coor_x, coor_y, tile_set_inventory, screen, &tile_clip);
}

//applys the texture at the PIXEL x,y coordinates
void apply_item_coor_inventory( int item_number, int coor_x, int coor_y){
	SDL_Rect item_clip;
	item_clip.h = item_clip.w = INVENTORY_TILE_SIZE;
	item_clip.x = INVENTORY_TILE_SIZE * ( item_number / (0x0100) );
	item_clip.y = INVENTORY_TILE_SIZE * ( item_number % (0x0100) );
	apply_surface_clips(coor_x, coor_y, item_set_inventory, screen, &item_clip);
}



//returns a 1 if the x,y coordinate is within the Rect. returns 0 otherwise.
int within_rect(int x, int y, SDL_Rect *clip){
	// do not try to evaluate if the clip is null
	if(clip == NULL){
		handle_error(10, "NULL clip in function:\n\twithin_rect(int x, int y, SDL_Rect *clip)");
		return 0;
	}
	if(x >= clip->x && x <= clip->w + clip->x){
		if(y >= clip->y && y <= clip->h + clip->y){
			//within the rectangle
			return 1;
		}
	}
	//position was not within the rectangle
	return 0;
}





// returns 0 if no string was input. returns 1 if successful
// allows the user to type in a text message up to string_length - 2. the function uses string_length number of elements in the char array.
// blanks the input_string first
int input_string( char *input_string, int string_length, TTF_Font *my_font, SDL_Color my_color){
	int i;
	//blank the input_string
	for(i = 0; i < string_length; i++){
		input_string[i] = '\0';
	}
	
	int times = 0, cursorblink = 200;
	int index = 0;
    while( 1 ){
    	//While there's an event to handle
    	while(SDL_PollEvent(&event)){
    		//If the user has Xed out the window
    		if(event.type == SDL_QUIT){
				//Quit the program
				quit_game();
			}
			if(event.type == SDL_KEYDOWN){
				if(index >= string_length - 1) index = string_length - 2;
				if( event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z ){
					if(index < string_length - 2 ){
						input_string[index++] = event.key.keysym.sym;
					}
				}
				else
				{
					switch(event.key.keysym.sym){
					case SDLK_MINUS:
						input_string[index++] = '-';
					case SDLK_0:
						input_string[index++] = '0';
						break;
					case SDLK_1:
						input_string[index++] = '1';
						break;
					case SDLK_2:
						input_string[index++] = '2';
						break;
					case SDLK_3:
						input_string[index++] = '3';
						break;
					case SDLK_4:
						input_string[index++] = '4';
						break;
					case SDLK_5:
						input_string[index++] = '5';
						break;
					case SDLK_6:
						input_string[index++] = '6';
						break;
					case SDLK_7:
						input_string[index++] = '7';
						break;
					case SDLK_8:
						input_string[index++] = '8';
						break;
					case SDLK_9:
						input_string[index++] = '9';
						break;
					case SDLK_ESCAPE:
						input_string[index] = '\0';
						return 0;
						break;
					case SDLK_RETURN:
						input_string[index] = '\0';
						return 1;
						break;
					case SDLK_BACKSPACE:
						// don't overwrite memory you weren't supposed to  :P
						if(index < 1) index = 1;
						input_string[index] = '\0';
						input_string[--index] = '\0';
						break;
					case SDLK_DELETE:
						for(i = 0; i <string_length; i++)
							input_string[i] = '\0';
						index = 0;
						break;
					case SDLK_SPACE:
						if(index < string_length - 2 )
							input_string[index++] = ' ';
						break;
					default:
						break;					
					}
				}
			}
    	}
    	//apply the text cursor
    	if(times > cursorblink/10) input_string[index] = '|';
    	else input_string[index] = '\0';
    	text = TTF_RenderText_Blended(my_font, input_string, my_color);
		apply_surface(SCREEN_WIDTH/2 - 400, SCREEN_HEIGHT/2 - 50, textBox, screen);
		apply_surface(SCREEN_WIDTH/2 - 370, SCREEN_HEIGHT/2 - 25, text, screen);
		if(SDL_Flip( screen ) == -1) handle_error(0, NULL);
		//free up that memory. without this, the game exploded to 2 GB in RAM! xD
		SDL_FreeSurface( screen ); // clean up (prevent memory leaks)
		SDL_FreeSurface( text );   // clean up (prevent memory leaks)
		// take a brake, jo.
		Sleep(10);
		//increment the times that the program has gone through rendering a frame.
		times++;
		//reset times
		if(times > cursorblink/5) times = 0;
    }
    //terminate the string.
    input_string[i] = '\0';
    return 1;
}


void zoom(int input){
	static int level = 32;
	
	int cameraCenter[2];
	
	cameraCenter[0] = cameraPos[0] + (SCREEN_WIDTH/2) / TILE_SIZE;
	cameraCenter[1] = cameraPos[1] + (SCREEN_HEIGHT/2) / TILE_SIZE;
	
	
	//takes care of translating the input number into what level you are at.
	switch(input){
	case ZOOM_IN:
		level = level << 1;
		break;
	case ZOOM_OUT:
		level = level >> 1;
		break;
	default:
		level = input;
		break;
	}
	if(level < 8)   level = 8;
	if(level > 128) level = 128;
	
	//variables;
	char tile_set_name[128]; // name length is a maximum of 128 (bigger than we'll need
	char item_set_name[128]; // ''
	char player_name[128];   // ''
	
	// picks the right file path.
	switch(level){
	case 128:
		strcpy(tile_set_name, "resources\\_tile_set_128.png");
		strcpy(item_set_name, "resources\\_item_set_128.png");
		strcpy(player_name, "resources\\_Davu128.png");
		break;
	case 64:
		strcpy(tile_set_name, "resources\\_tile_set_64.png");
		strcpy(item_set_name, "resources\\_item_set_64.png");
		strcpy(player_name, "resources\\_Davu64.png");
		break;
	case 32:
		strcpy(tile_set_name, "resources\\_tile_set_32.png");
		strcpy(item_set_name, "resources\\_item_set_32.png");
		strcpy(player_name, "resources\\_Davu32.png");
		break;
	case 16:
		strcpy(tile_set_name, "resources\\_tile_set_16.png");
		strcpy(item_set_name, "resources\\_item_set_16.png");
		strcpy(player_name, "resources\\_Davu16.png");
		break;
	case 8:
		strcpy(tile_set_name, "resources\\_tile_set_8.png");
		strcpy(item_set_name, "resources\\_item_set_8.png");
		strcpy(player_name, "resources\\_Davu8.png");
		break;
	default:
		handle_error(10, "zoom level error");
		strcpy(tile_set_name, "resources\\_tile_set_64.png");
		strcpy(item_set_name, "resources\\_item_set_64.png");
		strcpy(player_name, "resources\\_Davu64.png");
		break;
	}
	
	// load tile_set
	SDL_FreeSurface(tile_set);   // clean up (prevent memory leaks)
	tile_set = load_image(tile_set_name); // load the correct tile_set_xxx
	if(tile_set == NULL){ // if there was an error in loading surface
		handle_error(1, tile_set_name);
	}
	
	// load item_set
	SDL_FreeSurface(item_set);   // clean up (prevent memory leaks)
	item_set = load_image(item_set_name); // load the correct item_set_xxx
	if(item_set == NULL){ // if there was an error in loading surface
		handle_error(1, item_set_name);
	}


	// load player
	SDL_FreeSurface(player);   // clean up (prevent memory leaks)
	player = load_image(player_name); // load the correct player_xxx
	if(player == NULL){ // if there was an error in loading player surface
		handle_error(1, player_name);
	}


	// make the tile size the appropriate size.
	TILE_SIZE = level;

	// re-orient the camera
	cameraPos[0] = cameraCenter[0] - (SCREEN_WIDTH / TILE_SIZE)/2;
	cameraPos[1] = cameraCenter[1] - (SCREEN_HEIGHT / TILE_SIZE)/2;
	
}

void set_screen_size(){
	// make sure the values are multiples of the PIXELS_PER_SCREEN_DIVISION number.
	SCREEN_WIDTH = ( SCREEN_WIDTH / PIXELS_PER_SCREEN_DIVISION ) * PIXELS_PER_SCREEN_DIVISION;
	SCREEN_HEIGHT = ( SCREEN_HEIGHT / PIXELS_PER_SCREEN_DIVISION) * PIXELS_PER_SCREEN_DIVISION;
	
	// make sure the screen isn't too small
	if(SCREEN_WIDTH < PIXELS_PER_SCREEN_DIVISION * 4) SCREEN_WIDTH = PIXELS_PER_SCREEN_DIVISION * 4;
	if(SCREEN_HEIGHT < PIXELS_PER_SCREEN_DIVISION * 4) SCREEN_HEIGHT = PIXELS_PER_SCREEN_DIVISION * 4;
	
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
	
	init_buttons(); // re-initialize the buttons
}
