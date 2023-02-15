
/**
this function can be used to defrag one map:
	simply enter two pointers to the same map.
also, it can be used to copy maps:
	simply put the source map in the first argument, and the destination map in the second. like so:
	defrag_map( &source_map, &destination_map );
there you go! you now know everything there is to know about the defrag_map function!
p.s. defragType can be 0-4
0 = defrag tiles
1 = defrag items
2 = defrag tiles and items
3 = defrag maps
4 = defrag everything
*/
void defrag_map(int defragType, struct map *mapfrom, struct map *mapto){
	unsigned short indexFrom, indexTo;
	unsigned short objectValue;

	//defrag tiles
	if(defragType == 0 || defragType == 2 || defragType == 4){ // tiles
		indexFrom = 0;
		indexTo = 0;
		for(; indexFrom < MAX_TILES_PER_MAP; indexFrom++){
			objectValue = mapfrom->tiles[indexFrom].type;
			if(objectValue == t_SKIP) continue;
			// stop coying if you reach the end of the map
			else if(objectValue == t_EOT) break;

			//if all is well, copy data from one map to the other.
			mapto->tiles[indexTo].x = mapfrom->tiles[indexFrom].x;
			mapto->tiles[indexTo].y = mapfrom->tiles[indexFrom].y;
			mapto->tiles[indexTo].type = mapfrom->tiles[indexFrom].type;

			// move on to the next tile element in mapto
			indexTo++;
		}
		// make sure you end the map!
		mapto->tiles[indexTo].type = t_EOT;
		mapto->tsp = indexTo;
	}

	//defrag items
	if(defragType == 1 || defragType == 2 || defragType == 4){ // items
		indexFrom = 0;
		indexTo = 0;
		for(; indexFrom < MAX_ITEMS_PER_MAP; indexFrom++){
			objectValue = mapfrom->items[indexFrom].type;
			if(objectValue == i_SKIP) continue;
			// stop coying if you reach the end of the map
			else if(objectValue == i_EOI) break;

			//if all is well, copy data from one map to the other.
			mapto->items[indexTo].x = mapfrom->items[indexFrom].x;
			mapto->items[indexTo].y = mapfrom->items[indexFrom].y;
			mapto->items[indexTo].type = mapfrom->items[indexFrom].type;

			// move on to the next tile element in mapto
			indexTo++;
		}
		// make sure you end the map!
		mapto->items[indexTo].type = i_EOI;
		mapto->isp = indexTo;
	}

	//defrag maps
	if(defragType == 3 || defragType == 4){
		indexFrom = 0;
		indexTo =   0;
		for(; indexFrom < MAX_PORTALS_PER_MAP; indexFrom++){
			//if the portal valid?
			if(mapfrom->portals[indexFrom].nextMapName[0] != '\0'){
				//copy the portal over
				portal_copy(&mapfrom->portals[indexFrom], &mapto->portals[indexTo]);
				indexTo++;
			}
		}
	}
}





/// returns 0 if the map was NOT loaded.
/// returns 1 if it saved successfully.
int save_map(char* mapName){
	//int overwrite;
	char file_name[25];
    char file_path[64];
    FILE *fp = NULL;

    if(mapName == NULL) {
		/*
	// apply box
	apply_surface(SCREEN_WIDTH/2 - 400, SCREEN_HEIGHT/2 - 50 - 50 - 50, textBox, screen);
	// print "SAVE MAP
	apply_text(SCREEN_WIDTH/2 - 370, SCREEN_HEIGHT/2 + 10 - 50 - 50 - 50, sansFont, (char *)"SAVE MAP", brightGreen);
	// apply box
	apply_surface(SCREEN_WIDTH/2 - 400, SCREEN_HEIGHT/2 - 50 - 50, textBox, screen);
	//print text
	apply_text(SCREEN_WIDTH/2 - 370, SCREEN_HEIGHT/2 + 10 - 50 - 50, sansFont, (char *)"the .map extention will be added to your file", colorBlack);

	int ret_val = input_string(file_name, 25);
	if(ret_val == 0) return 0; // didn't save map
	strcpy(file_path, "maps\\");
	strcat(file_path, file_name);
	strcat(file_path, ".map");
	FILE *fp = fopen(file_path, "r");
	if(fp != NULL){
		overwrite = handle_error(3, file_name);
		//if the user doesn't want to overwrite the file, then try inputting the name again.
		if(overwrite == IDNO){
			save_map(NULL);
			return 0; // didn't save map
		}
		else if(overwrite == IDCANCEL){
			fclose(fp);
			return 0; // stop trying to save map. didn't save map
		}
	}
	fclose(fp);
	*/
		return 0;
    }
    else if(strchr(mapName, '\\' ) != NULL){
        strcat(file_path, mapName);
    }
    else {
        strcpy(file_path, "maps\\");
        strcat(file_path, mapName);
        strcat(file_path, ".map");
    }

	//at this point we know the user either wants to overwrite the file, or it doesn't exist yet.
	// in either case, we get to write the file!
	fp = fopen(file_path, "w");
	if(fp == NULL){
		fclose(fp);
		//handle_error(4, file_path);
		return 0; // stop trying to save the map
	}
	//at this point we know we can write the map data!

	//write the portal data
	int i;
	for(i = 0; i < MAX_PORTALS_PER_MAP; i++){
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

	//print the defaultTile
	fprintf(fp, "defaultTile = %x\n", currentMap.defaultTile);

    //if(mapName == NULL) Mix_PlayChannel(-1, a_find, 0); // sucess! saved the map!
	fclose(fp);
	//add the map's name on the the end of the window title.
	set_window_title(file_name);

	return 1;
}




/// returns 1 if map was loaded
/// returns 0 if it couldn't load the map.
/// If you send this function a string, it will try to load that map. It will try to access "maps\<inputName>.map"
/// If you send this function a NULL string, it will prompt the user to type in the name of a saved map in the "maps\" directory.
int load_map(char *inputName){
	static char error_message[128];
	char path[MAX_MAP_NAME_LENGTH + 50];
	char manualName[MAX_MAP_NAME_LENGTH];
	FILE *fp = NULL;
	//set to true if input name is a full file path eg
	//C:/
    //bool fullFilePath;

	if(inputName == NULL){
        /*
		// apply box
		apply_surface(SCREEN_WIDTH/2 - 400, SCREEN_HEIGHT/2 - 50 - 50 - 50, textBox, screen);
		// print "LOAD MAP"
		apply_text(SCREEN_WIDTH/2 - 370, SCREEN_HEIGHT/2 + 10 - 50 - 50 - 50, sansFont, (char *)"LOAD MAP", brightGreen);
		// apply box
		apply_surface(SCREEN_WIDTH/2 - 400, SCREEN_HEIGHT/2 - 50 - 50, textBox, screen);
		// print "the .map..."
		apply_text(SCREEN_WIDTH/2 - 370, SCREEN_HEIGHT/2 + 10 - 50 - 50, sansFont, (char *)"the .map extention will be added to your file", colorBlack);

		//user types in a map name.
		input_string( manualName, MAX_MAP_NAME_LENGTH);

		// if there was a string input, make the name of the file be "maps\\<input_string>.map" else NULL
		if( manualName != NULL ){
			mapName = manualName; // the mapname points at the manual, user-input name.
		}
		else*/
			return 0; // couldn't open the user's map. return fail
	}
	else if(strchr(inputName, '\\' ) != NULL){
        strcat(path, inputName);
	}
	else{
		strcpy(path, "maps\\");
		strcat(path, inputName);
		strcat(path, ".map");
	}

	fp = fopen(path, "r");

	if( strcmp(path, "maps\\.map") == 0) return 0; // if the input string was empty, return 0;

	if(fp == NULL){
		strcpy(error_message, "Cannot open map:\n\t");
		strcat(error_message, path);
		handle_error(5, path);
        return 0;
	}
	// at this point, we hve sucessfully opened the file.
	map_erase(&currentMap);
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
	currentMap.psp = portals; // advance the map stack pointer to reflect how many portals there are on the map.

	// check if there are too many portals in this map
	if(portals > MAX_PORTALS_PER_MAP){
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

	//input the spawn coordinates
	fscanf(fp, "spawnx = %d\n", &currentMap.spawnx );
	fscanf(fp, "spawny = %d\n", &currentMap.spawny );

	//input the defaultTile
	fscanf(fp, "defaultTile = %x\n", &currentMap.defaultTile);

	//sucess
	//close dat file
	fclose(fp);

	//set window name
	if(inputName == NULL)
		set_window_title(manualName);
	else
		set_window_title(inputName);

	return 1;
}

int save_map_gui()
{
	OPENFILENAME ofn;
	char szFileName[MAX_PATH] = "";

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFilter = "Map Files (*.map)\0*.map\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrDefExt = "map";
	ofn.lpstrInitialDir = "maps";
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR | OFN_FILEMUSTEXIST;

	if(GetSaveFileName(&ofn))
	{
	    return save_map(szFileName);
	}
	return 0;
}

int load_map_gui()
{
	OPENFILENAME ofn;
	char szFileName[MAX_PATH] = "";

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFilter = "Map Files (*.map)\0*.map\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrDefExt = "map";
	ofn.lpstrInitialDir = "maps";
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR | OFN_FILEMUSTEXIST;

	if(GetOpenFileName(&ofn))
	{
	    return load_map(szFileName);
	}
	return 0;
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


///puts a tile at map-coord (x,y)
///returns 1 if it changed anything. otherwise, returns 0.
int place_tile(x,y,type){
	if( get_tile(x,y) == type) return 0; // don't place duplicate tiles
	if( type == t_EOT || type == t_SKIP) return 0; // don't place these. that is pointless.
	if(type == t_SPAWN){
		currentMap.spawnx = x;
		currentMap.spawny = y;
		return 2; // don't try to actually place a spawn block. that is pointless.
	}
	currentMap.tiles[currentMap.tsp].x = x;
	currentMap.tiles[currentMap.tsp].y = y;
	currentMap.tiles[currentMap.tsp].type = type;
	currentMap.tsp++;
	return 1;
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


//this function places a tile beneath all other tiles on the map so far.
int place_tile_behind(int x, int y, int type){
	//don't bother if the type is stupid.
	if(type == t_EOT || type == t_SKIP) return 0;
	int i;
	static int rval[MAX_TILES_PER_MAP]; // this serves as a record of tiles removed

	//remove and store all tiles in the rval array.
	for(i=0; i<MAX_TILES_PER_MAP; i++){
		rval[i] = get_tile(x,y);
		if( rval[i]==-1 || rval[i]==t_EOT || rval[i]==t_SKIP ) break; // you have found the end of the items
		remove_tile(x,y);
	}
	place_tile(x,y,type); // place behind all others
	//replace original tiles
	for(i--; i>=0; i--){
		place_tile(x,y,rval[i]);
	}
	return 1;
}


///places item at map-coord (x,y)
///returns 1 if it changed anything. otherwise, returns 0.
int place_item(x,y,type){
	if( get_item(x,y) == type) return 0; // don't place duplicate items
	if( type == i_EOI || type == i_SKIP) return 0; // don't place these. that would be pointless.
	currentMap.items[currentMap.isp].x = x;
	currentMap.items[currentMap.isp].y = y;
	currentMap.items[currentMap.isp].type = type;
	currentMap.isp++;
	return 1;
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

int place_item_behind(int x, int y, int type){
	//don't bother if the item type is stupid.
	if(type == i_EOI || type == i_SKIP) return 0;
	int i;
	static int rval[MAX_ITEMS_PER_MAP]; // this serves as a record of items removed

	//remove and store all items in the rval array.
	for(i=0; i<MAX_ITEMS_PER_MAP; i++){
		rval[i] = get_item(x,y);
		if( rval[i]==-1 || rval[i]==i_EOI || rval[i]==i_SKIP ) break; // you have found the end of the items
		remove_item(x,y);
	}
	place_item(x,y,type); // place behind all others
	//replace original items
	for(i--; i>=0; i--){
		place_item(x,y,rval[i]);
	}
	return 1;
}



///checks to see
void check_box_for_item(int x, int y){
	int ret_item;//stores the return value of get_item.
	int ret_tile;//stores the return value of get_tile.
	//get item at (x,y)
	ret_item = get_item(x,y);
	//get tile at (x,y)
	ret_tile = get_tile(x, y);

	if(ret_item != -1 && ret_item != i_EOI && ret_item != i_SKIP){ // if there was a valid item
		//if there was a closed or open box underneath, make the a_box_open sound.
		if(ret_tile == t_box_opened || ret_tile == t_box_closed)
			Mix_PlayChannel(-1, a_box_open, 0);
		//if there was an open box underneath the item before, turn it into a closed box
		if(ret_tile == t_box_opened ){
			remove_tile(x, y); // remove the opened box
			place_tile(x, y, t_box_closed); // place a closed box in it's place
		}
	}
	else{
		//if there was a closed box underneath, make the a_box_open sound.
		if(ret_tile == t_box_closed){
			Mix_PlayChannel(-1, a_box_open, 0);
			remove_tile(x, y); // remove the opened box
			place_tile(x, y, t_box_closed); // place a closed box in it's place
		}
	}
}


///sets the portal that you send it to the default state. no name, 0's for coordinates.
void portal_erase(struct mapPortal *port){
	int j;
	 // reset portal name.
	for(j=0; j<MAX_MAP_NAME_LENGTH; j++)
		port->nextMapName[j] = '\0';
	//reset portal coordinates
	port->newCoor[0] = 0;
	port->oldCoor[0] = 0;
	port->newCoor[1] = 0;
	port->oldCoor[1] = 0;
}

void portal_copy(struct mapPortal *source, struct mapPortal *dest){
	 int j;
	 // reset portal name.
	for(j=0; j<MAX_MAP_NAME_LENGTH; j++)
		dest->nextMapName[j] = source->nextMapName[j];
	//reset portal coordinates
	dest->newCoor[0] = source->newCoor[0];
	dest->oldCoor[0] = source->oldCoor[0];
	dest->newCoor[1] = source->newCoor[1];
	dest->oldCoor[1] = source->oldCoor[1];
}


///this tries to erase the portal at the coordinates x,y on map datmap. NOT THE TILE ITSELF but the portal in the map data.
//datmap is the map with the portal that you want to erase
//x,y are the map-coordinates at which you want to remove the map.
void portal_erase_at_coords(struct map *datmap, int x, int y){
	int i;
	for(i=MAX_PORTALS_PER_MAP-1; i>=0; i--){
		if(datmap->portals[i].oldCoor[0] == x && datmap->portals[i].oldCoor[1] == y){ // if the coordinate here
			portal_erase(&datmap->portals[i]); // erase portal.
			break; // only remove the top-most portal (I'm assuming there aren't any below)
		}
	}
	//defrag portals
	defrag_map(3, &currentMap, &currentMap);
}



void map_erase(struct map *datmap){
	//set up the map
	int i, j;
	for( i = 0; i < MAX_TILES_PER_MAP; i++){
		datmap->tiles[i].type = t_EOT;
		datmap->items[i].type = i_EOI;
	}
	for(i = 0; i < MAX_PORTALS_PER_MAP; i++){
		for(j = 0; j < MAX_MAP_NAME_LENGTH; j++)
			portal_erase(&datmap->portals[i]);
	}
	datmap->tsp = 0; // no tiles
	datmap->isp = 0; // no items
	datmap->psp = 0; // no portals
	datmap->defaultTile = t_EOT;
}





int teleport( int x, int y, char *mapName ){
	load_map(mapName);
	player.x = x;
	player.y = y;

	cameraPos[0] = player.x - ( SCREEN_WIDTH / TILE_SIZE )/2;
	cameraPos[1] = player.y - ( SCREEN_HEIGHT / TILE_SIZE )/2;


	return 1;
}

/// returns a pointer to a mapPortal structure
struct mapPortal *get_portal(int x, int y){
	int i;
	for(i = 0; i < MAX_PORTALS_PER_MAP; i++){
		if(currentMap.portals[i].oldCoor[0] == x && currentMap.portals[i].oldCoor[1] == y){
			return &currentMap.portals[i];
		}
	}

	// if you didn't find a portal that mached up with this one, return NULL
	return NULL;
}




void portal_menu(int x, int y){

	currentMap.portals[currentMap.psp].oldCoor[0] = x; // old coordinates
	currentMap.portals[currentMap.psp].oldCoor[1] = y; // ''

	int ret_val;
	char myString[MAX_MAP_NAME_LENGTH];

	ret_val = MessageBox(
		NULL,
		"would you like to make this portal operational?",
		"make operational?",
		MB_YESNO | MB_TOPMOST | MB_DEFBUTTON1 | MB_ICONQUESTION
	);
	if(ret_val == IDYES){ // if the user wants to activate the portal
		apply_surface(SCREEN_WIDTH/2 - 400, SCREEN_HEIGHT/2 - 50 - 50, textBox, screen);
		apply_text(SCREEN_WIDTH/2 - 370, SCREEN_HEIGHT/2 + 10 - 50 - 50, sansFont, (char *)"Destination Map Name:", brightGreen);
		ret_val = input_string(currentMap.portals[currentMap.psp].nextMapName, MAX_MAP_NAME_LENGTH);

		if(ret_val == 1){ // user entered a valid map name
			apply_surface(SCREEN_WIDTH/2 - 400, SCREEN_HEIGHT/2 - 50 - 50, textBox, screen);
			apply_text(SCREEN_WIDTH/2 - 370, SCREEN_HEIGHT/2 + 10 - 50 - 50, sansFont, (char *)"Destination x:", brightGreen);
			ret_val = input_string(myString, MAX_MAP_NAME_LENGTH);
			currentMap.portals[currentMap.psp].newCoor[0] = atoi(myString);

			if(ret_val){ // user entered a valid x value
				apply_surface(SCREEN_WIDTH/2 - 400, SCREEN_HEIGHT/2 - 50 - 50, textBox, screen);
				apply_text(SCREEN_WIDTH/2 - 370, SCREEN_HEIGHT/2 + 10 - 50 - 50, sansFont, (char *)"Destination y:", brightGreen);
				ret_val = input_string(myString, MAX_MAP_NAME_LENGTH);
				currentMap.portals[currentMap.psp].newCoor[1] = atoi(myString);

				if(ret_val){
					currentMap.psp++; // increment the map stack pointer
					return; // sucess
				}
			}
		}


	}
	else return; // if the user doesn't want to make a portal, don't bug the user.

	//if the program failed making a portal, then alert the user.
	handle_error(10, "Didn't make portal");
}










