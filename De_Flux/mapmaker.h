
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
	//
	mapMakerInventoryTiles[1][0] = t_dirt;
	mapMakerInventoryTiles[1][1] = t_stone;
	mapMakerInventoryTiles[1][2] = t_studded;
	//boxes & chests
	mapMakerInventoryTiles[1][3] = t_chestClosed;
	mapMakerInventoryTiles[1][4] = t_chestOpenEmpty;
	mapMakerInventoryTiles[1][5] = t_chestOpenGold;
	mapMakerInventoryTiles[1][6] = t_box_closed;
	mapMakerInventoryTiles[1][7] = t_box_opened;
	// quarter tiles
	mapMakerInventoryTiles[2][0] = t_studded_up_right;
	mapMakerInventoryTiles[2][1] = t_studded_down_right;
	mapMakerInventoryTiles[2][2] = t_studded_down_left;
	mapMakerInventoryTiles[2][3] = t_studded_up_left;
	mapMakerInventoryTiles[2][4] = t_stone_up_right;
	mapMakerInventoryTiles[2][5] = t_stone_down_right;
	mapMakerInventoryTiles[2][6] = t_stone_down_left;
	mapMakerInventoryTiles[2][7] = t_stone_up_left;
	//bridges and bridge posts
	mapMakerInventoryTiles[3][0] = t_bridgePostsRight;
	mapMakerInventoryTiles[3][1] = t_bridgeHoriz;
	mapMakerInventoryTiles[3][2] = t_bridgePostsLeft;
	mapMakerInventoryTiles[3][3] = t_bridgePostsUp;
	mapMakerInventoryTiles[3][4] = t_bridgeVert;
	mapMakerInventoryTiles[3][5] = t_bridgePostsDown;
	mapMakerInventoryTiles[3][6] = t_bridgePostsMiddleHoriz;
	mapMakerInventoryTiles[3][7] = t_bridgePostsMiddleVert;
	//wood stuffs
	mapMakerInventoryTiles[5][1] = t_wood;
	mapMakerInventoryTiles[5][0] = t_wood_left;
	mapMakerInventoryTiles[5][2] = t_wood_right;
	mapMakerInventoryTiles[4][1] = t_wood_top;
	mapMakerInventoryTiles[4][0] = t_wood_left_top;
	mapMakerInventoryTiles[4][2] = t_wood_right_top;
	mapMakerInventoryTiles[6][1] = t_wood_bottom;
	mapMakerInventoryTiles[6][0] = t_wood_left_bottom;
	mapMakerInventoryTiles[6][2] = t_wood_right_bottom;

	mapMakerInventoryTiles[5][4] = t_darkbrick;
	mapMakerInventoryTiles[5][3] = t_darkbrick_left;
	mapMakerInventoryTiles[5][5] = t_darkbrick_right;
	mapMakerInventoryTiles[4][4] = t_darkbrick_top;
	mapMakerInventoryTiles[4][3] = t_darkbrick_left_top;
	mapMakerInventoryTiles[4][5] = t_darkbrick_right_top;
	mapMakerInventoryTiles[6][4] = t_darkbrick_bottom;
	mapMakerInventoryTiles[6][3] = t_darkbrick_left_bottom;
	mapMakerInventoryTiles[6][5] = t_darkbrick_right_bottom;



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
	mapMakerInventoryItems[0][5] = i_cereal_bawx;
	mapMakerInventoryItems[0][6] = i_laptop_SWAG;
	mapMakerInventoryItems[0][7] = i_laptop_twilight;

	//GAK
	mapMakerInventoryItems[1][0] = i_GAK_blue;
	mapMakerInventoryItems[1][1] = i_GAK_orange;
	mapMakerInventoryItems[1][2] = i_GAK_green;
	mapMakerInventoryItems[1][3] = i_GAK_yellow;
	mapMakerInventoryItems[1][4] = i_GAK_pink;

	//computer parts
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

	mapMakerInventoryItems[2][7] = i_stun_gun;


}

/**
inputs the x and y coordinates of the mouse and the current tile.
*/
int get_inventory(int x, int y, int objectType, int inventoryType, int *objectTileItem){

	//calibrate the x and y coordinates
	x -= SCREEN_WIDTH - ( INVENTORY_TILE_SIZE * INVENTORY_WIDTH ) - 16;
	y -= 32 + 8;
	// get the x and y components in terms of coordinates on the inventory grid.
	x /= 32;
	y /= 32;

	//user clicked outside the valid inventory area
	if(x < 0 || y < 0 || x >= INVENTORY_TILE_SIZE*INVENTORY_WIDTH || y >= INVENTORY_TILE_SIZE*INVENTORY_HEIGHT){
		return objectType;
	}

	// tiles
	if(inventoryType == 0){
		//if the tile is not and EOT or a SKIP, return new tile type. otherwise, return the same tile type.
		if( mapMakerInventoryTiles[y][x] != t_EOT && mapMakerInventoryTiles[y][x] != t_SKIP ){
			*objectTileItem = 0; // set object type to tile
			return mapMakerInventoryTiles[y][x];
		}
	}
	// items
	else if(inventoryType == 1){
		if(mapMakerInventoryItems[y][x] != i_SKIP || mapMakerInventoryItems[y][x] != i_EOI || mapMakerInventoryItems[y][x] != i_UNKNOWN ){ // if the item is valid
			*objectTileItem = 1; // set object type to item
			return mapMakerInventoryItems[y][x];
		}

	}

	//if inventoryType was invalid or if the user didn't click on a valid item, return what the user started with.
	return objectType;
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
	Mix_FadeInMusic(m_Learn_by_Doing, -1, MUSIC_FADE_TIME);
	//keeps track of if the user wants to quit (like if the user presses Alt + F4)
	int quit = 0;
	//this tell if the inventory is open or not. -1 = not open, 0 = tiles open, 1 = items open
	int inventoryOpen = -1;
	// this tells us if the user is holding a tile or an item. 0 = tile; 1 = item
	int objectTileItem = 0;
	//this holds what tile type does the user have selected
	int objectType = t_dirt;
	int i; // whore variable
	cameraPos[0] = cameraPos[1] = 0;
	const int NUMBER_OF_KEYS_TO_WATCH = 4;
	//define constant values for the keys. now i can use w, a, s, and d to index into my keys array.
	const int w = 0, a = 1, s = 2, d = 3;
	// keys[w][0] = the UP/DOWN value for the w key, keys[w][1] is the duration the w key has been down
	int keys[NUMBER_OF_KEYS_TO_WATCH]; keys[0] = UP; keys[1] = UP; keys[2] = UP; keys[3] = UP;
	// this holds data on whether the player wants to save data or not
	int save_the_map;
	// this hold data to whether the user want to clear the map
	int clear_the_map;
	//this keeps track of whether or not the user has edited anything yet.
	//edited is incremented if the map has been edited.
	//therefore, do not check for if(edited==1), instead check for if(edited) because that will detect all non-zero states.
	int edited = 0;
	// this holds the string version of currentMap.tsp so that it can be printed to the screen.
	char element_char[10];
	// used for displaying information about the current tile the mous is hovering over
	char xyString[2][10];
	// this holds which mouse button was pressed //[0][0] and [0][1] are ignored. we start at [1][0] and go up from there.
	int mouse[6][2]; // mouse[1][0] == left mouse button's current state, mouse[1][1] = left mouse button's previous state
	for(i = 1; i < 6; i++){
		mouse[i][0] = UP;
		mouse[i][1] = UP;
	}
	//cordinates of where the mouse is. x[0] = current mouse position, x[1] = the last mouse position
	int x[2] = {0,0}; int y[2] = {0,0};
	//has the camera moved since last time through the input-display loop?
	int cameraMoved = 0;
	//these are used as short hand for a much longer expression.
	int adjx=0, adjy=0;
	//these variables tells you whether shift, alt, and/or ctrl are currently pressed down
	bool shift=false, alt=false, ctrl=false;
	if(shift||alt||ctrl); // keeps the compiler quiet.
	//max size for the history struct array
	#define MAX_HISTORY 100000

    //history stuct to hold data about mouse clicks/movements for ctr z feature
	struct History {
    //object type is used to destingush between items, tiles, and other things
    //tiles = 0
    //itmes = 1
    //portals = 2
    //spawn point = 3
    //background = 4
	short objectType;
	//the tile/item value
	int objectValue;
	//x and y cord data
	int x,y;

	}History[MAX_HISTORY];

	//used to add items into the history array
	int num_tiles_edited = 0;

	// nice fresh map on mapmaker startup
	map_erase(&currentMap);
	zoom(32);
	//set the spawn point of this map (will most likely be edited later in mapmaker by the user)
	currentMap.spawnx = ( SCREEN_WIDTH / TILE_SIZE )  / 2;
	currentMap.spawny = ( SCREEN_HEIGHT / TILE_SIZE ) / 2;
	//reset camera position x and y
	cameraPos[0] = cameraPos[1] = 0;

	/// this is the core of mapmaker.
    do{
		//While there's an event to handle
    	while( SDL_PollEvent(&event) ){
    		//If the user has Xed out the window
    		if(event.type == SDL_QUIT || quit){
				// quit mapmaker
				if(edited == 0) quit_game(); // if the player didn't change anything in the map maker, just quit.

				while(1){
					save_the_map = handle_error(6, NULL);

					if(save_the_map == IDYES){
						if( save_map_gui() == 1 ) // if the map saved
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
					mouse[1][0] = DOWN;
					break;
				case 2: // middle click
					objectType = get_tile(x[0] / TILE_SIZE + cameraPos[0], y[0] / TILE_SIZE + cameraPos[1]);
					mouse[2][0] = DOWN;
					break;
				case 3: // right click
					mouse[3][0] = DOWN;
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
					mouse[1][0] = UP;
					break;
				case 2:
					mouse[2][0] = UP;
					break;
				case 3:
					mouse[3][0] = UP;
					x[1] = y[1] = -100000000; // this is to make sure that the user can right click, release the button, and right click again and remove the same tile/item
											 // the value negative one hundred million is chosen because it is an arbitrarily large number.
					break;
				case 4:
					break;
				case 5:
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
						if( save_map_gui())
							edited = 0; // the map has not been edited IF you saved properly.
					}
					else{
						keys[s] = DOWN;
					}
					break;
				case SDLK_d:
					keys[d] = DOWN;
					break;
				case SDLK_l:
					if(event.key.keysym.mod & KMOD_CTRL){ //LOAD A MAP
						if(edited){ // if the user edited the map, ask if they would like to save
							while(1){
								save_the_map = handle_error(6, NULL);
								if(save_the_map == IDYES){ // wants to save game
									if( save_map_gui() ){
										load_map_gui();
										break;
									}
								}
								else if(save_the_map == IDNO){
									load_map_gui();
									break;
								}
								else if(save_the_map == IDCANCEL) break; // just forget loading the map in this case
							}// while(1)
						}//if(edited)
						else{ // if the didn't change anything, don't bother them
							load_map_gui();
							edited = 0; // the map has not been edited! you just loaded it!
						}
					}
					break;
				case SDLK_e:
					Mix_PlayChannel(-1, a_button_click, 0);
					if(inventoryOpen == -1) // if the tiles inventory isn't open
						inventoryOpen = 0; // open the tiles
					else
						inventoryOpen = -1;
					break;
				case SDLK_r:
					Mix_PlayChannel(-1, a_button_click, 0);
					zoom(ZOOM_IN);
					break;
				case SDLK_f:
					Mix_PlayChannel(-1, a_button_click, 0);
					zoom(ZOOM_OUT);
					break;
				case SDLK_ESCAPE:
					//Save before leaving mapmaker?
					if(edited){
							save_the_map = handle_error(6, NULL); // "would you like to save the map?"
							if(save_the_map == IDYES){ // 			= yes:		save game
								if(save_map_gui()) return 0;
							}
							else if(save_the_map == IDNO){ // 		= no:		just exit
								return 0;
							}
							else if(save_the_map == IDCANCEL)// 			= cancel:	don't do anything
								break; // exit while loop
					}
					else return 0; // user didn't edit anything
					break;
				case SDLK_q:
					Mix_PlayChannel(-1, a_button_click, 0);
					objectTileItem = 1;
					objectType = get_item(x[0] / TILE_SIZE + cameraPos[0], y[0] / TILE_SIZE + cameraPos[1]);
					if(objectType == i_EOI || objectType == i_SKIP || objectType == -1){
						objectTileItem = 0;
						objectType = get_tile(x[0] / TILE_SIZE + cameraPos[0], y[0] / TILE_SIZE + cameraPos[1]);
					}
					break;
				case SDLK_LSHIFT: // combined cases for
				case SDLK_RSHIFT: // left and right shitf keys
					shift = 1;
					break;
				case SDLK_RCTRL:
				case SDLK_LCTRL:
					ctrl = 1;
					break;
				case SDLK_RALT:
				case SDLK_LALT:
					alt = 1;
					break;
				case SDLK_F4:
					if( alt ) // Alt + F4
						quit = 1;
					break;
                case SDLK_t: // test the map
                    save_map("temp"); // put the map into "maps\temp.map"
                    new_game("temp"); // play "maps\temp.map"
                    Mix_FadeInMusic(m_Learn_by_Doing, -1, MUSIC_FADE_TIME); // start music again
                    load_map("temp"); // reload the temp.map
                    DeleteFile("maps//temp.map"); // delete the temp map file.
                    break;
                case SDLK_DELETE:
					//clear the screen?
					if(edited){
							clear_the_map = handle_error(7, NULL); // "would you like to clear the map?"
							if(clear_the_map == IDOK){ // 			= yes:		clear screen
								map_erase(&currentMap);
								edited = false;
							}
							else if(clear_the_map == IDCANCEL)// 			= cancel:	don't do anything
								break; // exit while loop
					}
					else return 0; // user didn't edit anything
                    break;
                case SDLK_z:
                    if(event.key.keysym.mod & KMOD_CTRL){
                        for(i = (num_tiles_edited - 2); i >= 0; i--) {
                            num_tiles_edited--;  //decrements the var so that you can add more information to it
                            if(History[i].objectType == -1)  //checks for the flag
                                break;  //exits the loop after hiting the flag so that it doesnt remove any more tiles
                            else if(History[i].objectType == 0)  //checks if it is a tile
                                remove_tile(History[i].x, History[i].y);  //deletes tiles
                            else if(History[i].objectType == 1)  //checks if it is a item
                                remove_item(History[i].x, History[i].y);  //deletes items
                            else if(History[i].objectType == 2)  //checks if it is a portal
                                portal_erase_at_coords(&currentMap, History[i].x, History[i].y);  //delete the portal
                            else if(History[i].objectType == 3) {  //checks if it the spawn point
                                currentMap.spawnx = History[i].x;  //sets spawn point to previous x cord
                                currentMap.spawny = History[i].y;  //sets spawn point to previous y cord
                            }
                            else if(History[i].objectType == 4)  //checks if is the background
                                currentMap.defaultTile = History[i].objectValue;  //sets background to previous background
                            }
                        }
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
					Mix_PlayChannel(-1, a_button_click, 0);
					help("map_maker_environment.txt");
					break;
				case SDLK_RSHIFT:
				case SDLK_LSHIFT:
					shift = 0;
					break;
				case SDLK_RCTRL:
				case SDLK_LCTRL:
					ctrl = 0;
					break;
				case SDLK_RALT:
				case SDLK_LALT:
					alt = 0;
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
			// these are adjusted x and y coordinates to compensate for the camera and tile size.
			adjx = x[0] / TILE_SIZE + cameraPos[0];
			adjy = y[0] / TILE_SIZE + cameraPos[1];
			// this places tiles/items
			if(mouse[1][0] == DOWN){
				if(objectTileItem == 0){ // tile
					if(shift){//if shift is held
						edited += place_tile_behind(adjx,adjy,objectType);
					}
					else if(alt){ // if the user wants to change the background
						History[num_tiles_edited].objectValue = objectType;
						History[num_tiles_edited].objectType = 4;
						currentMap.defaultTile = objectType;
                        if(num_tiles_edited < MAX_HISTORY)
                            num_tiles_edited++;
						edited = 1;
					}
					else{ // if shift is not held, place the tile normally
						//checks if the tile has been edited or not
						if(place_tile(adjx, adjy, objectType) == 1) {
                            edited++;
                            History[num_tiles_edited].x = adjx;
                            History[num_tiles_edited].y = adjy;
                            History[num_tiles_edited].objectType = 0;
                            if(num_tiles_edited < MAX_HISTORY)
                                num_tiles_edited++;
						}
						//checks if the spawn has been edited or not
						else if(place_tile(adjx, adjy, objectType) == 2) {
                            History[num_tiles_edited].x = adjx;
                            History[num_tiles_edited].y = adjy;
                            History[num_tiles_edited].objectType = 3;
                            if(num_tiles_edited < MAX_HISTORY)
                                num_tiles_edited++;
						}
                        //checks if the portal has been edited or not
						else if(objectType == t_portal_green && edited){
							portal_menu(adjx, adjy);
                            History[num_tiles_edited].x = adjx;
                            History[num_tiles_edited].y = adjy;
                            History[num_tiles_edited].objectType = 2;
                            if(num_tiles_edited < MAX_HISTORY)
                                num_tiles_edited++;

							mouse[1][0] = UP;
							mouse[1][1] = DOWN;
						}
					}
				}
				else if(objectTileItem == 1){ // item
					if(shift) // if the user has shift held
						edited += place_item_behind(adjx,adjy,objectType);
					else{	  // otherwise
					    //checks if the item has been edited or not
                        if(place_item(adjx, adjy, objectType) == 1) {
                            edited++;
                            History[num_tiles_edited].x = adjx;
                            History[num_tiles_edited].y = adjy;
                            History[num_tiles_edited].objectType = 1;
                            if(num_tiles_edited < MAX_HISTORY)
                                num_tiles_edited++;
						}
					}

					if(edited){ // handles placing the item in a box if it is above one.
						check_box_for_item(adjx, adjy);
					}
				}
			}

            if(mouse[1][0] == UP && mouse[1][1] == DOWN) { // if mouse pressed then released
                History[num_tiles_edited].objectType = -1;  //adds a "flag" into the history
                if(num_tiles_edited < MAX_HISTORY)
                    num_tiles_edited++;
            }

			/// this removes objects
			if(mouse[3][0] == DOWN){ // if the right mouse is down
				if(alt){
					currentMap.defaultTile = t_EOT;
					edited = 1;
				}
				if( get_item(adjx, adjy) != -1 ){
					if(x[0]/TILE_SIZE != x[1]/TILE_SIZE || y[0]/TILE_SIZE != y[1]/TILE_SIZE || cameraMoved){
						remove_item(adjx, adjy);
					}
				}
				else if( get_tile(adjx, adjy) != -1 ){
					if(x[0]/TILE_SIZE != x[1]/TILE_SIZE || y[0]/TILE_SIZE != y[1]/TILE_SIZE || cameraMoved){
						if(get_tile(adjx, adjy) == t_portal_green){
							Mix_PlayChannel(-1, a_button_click, 0);
							portal_erase_at_coords(&currentMap, adjx, adjy); // if the user tries to delete a map, delete the map data as well.
						}
						remove_tile(adjx, adjy);
					}
				}
				x[1] = x[0];
				y[1] = y[0];
				cameraMoved = 0;
			}

			update_map(0);

			// here we display the user's selected tile/item under the cursor
			if(objectTileItem == 0){ // tile
				if(objectType != t_EOT || objectType != t_SKIP) // if the tile is valid
					apply_tile_coor( objectType, x[0] - TILE_SIZE/2, y[0] - TILE_SIZE/2); // display the tile under the cursor
			}
			if(objectTileItem == 1){ // item
				if(objectType != i_EOI || objectType != i_SKIP || objectType != i_UNKNOWN) // if the item is valid
					apply_item_coor( objectType, x[0] - TILE_SIZE/2, y[0] - TILE_SIZE/2); // display the item under the cursor
			}

		}
		else{
			update_map(0);
		}

		
		


		char outputString[100];

		//apply the tile stack pointer
		strcpy(outputString, "tsp=");
		itoa(currentMap.tsp, element_char, 10);
		strcat(outputString, element_char);
		text = TTF_RenderText_Blended(sansFont2, outputString, colorLightBlue);
		apply_surface(3, -5, text, screen);
		SDL_FreeSurface(text);   // clean up (prevent memory leaks)

		//apply the item stack pointer
		strcpy(outputString, "isp=");
		itoa(currentMap.isp, element_char, 10);
		strcat(outputString, element_char);
		text = TTF_RenderText_Blended(sansFont2, outputString, colorLightBlue);
		apply_surface(3, 18 - 5, text, screen);
		SDL_FreeSurface(text);   // clean up (prevent memory leaks)

		//apply the mouse coordinates x
		itoa(x[0] / TILE_SIZE + cameraPos[0], xyString[1], 10);
		strcpy(xyString[0], "x=");
		strcat(xyString[0], xyString[1]);
		text = TTF_RenderText_Blended(sansFont2, xyString[0], colorLightBlue);
		apply_surface(95 + 3, -5, text, screen);
		SDL_FreeSurface(text);   // clean up (prevent memory leaks)
		//apply the mouse coordinates y
		itoa(y[0] / TILE_SIZE + cameraPos[1], xyString[1], 10);
		strcpy(xyString[0], "y=");
		strcat(xyString[0], xyString[1]);
		text = TTF_RenderText_Blended(sansFont2, xyString[0], colorLightBlue);
		apply_surface(95 + 3, 18 - 5, text, screen);
		SDL_FreeSurface(text);   // clean up (prevent memory leaks)

		switch ( render_buttons(x[0], y[0], mouse[1][1], mouse[1][0], &mapMakerButtons) ){
		case-1: // no buttons pressed
			break;
		case 0: // clicked the "tiles" button
			if(inventoryOpen != 0) // if the tiles inventory isn't open
				inventoryOpen = 0; // open the tiles
			else
				inventoryOpen = -1;
			break;
		case 1:	// user clicked inside the inventory
			objectType = get_inventory(x[0], y[0], objectType ,inventoryOpen, &objectTileItem);
			break;
		case 2: // clicked on the "items" button
			if(inventoryOpen != 1)
				inventoryOpen = 1;
			else
				inventoryOpen = -1;
			break;
		default:
			handle_error(10, "Error in function:\n\t render_buttons(x[0], y[0], mouse[1][1], mouse[1][0], &mapMakerButtons)");
			break;
		}
		if(inventoryOpen != -1) display_inventory(x[0], y[0], 1, inventoryOpen); // display the inventory

		if(SDL_Flip( screen ) == -1) handle_error(0, NULL);
		SDL_FreeSurface(screen);   // clean up (prevent memory leaks)
		mouse[1][1] = mouse[1][0]; // previous state = current state (only for left mouse button)
		//Sleep(10); // if there isn't any event, take a short rest
	} while( 1 ); // end do{}


	// this is here so the compiler doesn't complain. I don't think the program ever gets here... i could be wrong...
	return 0;
}

