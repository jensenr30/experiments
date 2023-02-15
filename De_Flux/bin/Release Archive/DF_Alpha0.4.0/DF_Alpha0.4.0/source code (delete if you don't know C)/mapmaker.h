
int options( void ); // necessary function prototype

/**
important note about mapMakerInventoryTiles!!
this array is indexed into like this:
	- mapMakerInventoryTiles[y][x]
which is the opposite of my convetion of this:
	- mapMakerInventoryTiles[x][y]
**/
int mapMakerInventoryTiles[MAX_NUMBER_OF_TILES / INVENTORY_WIDTH][INVENTORY_WIDTH];
int mapMakerInventoryItems[MAX_NUMBER_OF_ITEMS / INVENTORY_WIDTH][INVENTORY_WIDTH];

/// this sets up the mapmaker inventory for both tiles and items
void init_map_maker_inventory(){
	
	int x, y;
	
	///tiles
	//initialize all inventory spots to t_EOT
	for(y = 0; y < MAX_NUMBER_OF_TILES / INVENTORY_WIDTH; y++){
		for(x = 0; x < INVENTORY_WIDTH; x++){
			mapMakerInventoryTiles[y][x] = t_EOT;
		}
	}
	//mapMakerInventoryTiles[][] = t_;
	
	mapMakerInventoryTiles[0][0] = t_SPAWN;
	mapMakerInventoryTiles[0][6] = t_portal_green;
	mapMakerInventoryTiles[0][7] = t_portal_red;
	
	mapMakerInventoryTiles[1][0] = t_dirt;
	mapMakerInventoryTiles[1][1] = t_stone;
	mapMakerInventoryTiles[1][2] = t_studded;
	mapMakerInventoryTiles[1][6] = t_box_closed;
	mapMakerInventoryTiles[1][7] = t_box_opened;
	
	mapMakerInventoryTiles[2][0] = t_studded_up_right;
	mapMakerInventoryTiles[2][1] = t_studded_down_right;
	mapMakerInventoryTiles[2][2] = t_studded_down_left;
	mapMakerInventoryTiles[2][3] = t_studded_up_left;
	mapMakerInventoryTiles[2][4] = t_stone_up_right;
	mapMakerInventoryTiles[2][5] = t_stone_down_right;
	mapMakerInventoryTiles[2][6] = t_stone_down_left;
	mapMakerInventoryTiles[2][7] = t_stone_up_left;
	
	
	
	///items
	//initialize all inventory spots to t_EOT
	for(y = 0; y < MAX_NUMBER_OF_ITEMS / INVENTORY_WIDTH; y++){
		for(x = 0; x < INVENTORY_WIDTH; x++){
			mapMakerInventoryItems[y][x] = i_EOI;
		}
	}
	//mapMakerInventoryItems[][] = i_;
	
	mapMakerInventoryItems[0][0] = i_scroll;
	mapMakerInventoryItems[0][1] = i_bananas;
	mapMakerInventoryItems[0][6] = i_laptop_SWAG;
	mapMakerInventoryItems[0][7] = i_laptop_twilight;
	
	
	mapMakerInventoryItems[1][0] = i_GAK_blue;
	mapMakerInventoryItems[1][1] = i_GAK_orange;
	mapMakerInventoryItems[1][2] = i_GAK_green;
	mapMakerInventoryItems[1][3] = i_GAK_yellow;
	mapMakerInventoryItems[1][4] = i_GAK_pink;
	
	
	mapMakerInventoryItems[2][0] = i_computer_tower;
	mapMakerInventoryItems[2][1] = i_computer_monitor;
	mapMakerInventoryItems[2][2] = i_computer_keyboard;
	mapMakerInventoryItems[2][3] = i_computer_mouse;
	mapMakerInventoryItems[2][4] = i_computer_power_cable;
	mapMakerInventoryItems[2][5] = i_computer_SATA_cable;
	
	mapMakerInventoryItems[3][0] = i_computer_motherboard;
	mapMakerInventoryItems[3][1] = i_computer_processor;
	mapMakerInventoryItems[3][2] = i_computer_RAM;
	mapMakerInventoryItems[3][3] = i_computer_power_supply;
	mapMakerInventoryItems[3][4] = i_computer_hard_drive;
	mapMakerInventoryItems[3][5] = i_computer_DVD_drive;
	
	
}

/**
inputs the x and y coordinates of the mouse and the current tile.
*/
int get_inventory(int x, int y, int objectValue, int inventoryType, int *objectType){
	
	//calibrate the x and y coordinates
	x -= SCREEN_WIDTH - ( INVENTORY_TILE_SIZE * INVENTORY_WIDTH ) - 16;
	y -= 32 + 8;
	// get the x and y components in terms of coordinates on the inventory grid.
	x /= 32;
	y /= 32;
	
	//user clicked outside the valid inventory area
	if(x < 0 || y < 0 || x >= INVENTORY_TILE_SIZE*INVENTORY_WIDTH || y >= INVENTORY_TILE_SIZE*INVENTORY_HEIGHT){
		return objectValue;
	}
	
	// tiles
	if(inventoryType == 0){
		//if the tile is not and EOT or a SKIP, return new tile type. otherwise, return the same tile type.
		if( mapMakerInventoryTiles[y][x] != t_EOT && mapMakerInventoryTiles[y][x] != t_SKIP ){
			*objectType = 0; // set object type to tile
			return mapMakerInventoryTiles[y][x];
		}
	}
	// items
	else if(inventoryType == 1){
		if(mapMakerInventoryItems[y][x] != i_SKIP || mapMakerInventoryItems[y][x] != i_EOI || mapMakerInventoryItems[y][x] != i_UNKNOWN ){ // if the item is valid
			*objectType = 1; // set object type to item
			return mapMakerInventoryItems[y][x];
		}
			
	}
	
	//if inventoryType was invalid or if the user didn't click on a valid item, return what the user started with.
	return objectValue;
}
/**
inventory_state is either a 1 or a 0.
	0 = gameplay inventory
	1 = mapmaker inventory
inventory_type  is either a 1 or a 0.
	0 = tiles
	1 = items
*/
void display_inventory(int x, int y, int inventory_state, int inventory_type){
	
	int posx = SCREEN_WIDTH - ( INVENTORY_TILE_SIZE * INVENTORY_WIDTH ) - 16;
	int posy = 32 + 8;
	int i; int j;
	//display verticle border pieces
	for(j = 32; j < (INVENTORY_HEIGHT+1)*32 + 16; j += 8){
		apply_surface( posx - 8, j, inventory_border, screen );
		apply_surface( posx + 32*INVENTORY_WIDTH, j, inventory_border, screen );
	}
	//display horizontal border pieces
	for(i = 0; i < INVENTORY_WIDTH*32; i += 8){
		apply_surface( i + posx, posy - 8, inventory_border, screen);
		apply_surface( i + posx, posy + INVENTORY_HEIGHT*32, inventory_border, screen);
	}
	
	
	///tiles
	if(inventory_type == 0){
		for(j = 0; j < INVENTORY_HEIGHT; j++){
			for(i = 0; i < INVENTORY_WIDTH; i++){
				apply_surface(posx + i*INVENTORY_TILE_SIZE, posy + j*INVENTORY_TILE_SIZE, inventory_background, screen); // apply the background
				if(mapMakerInventoryTiles[j][i] != t_EOT)
					apply_tile_coor_inventory( mapMakerInventoryTiles[j][i], posx + i*INVENTORY_TILE_SIZE, posy + j*INVENTORY_TILE_SIZE );
			}
		}
	}
	///items
	else if(inventory_type == 1){
		for(j = 0; j < INVENTORY_HEIGHT; j++){
			for(i = 0; i < INVENTORY_WIDTH; i++){
				apply_surface(posx + i*INVENTORY_TILE_SIZE, posy + j*INVENTORY_TILE_SIZE, inventory_background, screen); // apply the background
				if(mapMakerInventoryItems[j][i] != i_EOI)
					apply_item_coor_inventory( mapMakerInventoryItems[j][i], posx + i*INVENTORY_TILE_SIZE, posy + j*INVENTORY_TILE_SIZE );
			}
		}
	}
	
	
	return;
}




int map_maker_environment()
{
	//this tell if the inventory is open or not. -1 = not open, 0 = tiles open, 1 = items open
	int inventoryOpen = -1;
	// this tells us if the user is holding a tile or an item. 0 = tile; 1 = item
	int objectType = 0;
	//this holds what tile type does the user have selected
	int objectValue = 0x0100;
	int i; // whore variable
	cameraPos[0] = cameraPos[1] = 0;
	const int NUMBER_OF_KEYS_TO_WATCH = 4;
	//define constant values for the keys. now i can use w, a, s, and d to index into my keys array.
	const int w = 0, a = 1, s = 2, d = 3;
	// keys[w][0] = the UP/DOWN value for the w key, keys[w][1] is the duration the w key has been down
	int keys[NUMBER_OF_KEYS_TO_WATCH]; keys[0] = UP; keys[1] = UP; keys[2] = UP; keys[3] = UP;
	// this holds data on whether the player wants to save data or not
	int save_the_map;
	//this keeps track of whether or not the user has edited anything yet.
	int edited = 0;
	// this holds the string version of currentMap.tsp so that it can be printed to the screen.
	char element_char[10];
	// used for displaying information about the current tile the mous is hovering over
	char xyString[2][10];
	// this holds which mouse button was pressed
	int mouse[5][2]; // mouse[0][0] == left mouse button's current state, mouse[0][1] = left mouse button's previous state
	for(i = 0; i < 5; i++){
		mouse[i][0] = UP;
		mouse[i][1] = UP;
	}
	//cordinates of where the mouse is. x[0] = current mouse position, x[1] = the last mouse position
	int x[2] = {0,0}; int y[2] = {0,0};
	//this is where the return value from the get_tile() function.
	int get_tile_return_value = -1;
	//this is where the return value from the get_item() function.
	int get_item_return_value = -1;
	// this will store return values. most noteable from the save_map() function. it makes sure that the map was ACTUALLY SAVED before leaving the map.
	int ret_val = 0;
	// records whether or not shift is being pushed down
	//int shift = 0; int ctrl = 0;
	int cameraMoved = 0;
	
	
	// nice fresh map on mapmaker startup
	blank_map();
	zoom(32);
	//set the spawn point of this map (will most likely be edited later in mapmaker by the user)
	currentMap.spawnx = ( SCREEN_WIDTH / TILE_SIZE )  / 2;
	currentMap.spawny = ( SCREEN_HEIGHT / TILE_SIZE ) / 2;
	
	/// this is the core of mapmaker.
    do{
		//While there's an event to handle
    	while( SDL_PollEvent(&event) ){
    		//If the user has Xed out the window
    		if(event.type == SDL_QUIT){
				// quit mapmaker
				if(edited == 0) quit_game(); // if the player didn't change anything in the map maker, just quit.
				
				while(1){
					save_the_map = handle_error(6, NULL);
					
					if(save_the_map == IDYES){
						if( save_map() == 1 ) // if the map saved
							quit_game();
						else
							break;
					}
					else if(save_the_map == IDNO)
						quit_game();
					else if(save_the_map == IDCANCEL)
						break;
				}
			}
			if(event.type == SDL_MOUSEBUTTONDOWN){
				x[0] = event.button.x;
				y[0] = event.button.y;
				switch( event.button.button ){
				case 1://left click
					mouse[0][0] = DOWN;
					break;
				case 2: // middle click
					objectValue = get_tile(x[0] / TILE_SIZE - cameraPos[0], y[1] / TILE_SIZE - cameraPos[1]);
					mouse[1][0] = DOWN;
					break;
				case 3: // right click
					mouse[2][0] = DOWN;
					break;
				case 4: //scroll up
					break;
				case 5: //scroll down
					break;
				default:
					break;
				}
			}
			
			else if(event.type == SDL_MOUSEBUTTONUP){
				switch(event.button.button){
				case 1:
					mouse[0][0] = UP;
					break;
				case 2:
					mouse[1][0] = UP;
					break;
				case 3:
					mouse[2][0] = UP;
					x[1] = y[1] = -100000000; // this is to make sure that the user can right click, release the button, and right click again and remove the same tile/item
											 // the value negative one hundred million is chosen because it is an arbitrarily large number.
					break;
				case 4:
					mouse[3][0] = UP;
					break;
				case 5:
					mouse[4][0] = UP;
					break;
				default:
					break;
				}
					
			}
			
			else if(event.type == SDL_MOUSEMOTION){
				x[0] = event.button.x;
				y[0] = event.button.y;
			}
			
			else if(event.type == SDL_KEYDOWN){
				switch(event.key.keysym.sym){
				case SDLK_w:
					keys[w] = DOWN;
					break;
				case SDLK_a:
					keys[a] = DOWN;
					break;
				case SDLK_s:
					if(event.key.keysym.mod & KMOD_CTRL){
						save_map();
						edited = 0; // the map has not been edited! you just loaded it!
					}
					else{
						keys[s] = DOWN;
					}
					break;
				case SDLK_d:
					keys[d] = DOWN;
					break;
				case SDLK_l:
					if(event.key.keysym.mod & KMOD_CTRL){
						if(edited){ // if the user edited the map, ask if they would like to save
							ret_val = 0; // start it out as 0 (indicating it didn't save)
							while(1){
								save_the_map = handle_error(6, NULL);
								if(save_the_map == IDYES){ // wants to save game
									if( save_map() ){
										load_map(NULL);
										break;
									}
								}
								else if(save_the_map == IDNO){
									load_map(NULL);
									break;
								}
								else if(save_the_map == IDCANCEL) break; // just forget loading the map in this case
							}// while(1)
						}//if(edited)
						else{ // if the didn't change anything, don't bother them
							load_map(NULL);
							edited = 0; // the map has not been edited! you just loaded it!
						}
					}
					break;
				case SDLK_e:
					PlaySound("resources\\sounds\\_button_click.wav", NULL, SND_ASYNC);
					if(inventoryOpen == -1) // if the tiles inventory isn't open
						inventoryOpen = 0; // open the tiles
					else
						inventoryOpen = -1;
					break;
				case SDLK_r:
					PlaySound("resources\\sounds\\_button_click.wav", NULL, SND_ASYNC);
					zoom(ZOOM_IN);
					break;
				case SDLK_f:
					PlaySound("resources\\sounds\\_button_click.wav", NULL, SND_ASYNC);
					zoom(ZOOM_OUT);
					break;
				case SDLK_ESCAPE:
					//Save before leaving mapmaker?
					if(edited){
						ret_val = 0;
						while(ret_val == 0){
							save_the_map = handle_error(6, NULL); // "would you like to save the map?"
							if(save_the_map == IDYES){ // 			= yes:		save game
								ret_val = save_map();
							}
							else if(save_the_map == IDNO){ // 		= no:		just exit
								return 0;
								
							}
							else if(save_the_map == IDCANCEL)// 			= cancel:	don't do anything
								break; // exit while loop
						}
					}
					else return 0; // user didn't edit anything
					break;
				case SDLK_q:
					PlaySound("resources\\sounds\\_button_click.wav", NULL, SND_ASYNC);
					objectType = 1;
					objectValue = get_item(x[0] / TILE_SIZE + cameraPos[0], y[0] / TILE_SIZE + cameraPos[1]);
					if(objectValue == i_EOI || objectValue == i_SKIP || objectValue == -1){
						objectType = 0;
						objectValue = get_tile(x[0] / TILE_SIZE + cameraPos[0], y[0] / TILE_SIZE + cameraPos[1]);
					}
					break;
				case SDLK_LSHIFT: // combined cases for
				case SDLK_RSHIFT: // left and right shitf keys
					//shift = 1;
					break;
				case SDLK_RCTRL:
				case SDLK_LCTRL:
					//ctrl = 1;
					break;
				default:
					break; // do nothing if any other key is pressed
				}
			}
			
			else if(event.type == SDL_KEYUP){
				switch( event.key.keysym.sym ){
				case SDLK_w:
					keys[w] = UP;
					break;
				case SDLK_a:
					keys[a] = UP;
					break;
				case SDLK_s:
					keys[s] = UP;
					break;
				case SDLK_d:
					keys[d] = UP;
					break;
				case SDLK_h:
					PlaySound("resources\\sounds\\_button_click.wav", NULL, SND_ASYNC);
					system("resources\\help_files\\map_maker_environment.txt");
					break;				
				case SDLK_RSHIFT:
				case SDLK_LSHIFT:
					//shift = 0;
					break;
				case SDLK_RCTRL:
				case SDLK_LCTRL:
					//ctrl = 0;
					break;
				default:
					break; // do nothing if any other key is pressed
				}
			}
		} // while( SDL_PollEvent(&event) == 1)
		// end checking events
		
		
		
		
		// this moves the camera
		if( keys[w] == DOWN || keys[a] == DOWN || keys[s] == DOWN || keys[d] == DOWN ){
			
			if(keys[w] == DOWN)
				cameraPos[1]--;
			if(keys[a] == DOWN)
				cameraPos[0]--;
			if(keys[s] == DOWN)
				cameraPos[1]++;
			if(keys[d] == DOWN)
				cameraPos[0]++;
			cameraMoved = 1;
		}
		
		
		
		//only add new tiles or delete old ones if the cursor isn't on a button
		i = over_button(x[0], y[0], &mapMakerButtons);
		if( i == -1 || (inventoryOpen == -1 && i == 2) ){
			
			// this places tiles
			if(mouse[0][0] == DOWN){
				if(objectType == 0){ // tile
					get_tile_return_value = get_tile(x[0] / TILE_SIZE + cameraPos[0], y[0] / TILE_SIZE + cameraPos[1]);
					if( objectValue != get_tile_return_value && objectValue != t_EOT && objectValue != t_SKIP ){
						if(objectValue == t_SPAWN){ // place the spawn point
							currentMap.spawnx = x[0] / TILE_SIZE + cameraPos[0];
							currentMap.spawny = y[0] / TILE_SIZE + cameraPos[1];
							edited = 1;
						}
						else{ // place a tile normally
						//place a tile is different from what is already there.
						currentMap.tiles[currentMap.tsp].x = x[0] / TILE_SIZE + cameraPos[0];
						currentMap.tiles[currentMap.tsp].y = y[0] / TILE_SIZE + cameraPos[1];
						currentMap.tiles[currentMap.tsp].type = objectValue;
						//increase the tile stack pointer
						currentMap.tsp++;
						edited = 1;
						if(objectValue == t_portal_green){
							portal_menu( x[0] / TILE_SIZE + cameraPos[0], y[0] / TILE_SIZE + cameraPos[1]);
							mouse[0][0] = UP;
						}
						}
					}
				}
				else if(objectType == 1){ // item
					get_item_return_value = get_item(x[0] / TILE_SIZE + cameraPos[0], y[0] / TILE_SIZE + cameraPos[1]);
					if( objectValue != get_item_return_value && objectValue != i_EOI && objectValue != i_SKIP && objectValue != i_UNKNOWN ){
						//PlaySound("resources\\sounds\\_button_click.wav", NULL, SND_ASYNC);
						//place a tile is different from what is already there.
						currentMap.items[currentMap.isp].x = x[0] / TILE_SIZE + cameraPos[0];
						currentMap.items[currentMap.isp].y = y[0] / TILE_SIZE + cameraPos[1];
						currentMap.items[currentMap.isp].type = objectValue;
						//increase the tile stack pointer
						currentMap.isp++;
						edited = 1;
					}
				}
			}
			
			
			/// this removes objects
			if(mouse[2][0] == DOWN){ // if the mouse is down
				if( get_item(x[0] / TILE_SIZE + cameraPos[0], y[0] / TILE_SIZE + cameraPos[1]) != -1 ){
					if(x[0]/TILE_SIZE != x[1]/TILE_SIZE || y[0]/TILE_SIZE != y[1]/TILE_SIZE || cameraMoved){
						remove_item(x[0]/TILE_SIZE + cameraPos[0], y[0]/TILE_SIZE + cameraPos[1]);
					}
				}
				else if( get_tile(x[0] / TILE_SIZE + cameraPos[0], y[0] / TILE_SIZE + cameraPos[1]) != -1 ){
					if(x[0]/TILE_SIZE != x[1]/TILE_SIZE || y[0]/TILE_SIZE != y[1]/TILE_SIZE || cameraMoved){
						remove_tile(x[0]/TILE_SIZE + cameraPos[0], y[0]/TILE_SIZE + cameraPos[1]);
					}
				}
				x[1] = x[0];
				y[1] = y[0];
				cameraMoved = 0;
			}
			
			//blank dat screen.
			blank_screen();
			update_map(0,0); // update the map without blanking first and without displaying the character.
			
			// here we display the user's selected tile/item under the cursor
			if(objectType == 0){ // tile
				if(objectValue != t_EOT || objectValue != t_SKIP) // if the tile is valid
					apply_tile_coor( objectValue, x[0] - TILE_SIZE/2, y[0] - TILE_SIZE/2); // display the tile under the cursor
			}
			if(objectType == 1){ // item
				if(objectValue != i_EOI || objectValue != i_SKIP || objectValue != i_UNKNOWN) // if the item is valid
					apply_item_coor( objectValue, x[0] - TILE_SIZE/2, y[0] - TILE_SIZE/2); // display the item under the cursor
			}
			
		}
		else{
			blank_screen();
			update_map(0,0);
		}
		
		char outputString[100];
		
		//apply the tile stack pointer
		strcpy(outputString, "tsp=");
		itoa(currentMap.tsp, element_char, 10);
		strcat(outputString, element_char);
		text = TTF_RenderText_Blended(sansFont2, outputString, colorLightBlue);
		apply_surface(b_mmOptions.pos.w + b_mmOptions.pos.x + 3, -5, text, screen);
		SDL_FreeSurface(text);   // clean up (prevent memory leaks)
		
		//apply the item stack pointer
		strcpy(outputString, "isp=");
		itoa(currentMap.isp, element_char, 10);
		strcat(outputString, element_char);
		text = TTF_RenderText_Blended(sansFont2, outputString, colorLightBlue);
		apply_surface(b_mmOptions.pos.w + b_mmOptions.pos.x + 3, 18 - 5, text, screen);
		SDL_FreeSurface(text);   // clean up (prevent memory leaks)
		
		//apply the mouse coordinates x
		itoa(x[0] / TILE_SIZE + cameraPos[0], xyString[1], 10);
		strcpy(xyString[0], "x=");
		strcat(xyString[0], xyString[1]);
		text = TTF_RenderText_Blended(sansFont2, xyString[0], colorLightBlue);
		apply_surface(b_mmOptions.pos.w + b_mmOptions.pos.x + 95 + 3, -5, text, screen);
		SDL_FreeSurface(text);   // clean up (prevent memory leaks)
		//apply the mouse coordinates y
		itoa(y[0] / TILE_SIZE + cameraPos[1], xyString[1], 10);
		strcpy(xyString[0], "y=");
		strcat(xyString[0], xyString[1]);
		text = TTF_RenderText_Blended(sansFont2, xyString[0], colorLightBlue);
		apply_surface(b_mmOptions.pos.w + b_mmOptions.pos.x + 95 + 3, 18 - 5, text, screen);
		SDL_FreeSurface(text);   // clean up (prevent memory leaks)
		
		switch ( render_buttons(x[0], y[0], mouse[0][1], mouse[0][0], &mapMakerButtons) ){
		case-1: // no buttons pressed
			break;
		case 0: // clicked the "options" button
			options();
			break;
		case 1: // clicked the "tiles" button
			if(inventoryOpen != 0) // if the tiles inventory isn't open
				inventoryOpen = 0; // open the tiles
			else
				inventoryOpen = -1;
			break;
		case 2:	// user clicked inside the inventory
			objectValue = get_inventory(x[0], y[0], objectValue ,inventoryOpen, &objectType);
			break;
		case 3: // clicked on the "items" button
			if(inventoryOpen != 1)
				inventoryOpen = 1;
			else
				inventoryOpen = -1;
			break;
		default:
			handle_error(10, "Error in function:\n\trender_buttons(x[0], y[0], mouse[0][1], mouse[0][0], &mapMakerButtons)");
			break;
		}
		if(inventoryOpen != -1) display_inventory(x[0], y[0], 1, inventoryOpen); // display the inventory
		
		if(SDL_Flip( screen ) == -1) handle_error(0, NULL);
		SDL_FreeSurface(screen);   // clean up (prevent memory leaks)
		mouse[0][1] = mouse[0][0]; // previous state = current state (only for left mouse button)
		//Sleep(10); // if there isn't any event, take a short rest
	} while( 1 ); // end do{}
	
	
	// this is here so the compiler doesn't complain. I don't think the program ever gets here... i could be wrong...
	return 0;
}

