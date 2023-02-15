

//returns 1 if you can move into that tile
//returns 0 if there is something that cannot be tread on
//inputs grid-coordinates
int collision_detect(int x, int y){
	int i;
	int found_valid_block = 0;
	for(i = 0; i < MAX_TILES_PER_MAP; i++){
		if(currentMap.tiles[i].x != x) continue;
		if(currentMap.tiles[i].y != y) continue;
		if(tileAtt[ currentMap.tiles[i].type ].walkOn == 2) continue;
		if(currentMap.tiles[i].type == t_EOT) break; // break if you reach the end without hitting a
		if(tileAtt[currentMap.tiles[i].type].walkOn == 1)
			found_valid_block = 1;
		else
			return 0;
	}
	if(found_valid_block)
		return 1;
	else
		return 0;
}

/// this is the function that handles the entire in-game experience.
/// This basically is the core of the game iteself (just playing. not making maps etc...)
//  if you send new_game() a map name, it will load that map. if you don't send it a map name, it will prompt the user.
int new_game(char *mapName){
	//stop any pre-playing music
	Mix_FadeOutMusic(MUSIC_FADE_TIME);
	reset_playerVariables(&player);
	//general variable
	int i;
	// this hold which map to go to when you teleport. it holds the return value from get_portal
	struct mapPortal *nextMap;
	// these variables are for keeping track of what mouse button / key was pressed.
	int key;

	// apply box
	apply_surface(SCREEN_WIDTH/2 - 400, SCREEN_HEIGHT/2 - 50 - 50 - 50 - 50, textBox, screen);
	// print "LOAD MAP"
	apply_text(SCREEN_WIDTH/2 - 370, SCREEN_HEIGHT/2 + 10 - 50 - 50 - 50 - 47, sansFont, (char *)"PLAY GAME", brightGreen);

    if(mapName != NULL) load_map(mapName);
	else if( load_map_gui() == 0) return 0;
	//make sure the player starts off in the right place.
	player.x = currentMap.spawnx;
	player.y = currentMap.spawny;
	// these values are used to determine if the user is in the correct portion of the screen. they should be between 0 and 100
	int vertPercentage = 28, horizPercentage = 25;
	/// the first element [0] is the current value.
	///this [0] element gets incremented each cycle through the do{}while; loop that the player is holding down one of the WASD keys.
	///the second element [1] is responsible for how many itterations the do{}while; loop must go though for the play to move one tile.
	int playerMoveRate[2] = {0, player.speed};
	int playerMoved = 0; // keeps track of the user's motion. 0 = equals didn't move. 1 = moved.
	const int w=0, a=1, s=2, d=3; // used to index into the below "keys" array.
	int keys[4] = {UP, UP, UP, UP}; // this keeps track of user input to the WASD keys. use the w, a, s, and d const int variables to index into this array.
	int alt = UP;  // is the user pressing an alt key?
	int ctrl = UP; // is the user pressing a ctrl key?
	int quit = 0; // make this a 1 if you want to quit the program.
	// used to store return data from the get_tile() function.
	int overItem;
	//int mousex = 0; int mousey = 0;
	static int mouse[6][2]; // this contains the states of all the mouse buttons. it is used in checking to see if the user has pressed down a button (i.e. options, inventory, etc...)
					 // [i][0] is the current state of the i-th mouse button and [i][1] is the last state of the i-th mouse button.
	for(i = 1; i < 6; i++){ // i start this array at 1 and end at 6. those numbers correspond to the 5 mouse buttons: 1=left, 2=scrollclick, 3=left, 4=scrollup, 5=scrolldown. element [0] is ignored
		mouse[i][0] = UP; // make it so that all buttons are up by default
		mouse[i][1] = UP;
	}
	 // this can either be true or false it stores data on whether or not the mouse was just clicked.
	 // [0] is ignored
	 //[1]-[5] are left, middle, right, scroll up, and scroll down in that order
	//bool mouseClicked[6];
	//this keeps track of whether the user has the invOut pulled up or not. 0 = hide invOut. 1 = show inventory.
	bool invOut = false;
	//this is used to tell which inventory slot the user has selected. 0,1,2,3,... index into the array. -1 means that there is no inventory space selected.
	short invIndex = 0;
	//the number of columns in the player's inventory
	char columns = 6;



	if(w||a||s||d); // do nothing. this keeps the compiler quiet. to the compiler, it looks like these variables are being used now :)


    // main loop
    do{
		playerMoved = 0; // make it zero by default. it will be changed if need be.
    	//While there's an event to handle
    	while(SDL_PollEvent(&event)){
    		//If the user has Xed out the window
    		if(event.type == SDL_QUIT || quit){
				quit_game();
			}
			else if(event.type == SDL_MOUSEBUTTONDOWN){
				//mousex = event.motion.x;
				//mousey = event.motion.y;
				if(event.button.button >= 1 && event.button.button <= 5)
					mouse[event.button.button][0] = DOWN;
			}
			else if(event.type == SDL_MOUSEBUTTONUP){
				//mousex = event.motion.x;
				//mousey = event.motion.y;
				if(event.button.button >= 1 && event.button.button <= 5)
					mouse[event.button.button][0] = UP;
			}
			else if(event.type == SDL_MOUSEMOTION){
				//mousex = event.motion.x;
				//mousey = event.motion.y;
			}
			else if(event.type == SDL_KEYDOWN){
				key = event.key.keysym.sym; // copy key from the strcuture to the key variable.
				switch (key){

				case SDLK_w:
					keys[w] = DOWN;
					playerMoveRate[0] = playerMoveRate[1]; // make it max so that the next time the player tried to move, he/she moves right quick.
					break;
				case SDLK_a:
					keys[a] = DOWN;
					playerMoveRate[0] = playerMoveRate[1]; // make it max so that the next time the player tried to move, he/she moves right quick.
					break;
				case SDLK_s:
					if(ctrl == DOWN){
						//save_game(player.name);
						//Mix_PlayChannel(-1, a_button_click, 0);
					}
					else{
						keys[s] = DOWN;
						playerMoveRate[0] = playerMoveRate[1]; // make it max so that the next time the player tried to move, he/she moves right quick.
					}
					break;
				case SDLK_d:
					keys[d] = DOWN;
					playerMoveRate[0] = playerMoveRate[1]; // make it max so that the next time the player tried to move, he/she moves right quick.
					break;


				case SDLK_e:
					Mix_PlayChannel(-1, a_button_click, 0);
					// lanuch into inventory-space.
					if(inventory() == -1) quit = 1; //if inventory gets Alt+F4 or the X button, then quit.
					break;


				case SDLK_r:
					zoom(ZOOM_IN);
					break;
				case SDLK_f:
					zoom(ZOOM_OUT);
					break;


				case SDLK_UP:	//move up in the inventory
					if(invIndex >= columns) invIndex -= columns;
					break;
				case SDLK_DOWN:	//move down in the inventory
					if(invIndex <= MAX_PLAYER_ITEMS-columns-1) invIndex+=columns;
					break;
				case SDLK_LEFT:	//move left in the inventory (with wrap around)
					if(invIndex%6 != 0) //if you are selecting an inventory space NOT in the left-most column
						invIndex--; 	// move left
					else				//else
						invIndex+=5; 	// wrap around
					break;
				case SDLK_RIGHT://move right in the inventory (with wrap around)
					if(invIndex%6 != 5)	//if you are selecting an inventory space NOT in the right-most column
						invIndex++; 	// move right
					else				//else
						invIndex-=5;	//wrap around
					break;


				case SDLK_RSHIFT: // both right shift and left shift do the same thing.
				case SDLK_LSHIFT: // thus, they are combined into one case statement
					//shift = DOWN;
					break;
				case SDLK_LALT:
				case SDLK_RALT:
					alt = DOWN;
					break;
				case SDLK_RCTRL:
				case SDLK_LCTRL:
					ctrl = DOWN;
					break;
				case SDLK_ESCAPE:
					return 0; // return (exit gameply)
					break;
				case SDLK_F4:
					if(alt == DOWN) quit = 1;
					break;
				}
			}
			else if(event.type == SDL_KEYUP){
				key = event.key.keysym.sym; // copy key from the strcuture to the key variable.
				switch(key){
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
					help("gameplay.txt");
					break;
				case SDLK_RSHIFT:
				case SDLK_LSHIFT:
					//shift = UP;
					break;
				case SDLK_RALT:
				case SDLK_LALT:
					alt = UP;
					break;
				case SDLK_RCTRL:
				case SDLK_LCTRL:
					ctrl = UP;
					break;
				default:
					break;
				}

    		}


    	} // while (&event)


    	//handles player movement
    	if(keys[w] == DOWN || keys[a] == DOWN || keys[s] == DOWN || keys[d] == DOWN){
			playerMoveRate[0]++; // increment the count
			if(playerMoveRate[0] >= playerMoveRate[1]){
				playerMoveRate[0] = 0; //reset the count.
				if(keys[w] == DOWN) // w
					if( collision_detect(player.x, player.y-1) ){
						player.y--;
						playerMoved = 1;
					}
				if(keys[a] == DOWN) // a
					if( collision_detect(player.x-1, player.y) ){
						player.x--;
						playerMoved = 1;
					}
				if(keys[s] == DOWN) // s
					if( collision_detect(player.x, player.y+1) ){
						player.y++;
						playerMoved = 1;
					}
				if(keys[d] == DOWN) // d
					if( collision_detect(player.x+1, player.y) ){
						player.x++;
						playerMoved = 1;
					}
				//Mix_PlayChannel(-1, a_footstep, 0);
			}
		}

		//handles the camera
    	//player too far up
		if( ( 100 * TILE_SIZE * (player.y + 0.5 - cameraPos[1]) ) / SCREEN_HEIGHT < vertPercentage ) // if the character is in the upper <vertPercentage>% of the screen,
			cameraPos[1]--; // camera pans up
		//player too far left
		if( ( 100 * TILE_SIZE * (player.x + 0.5 - cameraPos[0]) ) / (SCREEN_WIDTH - invOut*208)  < horizPercentage ) // if the character is in the left <horizPercentage>% of the screen,
			cameraPos[0]--; // camera pans left
		//player too far down
		if( ( 100 * TILE_SIZE * (player.y + 0.5 - cameraPos[1] ) ) / SCREEN_HEIGHT > 100 - vertPercentage ) // if the character is in the lower <vertPercentage>% of the screen,
			cameraPos[1]++; // camera pans down
		//player too far right
		if( ( 100 * TILE_SIZE * (player.x + 0.5 - cameraPos[0]) ) / (SCREEN_WIDTH - invOut*208) > 100 - horizPercentage ) // if the character is in the right <horizPercentage>% of the screen,
			cameraPos[0]++; // camera pans right


    	//check for portals
    	if(playerMoved && get_tile(player.x, player.y) == t_portal_green){
			nextMap = get_portal(player.x, player.y);
			if(nextMap != NULL){
				//PlaySound("resources\\sounds\\_teleport.wav", NULL, SND_ASYNC);
				Mix_PlayChannel(-1, a_teleport, 0);
				teleport(nextMap->newCoor[0],nextMap->newCoor[1], nextMap->nextMapName);
			}
		}

		//check if there is a item
		if(playerMoved){
			overItem = get_item( player.x, player.y );
			if( overItem != -1 && overItem != i_EOI && overItem != i_SKIP ){
				if( add_item(overItem) ){
					remove_item(player.x, player.y);
					Mix_PlayChannel(-1, a_button_click, 0);
				}
			}
		}



    	// print map with blanking and player.
		update_map(1); // update with blanking the screen and displaying the character

    	for(i = 1; i < 6; i++){
			mouse[i][1] = mouse[i][0]; // previous mouse state equals the current one
    	}

    	if(SDL_Flip( screen ) == -1) handle_error(0, NULL);

    }while(1); // end do{}while(1)

    return 0; // stop playing
}





