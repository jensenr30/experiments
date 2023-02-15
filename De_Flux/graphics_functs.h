void defrag_map_v2(struct map *, struct map *);


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
	player.y--;
	else if(direction == DOWN)
	player.y++;
	else if(direction == LEFT)
	player.x--;
	else if(direction == RIGHT)
	player.x++;
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

///what in the hell was this empty function supposed to do?
//was this supposed to print the little images that show what items are inside boxes?
void print_item_in_box_notification(itemNumber){
	
	
	
	
	
	
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




///this prints maps
void print_map(struct map *datmap){
	SDL_Rect screenRect;
	//load up the screen coordinates and the screen size (in terms of tiles. i.e. the screenRect.x is the tile position that the screen is at.)
	screenRect.x = cameraPos[0];
	screenRect.y = cameraPos[1];
	screenRect.w = SCREEN_WIDTH  / TILE_SIZE - 1;
	screenRect.h = SCREEN_HEIGHT / TILE_SIZE - 1;
	int i,j;
	
	//these help me keep track of the porperties of the screen so i can know when to regenerate a background image.
	static int lastSCREEN_WIDTH		= -1;
	static int lastSCREEN_HEIGHT	= -1;
	static int lastTILE_SIZE		= -1;
	static int lastdefaultTile		= -1;
	
	// This is the background surface. I use it for printing the defaultTile to.
	static SDL_Surface *background = NULL;
	//this tells me where to copy and paste from the teil_set.
	SDL_Rect defaultTileClips;
	
	///this part 
	//if the defaultTile is valid
	if(datmap->defaultTile != t_EOT && datmap->defaultTile != t_SKIP){
		//if porperties of the screen have changed since the last time or if the defaultTile has changed
		if(lastSCREEN_HEIGHT != SCREEN_HEIGHT || lastSCREEN_WIDTH != SCREEN_WIDTH || lastTILE_SIZE != TILE_SIZE || lastdefaultTile != datmap->defaultTile){
			if(background != NULL)
				SDL_FreeSurface(background); // free the backgruond surface if it is valid.
			background = create_surface(SCREEN_WIDTH, SCREEN_HEIGHT); // create new backgruond surface.
			//debugging messages
			if(background == NULL) handle_error(10, "couldn't create background image");
			//generate clips for the tile in the tile_set
			defaultTileClips.x = (datmap->defaultTile/0x100)*TILE_SIZE;
			defaultTileClips.y = (datmap->defaultTile%0x100)*TILE_SIZE;
			defaultTileClips.h = defaultTileClips.w = TILE_SIZE;
			//render the new background
			for(j=0; j<SCREEN_HEIGHT/TILE_SIZE; j++){
				for(i=0; i<SCREEN_WIDTH/TILE_SIZE; i++){
					apply_surface_clips(i*TILE_SIZE, j*TILE_SIZE, tile_set, background, &defaultTileClips);
				}
			}
		}
		//apply the backgroun image to the screen
		apply_surface(0,0, background, screen);
	}
	
	
	
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
		//if( datmap->items[i].type == i_EOI  ) ;//break;
		// if there is a box here,
		if( get_tile(datmap->items[i].x, datmap->items[i].y) == t_box_closed){
			print_item_in_box_notification(i);
			continue; // don't print the item itself.
		}
		//if( datmap->items[i].type == i_SKIP ) ;//continue;
		// only apply items if you need to. don't do it if it lies outside the screen.
		if( within_rect( datmap->items[i].x, datmap->items[i].y, &screenRect) ){
			apply_item( datmap->items[i].type, datmap->items[i].x - cameraPos[0], datmap->items[i].y - cameraPos[1] );
		}
	}
	
	//print spawn
	apply_tile( t_SPAWN, currentMap.spawnx - cameraPos[0], currentMap.spawny - cameraPos[1] );
	
	//store the history variables
	lastSCREEN_HEIGHT = SCREEN_HEIGHT;
	lastSCREEN_WIDTH = SCREEN_WIDTH;
}


void update_map(int display_player){
	blank_screen();
	print_map(&currentMap);
	
	//apply player position
	if(display_player)
		apply_surface( (player.x-cameraPos[0]) * TILE_SIZE, (player.y-cameraPos[1]) * TILE_SIZE, playerAvatar, screen);
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
	apply_surface_clips(coor_x, coor_y, tile_set_32, screen, &tile_clip);
}


//applys the texture at the PIXEL x,y coordinates
void apply_item_coor_inventory( int item_number, int coor_x, int coor_y){
	SDL_Rect item_clip;
	item_clip.h = item_clip.w = INVENTORY_TILE_SIZE;
	item_clip.x = INVENTORY_TILE_SIZE * ( item_number / (0x0100) );
	item_clip.y = INVENTORY_TILE_SIZE * ( item_number % (0x0100) );
	apply_surface_clips(coor_x, coor_y, item_set_32, screen, &item_clip);
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

void apply_border(SDL_Surface *dest, SDL_Rect *clip, int color){
	
	SDL_Rect lineRect;
	
	//fill top line
	lineRect.x = clip->x;
	lineRect.y = clip->y;
	lineRect.w = clip->w;
	lineRect.h = 1;
	SDL_FillRect(dest, &lineRect, color);
	//fill bottom line
	lineRect.y += clip->h;
	SDL_FillRect(dest, &lineRect, color);
	//fill left line
	lineRect.y = clip->y;
	lineRect.h = clip->h;
	lineRect.w = 1;
	SDL_FillRect(dest, &lineRect, color);
	//fill right line
	lineRect.x += clip->w;
	lineRect.h++; // I don't know why this is needed. but "I NEED IT"
	SDL_FillRect(dest, &lineRect, color);
}


#define MAX_DROPDOWN_OPTIONS 40
///this accepts a list of strings and then allows the user to mouse-over each option and choose which he/she desires.
/*
strings is an array of pointers
strings[0] points to the first string,
strings[1] points to the seconds string,
etc... 
It works very well to do something like this for the strings:
	//lets have an example where there are 3 options, and thus three strings to send.
	char *myOptionStrings[3];
	myOptionStrings[0] = "Option #1";
	myOptionStrings[1] = "Option #2";
	myOptionStrings[2] = "Option #3";
*/
// n is the number of options you have. You will have n option lines to choose from.
//this function will display and allow the user to select between string[0], string[1], ... string[n-1].
//this function returns a number from 0 to n-1. that number is the string the user selected.
//if the user doesn't select any option, then this function returns -1
short dropdown(int x, int y, char n, char **optionStrings){
	//keep n properly bounded
	if(n>MAX_DROPDOWN_OPTIONS) n = MAX_DROPDOWN_OPTIONS;
	// why would there be less than one option? that is proposterous. return -1 on that bitch.
	if(n < 1) return -1;
	//option lines and offsets.
	int i, j;
	int lineSizeHeight = sansFont2Size;
	static SDL_Rect lineSize; // this is for specifying the size of option lines. the .y component is changed in the program to adjust to fit each option's place.
	lineSize.x = x;
	lineSize.h = lineSizeHeight; // this is the height of the option lines in the dropdown menu.
	lineSize.w = 128;			// this the the width of the option line size.
	static SDL_Rect textOffset; // this is the offset for where the text is placed in relation to the line of the dropdown menu it is on. ignore the .w and .h components of the structure.
	textOffset.x = 0;
	textOffset.y = -6;
	
	//make sure the dropdown is inside the screen size
	if(x + lineSize.w >= SCREEN_WIDTH) return dropdown(x - lineSize.w, y, n, optionStrings);		// too close to the right. Do a new dropdown menu that corrects that
	if(y + lineSize.h*n >= SCREEN_HEIGHT) return dropdown(x, y - lineSize.h*n, n, optionStrings);	// too close to the bottom. Do a new dropdown menu that corrects that
	
	
	//colors
	SDL_Color textColor = {0x00, 0x00, 0x00}; // color of the text
	static const int lineColor = 0xa0a0ba; // color of the option line beneath the text.
	int lineColorOver = lineColor + contrast; // color of the line under the text when the user's mouse is hovering over it.
	int lineColorDown = lineColor - contrast; // color of the option line beneath text when the user is clicking down on it.
	
	//mouse and keyboard input
	int key;
	bool quit = false;
	bool alt = false; // has the user pressed alt?
	bool mouseCurr = UP, mousePrev = UP; // keeping track of the user's mouse actions.
	SDL_Rect mouseCurrRect; // the .x and .y components are used to store the current location of the mouse. ignore the .w and .h components.
	mouseCurrRect.x = x; // init values
	mouseCurrRect.y = y; // init values
	SDL_Rect mousePrevRect; // the .x and .y components are used to store the previous location of the mouse. ignore the .w and .h components.
	mousePrevRect.x = x; // init values
	mousePrevRect.y = y; // init values
	bool optionLineAlreadyFound = false; // this keeps track of if you have already found the option line the user is hovering over.
	
	//text surface definitions and rendering.
	SDL_Surface *optionText[MAX_DROPDOWN_OPTIONS];
	for(i=0; i<n; i++){ // i has to be less than the number of options and the number of possible dropdown options.
		if(optionStrings[i] == NULL) continue; // if you encounter a null string just move past it. go to the next one.
		optionText[i] = TTF_RenderText_Blended(sansFont2, optionStrings[i], textColor); // generate the text and store it in optionText[i]
	}
	//While the user hasn't quit
    do{
    	//While there's an event to handle
    	while(SDL_PollEvent(&event)){
    		//If the user has Xed out the window
    		if(event.type == SDL_QUIT || quit == true){
				//Quit the program
				quit_game();
			}
			if(event.type == SDL_MOUSEBUTTONDOWN){
				if(event.button.button == 1){
					//set mouse state
					mouseCurr = DOWN;
					//store old mouse coordinates
					mousePrevRect.x = mouseCurrRect.x;
					mousePrevRect.y = mouseCurrRect.y;
					//update new mouse coordinates
					mouseCurrRect.x = event.button.x;
					mouseCurrRect.y = event.button.y;
				}
			}
			else if(event.type == SDL_MOUSEMOTION){
				mouseCurrRect.x = event.button.x;
				mouseCurrRect.y = event.button.y;
			}
			else if(event.type == SDL_MOUSEBUTTONUP){
				if(event.button.button == 1){
					//set mouse state
					mouseCurr = UP;
					//store old mouse coordinates
					mousePrevRect.x = mouseCurrRect.x;
					mousePrevRect.y = mouseCurrRect.y;
					//update new mouse coordinates
					mouseCurrRect.x = event.button.x;
					mouseCurrRect.y = event.button.y;
				}
			}
			else if(event.type == SDL_KEYDOWN){
				key = event.key.keysym.sym;
				if(key == SDLK_ESCAPE){
					//free optionText surfaces
					for(i=0; i<n; i++)
						SDL_FreeSurface(optionText[i]);
					return -1;//if the user presses escape
				}
				else if(key == SDLK_RALT || key == SDLK_LALT) alt = DOWN;
				else if(key == SDLK_F4){
					if(alt == DOWN) quit = true;
				}
			}
			else if(event.type == SDL_KEYUP){
					key = event.key.keysym.sym;
				if(key == SDLK_h){
					PlaySound("resources\\sounds\\_button_click.wav", NULL, SND_ASYNC);
					help("dropdown.txt");
				}
				else if(key == SDLK_RALT || key == SDLK_LALT) alt = UP;
			}
    	} // while ( SDL_PollEvent(&event) )
    	
    	//get whole area of all the dropdown menu options
    	lineSize.y = y;
    	lineSize.h = n*lineSizeHeight;
		//if the user presses AND RELEASES outside the valid dropdown menu area, return -1. nothing was selected
    	if(mouseCurr == UP && mousePrev == DOWN && within_rect(mouseCurrRect.x, mouseCurrRect.y, &lineSize) == false && within_rect(mousePrevRect.x, mousePrevRect.y, &lineSize) == false){
			//free optionText surfaces
			for(i=0; i<n; i++)
				SDL_FreeSurface(optionText[i]);
			return -1;
    	}
		//reset to porper height for lineSize.h.
		lineSize.h = lineSizeHeight;
		
		//default state of this variable
		optionLineAlreadyFound = 0;
		//this is the loop that displays the option backgrounds.
    	for(i=0; i<n; i++){
			//get position of the lineoption.
			lineSize.y = y + i*lineSize.h;
			
			//check to see if the user is over the option
			if( within_rect(mouseCurrRect.x, mouseCurrRect.y, &lineSize) && optionLineAlreadyFound == 0 ){
				// johnson, we have found our option line!
				optionLineAlreadyFound = 1;
				//is the user hovering?
				if(mouseCurr == UP && mousePrev == UP)
					SDL_FillRect(screen, &lineSize, lineColorOver);
					//is the user pressing down?
				else if(mouseCurr == DOWN)
					SDL_FillRect(screen, &lineSize, lineColorDown);
					//did the user just release? and was it on the same button that was pressed down earlier?
				else if(mouseCurr == UP && mousePrev == DOWN && within_rect(mousePrevRect.x, mousePrevRect.y, &lineSize)){
					//free optionText surfaces
					for(j=0; j<n; j++)
						SDL_FreeSurface(optionText[j]);
					return i;
				}
				else // normal color fill of this line option.
					SDL_FillRect(screen, &lineSize, lineColor);
			}
			else{
				//normal color fill of this line option.
				SDL_FillRect(screen, &lineSize, lineColor);
			}
			apply_surface(lineSize.x + textOffset.x, lineSize.y + textOffset.y, optionText[i], screen);
    	}
    	
    	
    	SDL_Flip(screen);
		SDL_FreeSurface( screen );   // clean up (prevent memory leaks)
		
		mousePrev = mouseCurr;
	} while(1); // end do{}
	
	
	//free optionText surfaces
	for(i=0; i<n; i++)
		SDL_FreeSurface(optionText[i]);
	//returns -1 when the user opts out of the 
	return -1;
}








/// this function accepts input from the mouse and prints the inventory!
/// this function does it all!
// mClicked is a 6-element array that holds information about mouse clicks.
// [0] is ignored
// [1] is left click
// [2] is middle click
// [3] is right click
// [4] is scroll up
// [5] is scroll down
//inventoryState determines whether the inventory is in or out.
//invi is the inventory index. it chooses what element of inventory we are selecting. -1 means there is no item selected.
//	0=in (hidden) 
//	1=out (shown)
int inventory_gui(short inventoryState, short invi, bool *mClicked, short x, short y){
	int i,j; // loop variables
	
	
	//this is the last item that was in the player.items[invi] spot. if it changes, then we need to show that a change occured.
	//this stores the hexID of the item stored in that inventory slot.
	static int lastItem = -1; // making this -1 will make sure that this function displays the name the first time around.
	
	//this keeps track of what the last invi was.
	static short changeOcurred = 0;
	
	//COLORS HERE
	static int background	= 0x9a9a9a;
	static int previewBackground= 0x6a6a6a;
	static int border = 0xb3b3b3;
	static int iconSpaceColor = 0x808080;
	
	static short borderThickness = 8; 
	static short columns = 6;
	static short iconSize = 32;
	static short previewSize = 128;
	// verticle height between the large 128x128 item preview and the rest of the inventory
	static short infoHeight  = 96;
	
	if(inventoryState == 0){ // if the inventory is not shown,
		apply_surface(SCREEN_WIDTH - 32, 0, inv_in, screen);
		//lastItem = player.items[invi].hexID;
		return invi;
	}
	
	
	//how wide is the inventory?
	short invWidth = borderThickness*2 + columns*iconSize;
	// how far from the left of the window will the item icon space begin?
	short startingWidth = SCREEN_WIDTH - columns*iconSize - borderThickness;
	// how far from the top of the window to where we start displaying the player's inventory (the inventory icons)
	short startingHeight = borderThickness*3 + previewSize + infoHeight;
	short rows = (SCREEN_HEIGHT-startingHeight)/iconSize;
	
	// general purpose rect that data will be shoved into
	SDL_Rect myRect;
	//rectangle used specifically for grabbing the item textures from the item_set_32.
	SDL_Rect itemRect;
	//the rectangle that is the size of strictly the area for the display of the contents of the inventory. this is where all the 32x32 icons get printed.
	SDL_Rect iconSpace;
	iconSpace.x = startingWidth;
	iconSpace.y = startingHeight;
	iconSpace.w = columns*iconSize;
	iconSpace.h = rows*iconSize;
	SDL_Rect nameSpace;
	nameSpace.h = sansFontSize-2;
	nameSpace.x = startingWidth + borderThickness - 6;
	nameSpace.y = iconSpace.y - nameSpace.h - 2;
	SDL_Rect previewSpace;
	previewSpace.x = SCREEN_WIDTH - previewSize - borderThickness;
	previewSpace.y = iconSpace.y - previewSize - nameSpace.h;
	previewSpace.w = previewSize;
	previewSpace.h = previewSize;
	
	
	//print inv_in button
	//apply_surface(SCREEN_WIDTH - 32 - invWidth, 0, inv_out, screen);
	
	//make border
	myRect.x = SCREEN_WIDTH - invWidth;
	myRect.y = 0;
	myRect.w = invWidth;
	myRect.h = SCREEN_HEIGHT;
	SDL_FillRect(screen, &myRect, border);
	
	//fill background
	myRect.x = SCREEN_WIDTH - invWidth + borderThickness;
	myRect.y = borderThickness;
	myRect.w = invWidth - 2*borderThickness;
	myRect.h = SCREEN_HEIGHT - 2*borderThickness;
	SDL_FillRect(screen, &myRect, background);
	
	
	//print the inventory iconSpace rectangle
	SDL_FillRect(screen, &iconSpace, iconSpaceColor);
	if(mClicked[1] || mClicked[3]){
		//if the user pressed inside the icon area
		if(within_rect(x,y,&iconSpace)){
			Mix_PlayChannel(-1, a_button_click, 0);
			myRect.w = myRect.h = iconSize;
			for(j=0; j<rows; j++){
				for(i=0; i<columns; i++){
					//find the rectangle where the item is going to be placed
					myRect.x = startingWidth  + i*iconSize;
					myRect.y = startingHeight + j*iconSize;
					//check to see if the user has pressed the item. if so, select it.
					if((mClicked[1] || mClicked[3]) && within_rect(x,y,&myRect)){
						changeOcurred = 1;
						invi = j*6 + i;
						j = rows; break; // exit loop.
					}
				}
			}
		}
	}
	else{
		changeOcurred = 0;
	}
	
	//if the item in the invi slot is different from last time, then there is a change.
	if(lastItem != player.items[invi].hexID) changeOcurred=1;
	
	
	//if there is a valid inventory index, print the darkness behind the selected item (behind invi)
	if(invi >= 0 && invi < MAX_PLAYER_ITEMS){
		//find the rectangle where the item is going to be placed
		myRect.w   = myRect.h = iconSize;
		myRect.x   = startingWidth +((invi%columns))*iconSize;
		myRect.y   = startingHeight + (invi/columns)*iconSize;
		//print the rectangle behind where the item will go
		SDL_FillRect(screen, &myRect, previewBackground - contrast);
	}
	
	
	//this prints the small icons of your inventory
	int invSpace;// invSpace keeps track of what inventory slot we are on. it goes from 0 to MAX_PLAYER_ITEMS if it can get that far.
	myRect.w = myRect.h = itemRect.w = itemRect.h = iconSize; // 32
	for(j=0, invSpace=0; j<rows; j++){
		for(i=0; i<columns; i++, invSpace++){
			if(invSpace >= MAX_PLAYER_ITEMS || invSpace >= player.isp){j=rows; break;} // exit the for loop if you have reached the end of the items
			//find correct place on the item_set_32 where the hexID item is located.
			itemRect.x = (player.items[invSpace].hexID / 0x100) * iconSize;
			itemRect.y = (player.items[invSpace].hexID % 0x100) * iconSize;
			//find the rectangle where the item is going to be placed
			myRect.x   = SCREEN_WIDTH - borderThickness +(i-6)*iconSize;
			myRect.y   = startingHeight + j*iconSize;
			//apply item texture to the screen
			apply_surface_clips(myRect.x, myRect.y, item_set_32, screen, &itemRect);
		}
	}
	
	//fill preview background (behind the 128x128 size of the selected item
	SDL_FillRect(screen, &previewSpace, previewBackground);
	
	//find the icon of the currently selected item on the 128x128 item_set. do this ONLY if there is a valid tile at player.items[invi] AND if it is selected.
	if(player.items[invi].hexID != i_EOI && player.items[invi].hexID != i_SKIP && invi != -1){
		myRect.x = (player.items[invi].hexID / 0x100) * previewSize;
		myRect.y = (player.items[invi].hexID % 0x100) * previewSize;
		myRect.w = myRect.h = previewSize; // width of 128
		//print the 128x128 tile in the upper right hand corner of the inventory gui
		apply_surface_clips(previewSpace.x, previewSpace.y, item_set_128, screen, &myRect);
	}
	
	//apply item name and information only if there is an item selected
	//SDL_Color infoColor = {0x30, 0x30, 0x30};
	SDL_Color nameColor = {0x00, 0x00, 0x00};
	static SDL_Surface *nameText = NULL;
	
	if(invi >= 0 && invi < MAX_PLAYER_ITEMS && player.items[invi].hexID != i_EOI && player.items[invi].hexID != i_SKIP){
		//only re-render text if a different item has been selected.
		if(changeOcurred) nameText = TTF_RenderText_Blended(sansFont2, player.items[invi].name, nameColor);
		apply_surface(nameSpace.x, nameSpace.y, nameText, screen);
		//apply_text(startingWidth + borderThickness, borderThickness, courierFontInfo, player.items[invi].name, nameColor);
		
	}
	
	
	lastItem = player.items[invi].hexID;
	return invi;
}





// returns 0 if no string was input. returns 1 if successful
// allows the user to type in a text message up to string_length - 2. the function uses string_length number of elements in the char array.
// blanks the input_string first
int input_string( char *input_string, int string_length){
	TTF_Font *my_font = sansFont;
	SDL_Color my_color = colorBlack;
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
					if(index < string_length - 2){
						switch(event.key.keysym.sym){
						case SDLK_MINUS:
							input_string[index++] = '-';
							break;
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
						default:
							break;
						}
					}
					switch(event.key.keysym.sym){
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
		strcpy(player_name, "resources\\_character128.png");
		break;
	case 64:
		strcpy(tile_set_name, "resources\\_tile_set_64.png");
		strcpy(item_set_name, "resources\\_item_set_64.png");
		strcpy(player_name, "resources\\_character64.png");
		break;
	case 16:
		strcpy(tile_set_name, "resources\\_tile_set_16.png");
		strcpy(item_set_name, "resources\\_item_set_16.png");
		strcpy(player_name, "resources\\_character16.png");
		break;
	case 8:
		strcpy(tile_set_name, "resources\\_tile_set_8.png");
		strcpy(item_set_name, "resources\\_item_set_8.png");
		strcpy(player_name, "resources\\_character8.png");
		break;
	case 32:
	default:
		strcpy(tile_set_name, "resources\\_tile_set_32.png");
		strcpy(item_set_name, "resources\\_item_set_32.png");
		strcpy(player_name, "resources\\_character32.png");
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
	SDL_FreeSurface(playerAvatar);   // clean up (prevent memory leaks)
	playerAvatar = load_image(player_name); // load the correct player_xxx
	if(playerAvatar == NULL){ // if there was an error in loading player surface
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
