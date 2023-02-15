
/**
this function can be used to defrag one map:
	simply enter two pointers to the same map.
also, it can be used to copy maps:
	simply put the source map in the first argument, and the destination map in the second. like so:
	defrag_map( &source_map, &destination_map );
there you go! you now know everything there is to know about the defrag_map_v2 function!
p.s. objectType can be 0, 1, or 2.
0 = defrag tiles
1 = defrag items
2 = defrag both
*/
void defrag_map(int objectType, struct map *mapfrom, struct map *mapto){
	unsigned short indexIN, indexOUT;
	unsigned short objectValue;
	
	if(objectType == 0 || objectType == 2){ // tiles
		indexIN = 0;
		indexOUT = 0;
		for(; indexIN < MAX_TILES_PER_MAP; indexIN++){
			objectValue = mapfrom->tiles[indexIN].type;
			if(objectValue == t_SKIP) continue;
			// stop coying if you reach the end of the map
			else if(objectValue == t_EOT) break;
			
			//if all is well, copy data from one map to the other.
			mapto->tiles[indexOUT].x = mapfrom->tiles[indexIN].x;
			mapto->tiles[indexOUT].y = mapfrom->tiles[indexIN].y;
			mapto->tiles[indexOUT].type = mapfrom->tiles[indexIN].type;
			
			// move on to the next tile element in mapto
			indexOUT++;
		}
		// make sure you end the map!
		mapto->tiles[indexOUT].type = t_EOT;
		mapto->tsp = indexOUT;
	}
	
	
	if(objectType == 1 || objectType == 2){
		indexIN = 0;
		indexOUT = 0;
		for(; indexIN < MAX_ITEMS_PER_MAP; indexIN++){
			objectValue = mapfrom->items[indexIN].type;
			if(objectValue == i_SKIP) continue;
			// stop coying if you reach the end of the map
			else if(objectValue == i_EOI) break;
			
			//if all is well, copy data from one map to the other.
			mapto->items[indexOUT].x = mapfrom->items[indexIN].x;
			mapto->items[indexOUT].y = mapfrom->items[indexIN].y;
			mapto->items[indexOUT].type = mapfrom->items[indexIN].type;
			
			// move on to the next tile element in mapto
			indexOUT++;
		}
		// make sure you end the map!
		mapto->items[indexOUT].type = i_EOI;
		mapto->isp = indexOUT;
	}
}



/// returns 0 if the map was NOT loaded.
/// returns 1 if it saved successfully.
int save_map(){
	int overwrite;
	char file_name[25];
	
	
	// apply box
	apply_surface(SCREEN_WIDTH/2 - 400, SCREEN_HEIGHT/2 - 50 - 50 - 50, textBox, screen);
	// print "SAVE MAP
	apply_text(SCREEN_WIDTH/2 - 370, SCREEN_HEIGHT/2 + 10 - 50 - 50 - 50, sansFont, (char *)"SAVE MAP", brightGreen);
	// apply box
	apply_surface(SCREEN_WIDTH/2 - 400, SCREEN_HEIGHT/2 - 50 - 50, textBox, screen);
	//print text
	apply_text(SCREEN_WIDTH/2 - 370, SCREEN_HEIGHT/2 + 10 - 50 - 50, sansFont, (char *)"the .map extention will be added to your file", colorBlack);
	
	int ret_val = input_string(file_name, 25, sansFont, colorBlack);
	if(ret_val == 0) return 0; // didn't save map
	char file_path[64];
	strcpy(file_path, "maps\\");
	strcat(file_path, file_name);
	strcat(file_path, ".map");
	FILE *fp = fopen(file_path, "r");
	if(fp != NULL){
		overwrite = handle_error(3, file_name);
		//if the user doesn't want to overwrite the file, then try inputting the name again. 
		if(overwrite == IDNO){
			save_map();
			return 0; // didn't save map
		}
		else if(overwrite == IDCANCEL){
			fclose(fp);
			return 0; // stop trying to save map. didn't save map
		}
	}
	fclose(fp);
	
	
	//at this point we know the user either wants to overwrite the file, or it doesn't exist yet.
	// in either case, we get to write the file!
	fp = fopen(file_path, "w");
	if(fp == NULL){
		fclose(fp);
		handle_error(4, file_path);
		return 0; // stop trying to save the map
	}
	//at this point we know we can write the map data!
	
	//write the portal data
	int i;
	for(i = 0; i < MAX_PORTALS; i++){
		//skip non-existant maps
		if(currentMap.portals[i].nextMapName[0] == '\0') continue;
		
		fprintf(fp, "%s\n", currentMap.portals[i].nextMapName);
		fprintf(fp, "%d:%d\n", currentMap.portals[i].oldCoor[0], currentMap.portals[i].oldCoor[1]);
		fprintf(fp, "%d:%d\n", currentMap.portals[i].newCoor[0], currentMap.portals[i].newCoor[1]);
	}
	
	//print tiles
	for(i = 0; i < MAX_TILES_PER_MAP; i++){
		// if there is no tile here, move on to the next one.
		if(currentMap.tiles[i].type == t_SKIP) continue;
		// skip -- do not quit -- when you encounter an t_EOT. it is worth it to check the entire file for tiles.
		if(currentMap.tiles[i].type == t_EOT)  continue;
		// at thi point, we know there must be a tile save at location i
		fprintf(fp, "%x@%d:%d\n", currentMap.tiles[i].type, currentMap.tiles[i].x, currentMap.tiles[i].y);
	}
	//ffff@0:0 will signify the end of the tiles
	fprintf(fp, "000000@000000:000000\n");
	
	//print items
	for(i = 0; i < MAX_ITEMS_PER_MAP; i++){
		// if there is no tile here, move on to the next one.
		if(currentMap.items[i].type == i_SKIP) continue;
		// skip -- do not quit -- when you encounter an t_EOT. it is worth it to check the entire file for tiles.
		if(currentMap.items[i].type == i_EOI)  continue;
		// at thi point, we know there must be a tile save at location i
		fprintf(fp, "%x@%d:%d\n", currentMap.items[i].type, currentMap.items[i].x, currentMap.items[i].y);
	}
	//ffff@0:0 will signify the end of the items
	fprintf(fp, "000000@000000:000000\n");
	
	//print the cameraPos
	fprintf(fp, "cameraPos[0] = %d\n", cameraPos[0]);
	fprintf(fp, "cameraPos[1] = %d\n", cameraPos[1]);
	
	// print the tile_size (what zoom level you are at)
	fprintf(fp, "TILE_SIZE = %d\n", TILE_SIZE);
	
	//print the spawn coordinates
	fprintf(fp, "spawnx = %d\n", currentMap.spawnx);
	fprintf(fp, "spawny = %d\n", currentMap.spawny);
	
	//PlaySound("resources\\sounds\\_map_saved.wav", NULL, SND_ASYNC);
	fclose(fp);
	return 1;
}


/// returns 1 if map was loaded
/// returns 0 if it couldn't load the map.
int load_map(char *inputName){
	static char error_message[128];
	char path[MAX_MAP_NAME_LENGTH + 50];
	char manualName[MAX_MAP_NAME_LENGTH];
	FILE *fp = NULL;
	
	// apply box
	apply_surface(SCREEN_WIDTH/2 - 400, SCREEN_HEIGHT/2 - 50 - 50 - 50, textBox, screen);
	// print "LOAD MAP"
	apply_text(SCREEN_WIDTH/2 - 370, SCREEN_HEIGHT/2 + 10 - 50 - 50 - 50, sansFont, (char *)"LOAD MAP", brightGreen);
	// apply box
	apply_surface(SCREEN_WIDTH/2 - 400, SCREEN_HEIGHT/2 - 50 - 50, textBox, screen);
	// print "the .map..."
	apply_text(SCREEN_WIDTH/2 - 370, SCREEN_HEIGHT/2 + 10 - 50 - 50, sansFont, (char *)"the .map extention will be added to your file", colorBlack);
	
	
	if(inputName == NULL){
		
		input_string( manualName, MAX_MAP_NAME_LENGTH, sansFont, colorBlack );
		// if there was a string input, make the name of the file be "maps\\<input_string>.map" else NULL
		if( manualName != NULL ){
			strcpy(path, "maps\\");
			strcat(path, manualName);
			strcat(path, ".map");
			fp = fopen(path, "r");
		}
		else
			return 0;
	}
	else if( inputName != NULL ){
		strcpy(path, "maps\\");
		strcat(path, inputName);
		strcat(path, ".map");
		fp = fopen(path, "r");
	}
	
	if( strcmp(path, "maps\\.map") == 0) return 0; // if the input string was empty, return 0;
	
	if(fp == NULL){
		strcpy(error_message, "Cannot open map:\n\t");
		strcat(error_message, path);
		int box_ret_val = handle_error(5, path);
		
		if(box_ret_val == IDRETRY)
			return load_map(inputName);
		else
			return 0;
	}
	// at this point, we hve sucessfully opened the file.
	blank_map();
	//find which line the first tile is on
	int newlines = 0;
	char inputChar = '\0';
	while(inputChar != '@'){
		inputChar = fgetc(fp);
		if(inputChar == '\n')
			newlines++;
	}
	
	if(newlines % 3){
		//there is a number of newlines in the portal segment other than a multiple of 3.
		//that means that there is an error as every portal has 3 lines.
		strcpy(error_message, "Error in portal segment of map:\n\t");
		strcat(error_message, path);
		handle_error(10, error_message);
		return 0;
	}
	int portals = newlines / 3;
	currentMap.msp = portals; // advance the map stack pointer to reflect how many portals there are on the map.
	
	// check if there are too many portals in this map
	if(portals > MAX_PORTALS){
		strcpy(error_message, "Map contains too many portals:\n\t");
		strcat(error_message, path);
		handle_error(10, error_message);
		return 0;
	}
	
	//finally, we can be sure the text document is readable!  =D
	rewind(fp);
	
	//start reading in the portals
	int i, j;
	for(i = 0; i < portals; i++){
		for(j = 0; j < MAX_MAP_NAME_LENGTH; j++){
			inputChar = fgetc(fp);
			if( inputChar == '\n' ){
				currentMap.portals[i].nextMapName[j] = '\0';
				break;
			}
			else
				currentMap.portals[i].nextMapName[j] = inputChar;
		}
		//input x:y values
		fscanf(fp, "%d:%d\n", &currentMap.portals[i].oldCoor[0], &currentMap.portals[i].oldCoor[1]);
		fscanf(fp, "%d:%d\n", &currentMap.portals[i].newCoor[0], &currentMap.portals[i].newCoor[1]);
	}
	// read in the tiles
	for(i = 0; i < MAX_TILES_PER_MAP; i++){
		//input tile
		fscanf(fp, "%hx@%d:%d\n", &currentMap.tiles[i].type, &currentMap.tiles[i].x, &currentMap.tiles[i].y);
		//did you find the end of the tiles?
		if(currentMap.tiles[i].type == t_EOT && currentMap.tiles[i].x == 0 && currentMap.tiles[i].y == 0)
			break; // reached end of the tiles
	}
	currentMap.tsp = i;
	
	// read in the items
	for(i = 0; i < MAX_ITEMS_PER_MAP; i++){
		//input tile
		fscanf(fp, "%hx@%d:%d\n", &currentMap.items[i].type, &currentMap.items[i].x, &currentMap.items[i].y);
		//did you find the end of the items?
		if(currentMap.items[i].type == i_EOI && currentMap.items[i].x == 0 && currentMap.items[i].y == 0)
			break; // reached end of the items
	}
	currentMap.isp = i;
	
	//scan for the cameraPos
	fscanf(fp, "cameraPos[0] = %d\n", &cameraPos[0]);
	fscanf(fp, "cameraPos[1] = %d\n", &cameraPos[1]);
	
	// scan for the tile_size (what zoom level you are at)
	fscanf(fp, "TILE_SIZE = %d\n", &TILE_SIZE);
	zoom(TILE_SIZE); // zoom to the correct level.
	
	//print the spawn coordinates
	fscanf(fp, "spawnx = %d\n", &currentMap.spawnx );
	fscanf(fp, "spawny = %d\n", &currentMap.spawny );
	
	//PlaySound("resources\\sounds\\_map_loaded.wav", NULL, SND_ASYNC);
	//close dat file
	fclose(fp);
	return 1;
}




/// returns the tile type at the tile coordinate ( x,y )
int get_tile( int xcoor, int ycoor ){
	int i = currentMap.tsp-1;
	for(; i >= 0; i--){
		// don't register t_EOT or t_SKIP tiles as tiles 'real' tiles
		if(currentMap.tiles[i].type == t_EOT || currentMap.tiles[i].type == t_SKIP) continue;
		//if we find a tile at x,y, return its type.
		if( currentMap.tiles[i].x == xcoor && currentMap.tiles[i].y == ycoor )
			break;
	}
	// didn't find a match.
	if( i < 0 ) return -1;
	
	// found a match
	return currentMap.tiles[i].type;
}

/// returns the item type at the item coordinate ( x,y )
int get_item( int xcoor, int ycoor ){
	int i;
	for(i = currentMap.isp - 1; i >= 0; i--){
		// don't register t_EOT or t_SKIP items as 'real' items
		if(currentMap.items[i].type == i_EOI || currentMap.items[i].type == i_SKIP) continue;
		//if we find a item at x,y, return its type.
		if( currentMap.items[i].x == xcoor && currentMap.items[i].y == ycoor )
			break;
	}
	// didn't find a match.
	if( i < 0 ) return -1;
	
	// found a match
	return currentMap.items[i].type;
}





void blank_map(){
	//set up the map
	int i, j;
	for( i = 0; i < MAX_TILES_PER_MAP; i++){
		currentMap.tiles[i].type = t_EOT;
		currentMap.items[i].type = i_EOI;
	}
	for(i = 0; i < MAX_PORTALS; i++){
		for(j = 0; j < MAX_MAP_NAME_LENGTH; j++)
			currentMap.portals[i].nextMapName[j] = '\0';
		currentMap.portals[i].newCoor[0] = 0;
		currentMap.portals[i].oldCoor[0] = 0;
		currentMap.portals[i].newCoor[1] = 0;
		currentMap.portals[i].oldCoor[1] = 0;
		
	}
	currentMap.tsp = 0; // no tiles
	currentMap.isp = 0; // no items
	currentMap.msp = 0; // no portals
}





int teleport( int x, int y, char *mapName ){
	load_map(mapName);
	playerPosition[0] = x;
	playerPosition[1] = y;
	
	
	return 1;
}

/// returns a pointer to a mapPortal structure
struct mapPortal *get_portal(int x, int y){
	int i;
	for(i = 0; i < MAX_PORTALS; i++){
		if(currentMap.portals[i].oldCoor[0] == x && currentMap.portals[i].oldCoor[1] == y){
			return &currentMap.portals[i];
		}
	}
	
	// if you didn't find a portal that mached up with this one, return NULL
	return NULL;
}




void portal_menu(int x, int y){
	
	currentMap.portals[currentMap.msp].oldCoor[0] = x; // old coordinates
	currentMap.portals[currentMap.msp].oldCoor[1] = y; // ''
	
	int ret_val;
	char myString[MAX_MAP_NAME_LENGTH];
	
	ret_val = MessageBox(
		NULL,
		"would you like to make this portal operational?",
		"activate portal?",
		MB_YESNO | MB_TASKMODAL | MB_TOPMOST | MB_DEFBUTTON1
	);
	if(ret_val == IDYES){ // if the user wants to activate the portal
		apply_surface(SCREEN_WIDTH/2 - 400, SCREEN_HEIGHT/2 - 50 - 50, textBox, screen);
		apply_text(SCREEN_WIDTH/2 - 370, SCREEN_HEIGHT/2 + 10 - 50 - 50, sansFont, (char *)"Destination Map Name:", brightGreen);
		ret_val = input_string(currentMap.portals[currentMap.msp].nextMapName, MAX_MAP_NAME_LENGTH, sansFont, colorBlack);
		
		if(ret_val == 1){ // user entered a valid map name
			apply_surface(SCREEN_WIDTH/2 - 400, SCREEN_HEIGHT/2 - 50 - 50, textBox, screen);
			apply_text(SCREEN_WIDTH/2 - 370, SCREEN_HEIGHT/2 + 10 - 50 - 50, sansFont, (char *)"Destination x:", brightGreen);
			ret_val = input_string(myString, MAX_MAP_NAME_LENGTH, sansFont, colorBlack);
			currentMap.portals[currentMap.msp].newCoor[0] = atoi(myString);
			
			if(ret_val){ // user entered a valid x value
				apply_surface(SCREEN_WIDTH/2 - 400, SCREEN_HEIGHT/2 - 50 - 50, textBox, screen);
				apply_text(SCREEN_WIDTH/2 - 370, SCREEN_HEIGHT/2 + 10 - 50 - 50, sansFont, (char *)"Destination y:", brightGreen);
				ret_val = input_string(myString, MAX_MAP_NAME_LENGTH, sansFont, colorBlack);
				currentMap.portals[currentMap.msp].newCoor[1] = atoi(myString);
				
				if(ret_val){
					currentMap.msp++; // increment the map stack pointer
					return; // sucess
				}
			}
		}
		
		
	}
	//if the user doesn't want to make a portal
	handle_error(10, "Didn't make portal");
}






// x and y are in tile coordinates (x,y)
void remove_tile( int x, int y ){
	
	int i = currentMap.tsp;
	
	for(; i >= 0; i--){
		// if there is a tile that is in the same tilespace as where the user clicked, set it to a type t_SKIP
		
		if(currentMap.tiles[i].x == x && currentMap.tiles[i].y == y && currentMap.tiles[i].type != t_SKIP && currentMap.tiles[i].type != t_EOT){
			currentMap.tiles[i].type = t_SKIP;
			defrag_map(0, &currentMap, &currentMap);
			break;
			
		}
		
	}
}

// x and y are in item coordinates (x,y)
void remove_item( int x, int y ){
	
	int i = currentMap.isp;
	
	for(; i >= 0; i--){
		// if there is a item that is in the same tilespace as where the user clicked, set it to a type i_SKIP
		
		if(currentMap.items[i].x == x && currentMap.items[i].y == y && currentMap.items[i].type != i_EOI){
			currentMap.items[i].type = i_SKIP;
			defrag_map(1, &currentMap, &currentMap);
			break;
			
		}
		
	}
}









