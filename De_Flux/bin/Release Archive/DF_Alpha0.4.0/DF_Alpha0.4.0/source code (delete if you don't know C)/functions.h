int handle_error(int, char *);

bool init(){
	//Initialize all subsystems
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ){
		return false;
	}
	
	//Initialize SDL_ttf
	if( TTF_Init() == -1 ){
		exit(10);
	}
	
	
	//Set up the screen
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
	
	//If there was an error setting up the screen
	if(screen == NULL ) {
		return false;
	}
	
	//Set the window caption
	SDL_WM_SetCaption( "De_Flux Aplha0.4.0", NULL );
	
	
	//blank the map
	blank_map();
	
	
	
	//If everything initialized fine
	return true;
}

// there may be just a feeeew dragons here. I encounted some at one point. I don't know how I fended them off :-x


bool load_files(){
	
	//load the "font" font
	courierFont = TTF_OpenFont("resources\\FreeMonoBold.ttf", textSize);
	if(courierFont == NULL) handle_error(1, (char *)"resources\\FreeMonoBold.ttf");
	//load the "sansFont" font
	sansFont = TTF_OpenFont("resources\\FreeSans.ttf", sansFontSize);
	if(sansFont == NULL) handle_error(1, (char *)"resources\\FreeSans.ttf");
	
	sansFont2 = TTF_OpenFont("resources\\FreeSans.ttf", sansFont2Size);
	if(sansFont2 == NULL) handle_error(1, (char *)"resources\\FreeSans.ttf");
	
	// splash screen
	splash = load_image("resources\\_DF3.png");
	//  title screen
	title_image = load_image("resources\\_De_Flux_Alpha0.4_transparent.png");
	
	
	//Load the tile set
	tile_set = load_image( (char *) "resources\\_tile_set_32.png" );
	
	//Load the item set
	item_set = load_image( (char *) "resources\\_item_set_32.png" );
	
	//Load the tile set for the inventory
	tile_set_inventory = load_image( (char *) "resources\\_tile_set_32.png" );
	
	//Load the item set for the inventory
	item_set_inventory = load_image( (char *) "resources\\_item_set_32.png" );
	
	inventory_background = load_image( (char *) "resources\\_inventoryBackground32x32.png" );
	
	inventory_border = load_image( (char *) "resources\\_inventoryBorder8x8.png" );
	
	//Load the textbox image
	textBox = load_image( (char *) "resources\\_textBox.png" );
	
	//Load the greenButton
	blueButtonOver = load_image( (char *) "resources\\buttons\\_blueButtonOver256x48.png" );
	//Load the greenButton
	blueButtonUp = load_image( (char *) "resources\\buttons\\_blueButtonUp256x48.png" );
	//Load the greenButton
	blueButtonDown = load_image( (char *) "resources\\buttons\\_blueButtonDown256x48.png" );

	//Load the whiteButton
	whiteButton = load_image( (char *) "resources\\buttons\\_whiteButton128x48.png" );
		
	//Load the whiteBlueButton
	whiteBlueButton = load_image( (char *) "resources\\buttons\\_whiteBlueButton64x48.png" );
		
	//Load the blueGlintIvy96x32
	blueGlintIvy96x32 = load_image( (char *) "resources\\buttons\\_blueGlintIvy96x32.png" );
	
	//Load the blueGlintIvy128x48
	blueGlintIvy128x48 = load_image( (char *) "resources\\buttons\\_blueGlintIvy128x48.png" );
		
	
	
	
	// load the icon
	icon = load_image( (char *) "resources\\_DF3.png" );
	//if(icon != NULL)
		//SDL_WM_SetIcon(icon, NULL); // set it as the icon if it was loaded.
	
	//load character.
	player = load_image( (char *)"resources\\_Davu32.png");
		
	// 512 x 512 of black. because I can.
	black512 = load_image( (char *)   "resources\\_black512.png" );
	
	
	
	//If everthing loaded fine
	return true;
}




/*
there has been an error! oh noes!
0: error in flipping the screen

if you enter a 10, it is a generic error with the title "Error" and the body of the error bessage is just the input string.

*/
int handle_error(int input, char *input_string){
	PlaySound("resources\\sounds\\_error.wav", NULL, SND_ASYNC);
	char main_message[512], title_message[128];
	// if exit == 1, the program will exit after the message box.
	// if exit == 0, the program continues with execution after the error message box.
	int hault = 0, ret_val = 404, box_ret_val;
	int box_type = MB_OK;

	// general error message
	if      (input == 10){
		strcpy(main_message, input_string);
		strcpy(title_message, "Error");
	}
	else if (input == 0){ // couldn't flip screen.
		strcpy(main_message, "Dungeon Crawler cannot update the screen.");
		strcpy(title_message, "Generic Graphics Error");
		ret_val = 100;
	}
	else if(input == 1){ // missing a specific file
		strcpy(main_message, "Missing File:\n\t");
		strcat(main_message, input_string);
		strcpy(title_message, "Missing File");
		ret_val = 101;
	}
	else if(input == 2){ // missing one or more files
		strcpy(main_message, "Dungeon Crawler is missing one or more files.\nDownload a new copy.");
		strcpy(title_message, "Missing One Or More Files");
		ret_val = 102;
	}
	else if(input == 3){ // overwrite saved map?
		strcpy(main_message, "Are you sure you want to overwrite\n\t");
		strcat(main_message, input_string);
		strcpy(title_message, "Overwrite?");
		box_type = MB_YESNOCANCEL;
	}
	else if(input == 4){ // can't create file
		strcpy(main_message, "cannot create map:\n\t");
		strcat(main_message, input_string);
		strcpy(title_message, "Error creating map");
	}
	else if(input == 5){ // can't load file
		strcpy(main_message, "cannot load map:\n\t");
		strcat(main_message, input_string);
		strcpy(title_message, "Map Load Error");
		box_type = MB_RETRYCANCEL;
	}
	else if(input == 6){
		strcpy(main_message, "Save before leaving the map?");
		strcpy(title_message, "SAVE?");
		box_type = MB_YESNOCANCEL;
	}
	else{
		strcpy(main_message, "I just don't know what went wrong!");
		strcpy(title_message, "Unknown Error Has Occured!");
	}
	
	box_ret_val = MessageBox(
		NULL,
		main_message,
		title_message,
		box_type
	);
	// exit the program if this specific error handling requires it.
	if(hault)
		exit(ret_val);
	// if the program was not meant to stop, return the value returned from the message box.
	return box_ret_val;
}




void clean_up(){
	SDL_FreeSurface( text);
	SDL_FreeSurface( screen   		);
	SDL_FreeSurface( tile_set 		);
	SDL_FreeSurface( item_set 		);
	SDL_FreeSurface( player   		);
	
	SDL_FreeSurface( grid512		);
	SDL_FreeSurface( black512 		);
	SDL_FreeSurface( title_image		);
	SDL_FreeSurface( icon );
	SDL_FreeSurface( splash );
	
	SDL_FreeSurface( blueButtonOver	);
	SDL_FreeSurface( blueButtonUp );
	SDL_FreeSurface( blueButtonDown );

	SDL_FreeSurface( whiteButton );
	
	SDL_FreeSurface( msg );
	SDL_FreeSurface( textBox );
	
	un_init_buttons();
	
	//SDL_FreeSurface(  );
	
	//Quit SDL
	SDL_Quit();
}



void quit_game(){
	clean_up();
	exit(0);
}
