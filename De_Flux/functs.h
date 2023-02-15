
void startUpScreen(){
    //set ambiance
	Mix_PlayChannel(-1, a_find, 0);
    //apply the splash screen
    apply_surface(SCREEN_WIDTH/2 - 180/2, SCREEN_HEIGHT/2 - 180/2, splash, screen);

    int i, radius = 200, steps = 20;
    double a, b;
    float pi = 3.1415;
    SDL_Rect startUpRect;
    zoom(64);
    for(i = 0; i < steps; i++){
        //startUpRect.h = 32;
        //startUpRect.w = 32;
        a = cos(  i * pi * 2 / steps );
        b = sin(  i * pi * 2 / steps );
        startUpRect.x = (SCREEN_WIDTH/2 - 30 + a * radius);
        startUpRect.y = (SCREEN_HEIGHT/2 - 30 + b * radius);
        apply_item_coor( i_GAK_blue, startUpRect.x, startUpRect.y);
        //SDL_FillRect( screen , &startUpRect , 0xffffff);
        Sleep(900/steps);
        SDL_Flip(screen);
    }

    //Sleep(200); // wait for a bit (let the user soak up the raw awesomeness that is the "DF" logo.
}

SDL_Surface *create_surface(int width, int height){
	return SDL_CreateRGBSurface(SDL_HWSURFACE, width, height, 32, 0xFF0000, 0x00FF00, 0x0000FF, 0x000000);
}


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



Mix_Chunk *load_audio( char *path ){

	Mix_Chunk *chunk = NULL;
	chunk = Mix_LoadWAV( path );

	if(chunk == NULL){
		char errorMessage[150];

		strcpy(errorMessage, "couldn't load file:\n\t");
		strcat(errorMessage, path);
		handle_error(10, errorMessage);
		return NULL;
	}
	// return a pointer to the loaded music if it was properly loaded
	return chunk;
}

Mix_Music *load_music( char *path ){

	Mix_Music *music = NULL;
	music = Mix_LoadMUS( path );

	if(music == NULL){
		char errorMessage[150];

		strcpy(errorMessage, "couldn't load file:\n\t");
		strcat(errorMessage, path);
		handle_error(10, errorMessage);
		return NULL;
	}
	// return a pointer to the loaded music if it was properly loaded
	return music;
}


//this set the title of the window to, "<WINDOW_TITLE_PREFIX> - <inputString>"
void set_window_title(char * inputString){

	char windowTitle[256];
	strcpy(windowTitle, WINDOW_TITLE_PREFIX);
	strcat(windowTitle, " - ");
	strcat(windowTitle, inputString);

	SDL_WM_SetCaption(windowTitle, NULL);
}

/*
SDL_Surface* create_surface(Uint32 flags,int width,int height){

	// 'display' is the surface whose format you want to match
	//  if this is really the display format, then use the surface returned from SDL_SetVideoMode

	//const SDL_PixelFormat fmt;
	//fmt. = screen->format;


	Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

	return SDL_CreateRGBSurface(flags, width, height, SCREEN_BPP, rmask, gmask, bmask, amask );
}
*/


void copy_rect(SDL_Rect *source, SDL_Rect *dest){
	dest->x = source->x;
	dest->y = source->y;
	dest->w = source->w;
	dest->h = source->h;
}

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

	//init music/audio
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 512) == -1){
		return false;
	}

	//Set the window caption
	SDL_WM_SetCaption( WINDOW_TITLE_PREFIX, NULL );

	//blank the map
	map_erase(&currentMap);

	//If everything initialized fine
	return true;
}

// there may be just a feeeew dragons here. I encounted some at one point. I don't know how I fended them off :-x


bool load_files(){

	//load the "courierFont" font
	courierFont = TTF_OpenFont("resources\\FreeMonoBold.ttf", courierFontSize);
	if(courierFont == NULL) handle_error(1, (char *)"resources\\FreeMonoBold.ttf");
	//load the "courierFontInfo" font
	courierFontInfo = TTF_OpenFont("resources\\FreeMonoBold.ttf", courierFontInfoSize);
	if(courierFontInfo == NULL) handle_error(1, (char *)"resources\\FreeMonoBold.ttf");
	//load the "sansFont" font
	sansFont = TTF_OpenFont("resources\\FreeSans.ttf", sansFontSize);
	if(sansFont == NULL) handle_error(1, (char *)"resources\\FreeSans.ttf");

	sansFont2 = TTF_OpenFont("resources\\FreeSans.ttf", sansFont2Size);
	if(sansFont2 == NULL) handle_error(1, (char *)"resources\\FreeSans.ttf");


	// splash screen
	splash = load_image((char*)"resources\\_DF3.png");
	pressH = load_image((char*)"resources\\pressH.png");
	//  title screen
	title_image = load_image((char*)"resources\\DF5v2.png");


	//Load the tile set
	tile_set = load_image( (char *) "resources\\_tile_set_32.png" );
	tile_set_8   = load_image( (char*) "resources\\_tile_set_8.png"  );
	tile_set_16  = load_image( (char*) "resources\\_tile_set_16.png" );
	tile_set_32  = load_image( (char*) "resources\\_tile_set_32.png" );
	tile_set_64  = load_image( (char*) "resources\\_tile_set_64.png" );
	tile_set_128 = load_image( (char*) "resources\\_tile_set_128.png");

	//Load the item set(s)
	item_set = load_image( (char *) "resources\\_item_set_32.png" );
	item_set_8   = load_image( (char*) "resources\\_item_set_8.png"  );
	item_set_16  = load_image( (char*) "resources\\_item_set_16.png" );
	item_set_32  = load_image( (char*) "resources\\_item_set_32.png" );
	item_set_64  = load_image( (char*) "resources\\_item_set_64.png" );
	item_set_128 = load_image( (char*) "resources\\_item_set_128.png");
	//being set
	being_set	 = load_image( (char*) "resources\\_being_set.png");
	
	//inventory buttons
	inv_in = load_image((char*) "resources\\buttons\\invIn32x32.png");
	inv_out = load_image((char*) "resources\\buttons\\invOut32x32.png");
	inventory_background = load_image( (char *) "resources\\_inventoryBackground32x32.png" );
	inventory_border = load_image( (char *) "resources\\_inventoryBorder8x8.png" );

	//Load the textbox image
	textBox = load_image( (char *) "resources\\_textBox.png" );

	//Load the greenButton
	blueButtonOver = load_image( (char *) "resources\\buttons\\_buttonOver256x48.png" );
	//Load the greenButton
	blueButtonUp = load_image( (char *) "resources\\buttons\\_buttonUp256x48.png" );
	//Load the greenButton
	blueButtonDown = load_image( (char *) "resources\\buttons\\_buttonDown256x48.png" );

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

	//load acatar.
	playerAvatar = load_image( (char *)"resources\\_character32.png");
	//load 128x128 player avatar.
	playerAvatar128 = load_image( (char *)"resources\\_character128.png");
	//the 128x256 player avatar for the inventory.
	playerAvatarInventory = load_image( (char*) "resources\\_character_inv.png");

	// 512 x 512 of black. because I can.
	black512 = load_image( (char *)   "resources\\_black512.png" );
	grid512  = load_image( (char *) "resources\\_grid512_2.0.png");


	//load audio
	a_button_click = 	load_audio( "resources\\sounds\\_button_click.wav");
	a_error = 			load_audio( "resources\\sounds\\_error.wav");
	a_find = 			load_audio( "resources\\sounds\\_find.wav");
	a_teleport = 		load_audio( "resources\\sounds\\_teleport.wav");
	a_footstep =		load_audio( "resources\\sounds\\_footstep.wav");
	a_box_open =		load_audio( "resources\\sounds\\_box_open.wav");
	a_blast =			load_audio("resources\\sounds\\enemies\\_blast.wav");
	//load music
	m_Learn_by_Doing =	load_music( "resources\\sounds\\Learn by Doing.ogg");


	//If everthing loaded fine
	return true;
}




/*
there has been an error! oh noes!
0: error in flipping the screen

if you enter a 10, it is a generic error with the title "Error" and the body of the error bessage is just the input string.

*/
int handle_error(int input, char *input_string){
	Mix_PlayChannel(-1, a_error, 0);
	char main_message[512], title_message[128];
	// if exit == 1, the program will exit after the message box.
	// if exit == 0, the program continues with execution after the error message box.
	int hault = 0, ret_val = 404, box_ret_val;
	int box_type = MB_OK;

	// general error message
	if      (input == 10){
		strcpy(main_message, input_string);
		strcpy(title_message, "Error");
		box_type |= MB_ICONERROR;
	}
	else if (input == 0){ // couldn't flip screen.
		strcpy(main_message, "Dungeon Crawler cannot update the screen.");
		strcpy(title_message, "Generic Graphics Error");
		ret_val = 100;
		box_type |= MB_ICONWARNING;
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
		box_type |= MB_ICONWARNING;
	}
	else if(input == 3){ // overwrite saved map?
		strcpy(main_message, "Are you sure you want to overwrite\n\t");
		strcat(main_message, input_string);
		strcpy(title_message, "Overwrite?");
		box_type = MB_YESNOCANCEL | MB_ICONQUESTION;
	}
	else if(input == 4){ // can't create file
		strcpy(main_message, "cannot create map:\n\t");
		strcat(main_message, input_string);
		strcpy(title_message, "Error creating map");
		box_type |= MB_ICONERROR;
	}
	else if(input == 5){ // can't load file
		strcpy(main_message, "cannot load map:\n\t");
		strcat(main_message, input_string);
		strcpy(title_message, "Map Load Error");
		box_type = MB_OK | MB_ICONERROR;
	}
	else if(input == 6){
		strcpy(main_message, "Save before leaving the map?");
		strcpy(title_message, "SAVE?");
		box_type = MB_YESNOCANCEL | MB_ICONQUESTION;
	}
	else if(input == 7){
        strcpy(main_message, "Clear ALL the tiles and items?");
		strcpy(title_message, "CLEAR?");
		box_type = MB_OKCANCEL | MB_ICONQUESTION;
	}
	else{
		strcpy(main_message, "I just don't know what went wrong!");
		strcpy(title_message, "Unknown Error Has Occured!\nWhat do you WANT FROM ME?!?!");
		box_type = MB_YESNOCANCEL | MB_ICONWARNING;
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

/// this function accepts a file name (with an extention) and opens it in the users default program.
/// "resources\\help_files\\" is were the program looks for the file (directory).
void help(char* place){
    ShellExecute(NULL, "open", place, NULL, "resources\\help_files\\", SW_SHOWNORMAL);
}


//adds two items together and producess an item
//bare bones to get it working
short calc_item(short item1, short item2) {

    return sqrt((item1 * item1) + (item2 * item2));

}

void engineer( struct item *item1, struct item *item2, struct item *dest){

    dest->attack = calc_item(item1->attack, item2->attack);
    dest->defense = calc_item(item1->defense, item2->defense);
    dest->uses = calc_item(item1->uses, item2->uses);
    dest->repair = calc_item(item1->repair, item2->repair);
    dest->health = calc_item(item1->health, item2->health);
    dest->speed = ((item1->speed + item2->speed) / 2);
    dest->thirst = calc_item(item1->thirst, item2->thirst);
    //we will have to fix the below later as we just need the desitination item to have a value
    dest->hexID = item1->hexID;
    dest->name = item1->name;
    dest->type = item1->type;
    dest->description = item1->description;

}




void clean_up(){
	//SDL_FreeSurface( text			);
	SDL_FreeSurface( screen   		);
	SDL_FreeSurface( tile_set 		);
	SDL_FreeSurface( item_set 		);
	SDL_FreeSurface( playerAvatar	);

	SDL_FreeSurface( grid512		);
	SDL_FreeSurface( black512 		);
	SDL_FreeSurface( title_image	);
	SDL_FreeSurface( icon			);
	SDL_FreeSurface( splash 		);
	SDL_FreeSurface( pressH         );

	SDL_FreeSurface( blueButtonOver	);
	SDL_FreeSurface( blueButtonUp 	);
	SDL_FreeSurface( blueButtonDown );

	SDL_FreeSurface( whiteButton 	);

	SDL_FreeSurface( msg 			);
	SDL_FreeSurface( textBox 		);

	un_init_buttons();

	Mix_FreeChunk( a_error 			);
	Mix_FreeChunk( a_button_click 	);
	Mix_FreeChunk( a_teleport 		);
	Mix_FreeChunk( a_find 			);

	//SDL_FreeSurface(  );

	//Quit SDL
	SDL_Quit();
}



void quit_game(){
	clean_up();
	exit(0);
}
