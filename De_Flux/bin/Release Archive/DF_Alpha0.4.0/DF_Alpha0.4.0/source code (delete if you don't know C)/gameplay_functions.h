

//returns 1 if you can move into that tile
//returns 0 if there is something that cannot be tread on
int collision_detect(int x, int y){
	int i;
	int found_valid_block = 0;
	for(i = 0; i < MAX_TILES_PER_MAP; i++){
		if(currentMap.tiles[i].x != x) continue;
		if(currentMap.tiles[i].y != y) continue;
		if(currentMap.tiles[i].type == t_EOT) break; // break if you reach the end without hitting a 
		if(tileAtt[currentMap.tiles[i].type].walkOn)
			found_valid_block = 1;
		else
			return 0;
		
		
	}
	if(found_valid_block)
		return 1;
	else
		return 0;
}



int new_game(){
	// this hold which map to go to when you teleport. it holds the return value from get_portal
	struct mapPortal *nextMap;
	// these variables are for keeping track of what mouse button / key was pressed.
	int key, mouse;
	// apply box
	apply_surface(SCREEN_WIDTH/2 - 400, SCREEN_HEIGHT/2 - 50 - 50 - 50 - 50, textBox, screen);
	// print "LOAD MAP"
	apply_text(SCREEN_WIDTH/2 - 370, SCREEN_HEIGHT/2 + 10 - 50 - 50 - 50 - 47, sansFont, (char *)"PLAY GAME", brightGreen);
	
	//int shift = UP;
	if( load_map(NULL) == 0) return 0;
	//make sure the player starts off in the right place.
	playerPosition[0] = currentMap.spawnx;
	playerPosition[1] = currentMap.spawny;
	// these values are used to determine if the user is in the correct portion of the screen. they should be between 0 and 100
	int vertPercentage = 28, horizPercentage = 25;
	/// the first element [0] is the current value.
	///this [0] element gets incremented each cycle through the do{}while; loop that the player is holding down one of the WASD keys.
	///the second element [1] is responsible for how many itterations the do{}while; loop must go though for the play to move one tile.
	int playerMoveRate[2] = {0, 8};
	int playerMoved = 0;
	const int w=0, a=1, s=2, d=3; // used to index into the below "keys" array.
	int keys[4] = {UP, UP, UP, UP}; // this keeps track of user input to the WASD keys. use the w, a, s, and d const int variables to index into this array.
	
	if(w||a||s||d); // do nothing. this keeps the compiler quiet. to the compiler, it looks like these variables are being used now :)
	
	
    // main loop
    do{
    	//While there's an event to handle
    	while(SDL_PollEvent(&event)){
    		//If the user has Xed out the window
    		if(event.type == SDL_QUIT){
				quit_game();
			}
			else if(event.type == SDL_MOUSEBUTTONDOWN){
				mouse = event.button.button;
				switch(mouse){
				case 1: // left mouse button
					break;
				case 2: // scroll button
					break;
				case 3: // left click
					break;
				case 4: // scroll up
					break;
				case 5: // scroll down
					break;
				}
			}
			else if(event.type == SDL_KEYDOWN){
				key = event.key.keysym.sym; // copy key from the strcuture to the key variable.
				switch (key){
				case SDLK_w:
					keys[w] = DOWN;
					break;
				case SDLK_a:
					keys[a] = DOWN;
					break;
				case SDLK_s:
					keys[s] = DOWN;
					break;
				case SDLK_d:
					keys[d] = DOWN;
					break;
				case SDLK_r:
					zoom(ZOOM_IN);
					break;
				case SDLK_f:
					zoom(ZOOM_OUT);
					break;
				case SDLK_RSHIFT: // both right shift and left shift do the same thing.
				case SDLK_LSHIFT: // thus, they are combined into one case statement
					//shift = DOWN;
					break;
				case SDLK_ESCAPE:
					return 0; // return (exit gameply)
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
					PlaySound("resources\\sounds\\_button_click.wav", NULL, SND_ASYNC);
					system("resources\\help_files\\gameplay.txt");
					break;	
				case SDLK_RSHIFT:
				case SDLK_LSHIFT:
					//shift = UP;
					break;
				}
			
    		}
    	
    	
			
    	} // while (&event)
    	
    	if(keys[w] == DOWN || keys[a] == DOWN || keys[s] == DOWN || keys[d] == DOWN){
			playerMoved = 1;
			playerMoveRate[0]++; // increment the count
			if(playerMoveRate[0] >= playerMoveRate[1]){
				playerMoveRate[0] = 0; //reset the count.
				if(keys[w] == DOWN) // w
					if( collision_detect(playerPosition[0], playerPosition[1]-1) )
						playerPosition[1]--;
				if(keys[a] == DOWN) // a
					if( collision_detect(playerPosition[0]-1, playerPosition[1]) )
						playerPosition[0]--;
				if(keys[s] == DOWN) // s
					if( collision_detect(playerPosition[0], playerPosition[1]+1) )
						playerPosition[1]++;
				if(keys[d] == DOWN) // d
					if( collision_detect(playerPosition[0]+1, playerPosition[1]) )
						playerPosition[0]++;
			}
		}
		else{
			playerMoveRate[0] = playerMoveRate[1]; // make it max so that the next time the player tried to move, he/she moves right quick.
		}
    	
	//handles the camera
    	//player too far up
		if( ( 100 * TILE_SIZE * (playerPosition[1] + 0.5 - cameraPos[1]) ) / SCREEN_HEIGHT < vertPercentage ) // if the character is in the upper <vertPercentage>% of the screen,
			cameraPos[1]--; // camera pans up
		//player too far left
		if( ( 100 * TILE_SIZE * (playerPosition[0] + 0.5 - cameraPos[0]) ) / SCREEN_WIDTH < horizPercentage ) // if the character is in the left <horizPercentage>% of the screen,
			cameraPos[0]--; // camera pans left
		//player too far down
		if( ( 100 * TILE_SIZE * (playerPosition[1] + 0.5 - cameraPos[1] ) ) / SCREEN_HEIGHT > 100 - vertPercentage ) // if the character is in the lower <vertPercentage>% of the screen,
			cameraPos[1]++; // camera pans down
		//player too far right
		if( ( 100 * TILE_SIZE * (playerPosition[0] + 0.5 - cameraPos[0]) ) / SCREEN_WIDTH > 100 - vertPercentage ) // if the character is in the right <horizPercentage>% of the screen,
			cameraPos[0]++; // camera pans right
		
		
		//print map
		update_map(1,1); // update with blanking the screen and displaying the character
		if(SDL_Flip( screen ) == -1) handle_error(0, NULL);
    	
    	
    	
    	//check for portals
    	if(playerMoved && get_tile(playerPosition[0], playerPosition[1]) == t_portal_green){
				nextMap = get_portal(playerPosition[0], playerPosition[1]);
				if(nextMap != NULL){
						PlaySound("resources\\sounds\\_button_click.wav", NULL, SND_ASYNC);
						teleport(nextMap->newCoor[0],nextMap->newCoor[1], nextMap->nextMapName);
				}
		}
    	playerMoved = 0; // make it zero everytime
    }while(1); // end do{}
    
    return 0;
}





