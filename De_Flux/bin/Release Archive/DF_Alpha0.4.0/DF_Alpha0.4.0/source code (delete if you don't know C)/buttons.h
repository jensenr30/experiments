//button surfaces
SDL_Surface *blueButtonOver	= NULL;
SDL_Surface *blueButtonUp	= NULL;
SDL_Surface *blueButtonDown	= NULL;
SDL_Surface *whiteButton        = NULL;
SDL_Surface *whiteBlueButton   =  NULL;
SDL_Surface *blueGlintIvy96x32	= NULL;
SDL_Surface *blueGlintIvy128x48	= NULL;

// button text colors
SDL_Color buttonColorOver = { 0x0,0x0,0x0 };
SDL_Color buttonColorUpRed =   { 0x8b, 0x0f, 0x0f };
SDL_Color buttonColorUpPurple =   { 0x2c, 0x0f, 0x6c };
SDL_Color buttonColorDown = { 0x0,0x0,0x0 };

SDL_Color whiteButtonColorUp = { 0x7f, 0x7f, 0x7f };
SDL_Color whiteButtonColorOver = { 0x9f, 0x9f, 0x9f };

SDL_Color colorWhite = {255,255,255};
SDL_Color colorGreyUp = {0x7f, 0x7f, 0x7f};
SDL_Color colorGreyOver = {0x9f, 0x9f, 0x9f};
SDL_Color colorBlack = {0,0,0};




struct button{
	// pos needs to be first in order for within_rect(x, y, butSet->buttons) to work properly (see the render_buttons() function
	SDL_Rect pos;	// this describes where the button is and what its size is.
	SDL_Rect textOffset;// this holds where the text goes (in relation to the position of the button)
	char *text;		// what the button is called
	int state;	// this holds the state of the button (OVER, UP, or DOWN)
	
	SDL_Surface *over;	// when the mouse is over the button
	SDL_Surface *up;	// this is what lies under the button
	SDL_Surface *down;	// this is what lies under the button
	
	SDL_Color colorUp;	// this is the color of the text when the button is not pressed in
	SDL_Color colorDown;// this is the color of the text when the button is pressed in
	SDL_Color colorOver;// this is for the color fo the text when the cursor is over the button
	TTF_Font *font;	// this is the font the button will be rendered with.
};

struct buttonSet{
	struct button *buttons[MAX_BUTTONS_IN_A_SET]; // an array of pointers to a button
	int totalButtons;   // the number of buttons in a buttonSet
};




struct buttonSet titleScreenButtons;
struct button b_play, b_mapMaker, b_quit, b_options, b_help;

struct buttonSet mapMakerButtons;
struct button b_mmOptions, b_mmTiles, b_mmItems, b_inventoryArea;

struct buttonSet optionsButtons;
struct button b_optionsWidthUp, b_optionsWidthDown, b_optionsHeightUp, b_optionsHeightDown;


//initializes all of the button sets
void init_buttons()
{
	//--------------------------------------------------------------------------------------------------
	// optionsButtons
	//--------------------------------------------------------------------------------------------------
//buttonSet
	optionsButtons.buttons[0] = &b_optionsWidthUp;
	optionsButtons.buttons[1] = &b_optionsWidthDown;
	optionsButtons.buttons[2] = &b_optionsHeightUp;
	optionsButtons.buttons[3] = &b_optionsHeightDown;
	optionsButtons.totalButtons = 4;
//buttons
	
	b_optionsWidthUp.state = b_optionsWidthDown.state = b_optionsHeightUp.state = b_optionsHeightDown.state = UP;
	b_optionsWidthUp.text = "w++";
	b_optionsWidthDown.text = "w--";
	b_optionsHeightUp.text = "h++";
	b_optionsHeightDown.text = "h--";
	
	b_optionsHeightUp.font = b_optionsHeightDown.font = b_optionsWidthUp.font = b_optionsWidthDown.font = sansFont;
	
	b_optionsHeightUp.colorUp = b_optionsHeightDown.colorUp = b_optionsWidthUp.colorUp = b_optionsWidthDown.colorUp = colorBlack;
	b_optionsHeightUp.colorOver = b_optionsHeightDown.colorOver = b_optionsWidthUp.colorOver = b_optionsWidthDown.colorOver = colorGreyOver;
	b_optionsHeightUp.colorDown = b_optionsHeightDown.colorDown = b_optionsWidthUp.colorDown = b_optionsWidthDown.colorDown = colorBlack;
	
	b_optionsWidthUp.pos.x = 8 + 64 + 8 + 64 + 8;
	b_optionsWidthUp.pos.y = 8 + 48;
	b_optionsWidthUp.pos.w = 64;
	b_optionsWidthUp.pos.h = 48;
	
	b_optionsWidthDown.pos.x = 8;
	b_optionsWidthDown.pos.y = 8 + 48;
	b_optionsWidthDown.pos.w = 64;
	b_optionsWidthDown.pos.h = 48;
	
	b_optionsHeightUp.pos.x = 8 + 64 + 8;
	b_optionsHeightUp.pos.y = 8 + 48 + 8 + 48 + 8;
	b_optionsHeightUp.pos.w = 64;
	b_optionsHeightUp.pos.h = 48;
	
	b_optionsHeightDown.pos.x = 8 + 64 + 8;
	b_optionsHeightDown.pos.y = 8;
	b_optionsHeightDown.pos.w = 64;
	b_optionsHeightDown.pos.h = 48;
	
	b_optionsWidthUp.over = b_optionsWidthDown.over = b_optionsHeightUp.over = b_optionsHeightDown.over = whiteBlueButton;
	b_optionsWidthUp.up   = b_optionsWidthDown.up   = b_optionsHeightUp.up   = b_optionsHeightDown.up   = whiteBlueButton;
	b_optionsWidthUp.down = b_optionsWidthDown.down = b_optionsHeightUp.down = b_optionsHeightDown.down = whiteBlueButton;
	
	b_optionsWidthUp.textOffset.x = b_optionsWidthDown.textOffset.x = b_optionsHeightUp.textOffset.x = b_optionsHeightDown.textOffset.x = 10;
	b_optionsWidthUp.textOffset.y = b_optionsWidthDown.textOffset.y = b_optionsHeightUp.textOffset.y = b_optionsHeightDown.textOffset.y = 0;
	
	
	
	//--------------------------------------------------------------------------------------------------
	// mapMakerButtons
	//--------------------------------------------------------------------------------------------------
	
//buttonSet
	mapMakerButtons.buttons[0] = &b_mmOptions;
	mapMakerButtons.buttons[1] = &b_mmTiles;
	mapMakerButtons.buttons[2] = &b_inventoryArea;
	mapMakerButtons.buttons[3] = &b_mmItems;
	mapMakerButtons.totalButtons = 4;
	
//buttons
	b_mmOptions.text = "Options";
	b_mmOptions.state = UP;
	
	b_mmOptions.pos.x = 4;
	b_mmOptions.pos.y = 4;
	b_mmOptions.pos.w = 96;
	b_mmOptions.pos.h = 32;
	
	b_mmOptions.over = b_mmOptions.up = b_mmOptions.down = blueGlintIvy96x32;
	
	b_mmOptions.textOffset.x = 21;
	b_mmOptions.textOffset.y = 2;
	b_mmOptions.colorDown = colorBlack;
	b_mmOptions.colorOver = whiteButtonColorOver;
	b_mmOptions.colorUp = colorBlack;
	b_mmOptions.font = sansFont2;
	
	b_mmTiles.text = "Tiles";
	b_mmTiles.state = UP;
	b_mmTiles.font = sansFont2;
	b_mmTiles.textOffset.x = 30;
	b_mmTiles.textOffset.y = 2;
	b_mmTiles.colorOver = whiteButtonColorOver;
	b_mmTiles.colorUp = b_mmTiles.colorDown = colorBlack;
	
	b_mmTiles.pos.w = 96;
	b_mmTiles.pos.h = 32;
	b_mmTiles.pos.y = 0;
	b_mmTiles.pos.x = SCREEN_WIDTH - b_mmTiles.pos.w;
	
	b_mmTiles.over = b_mmTiles.up = b_mmTiles.down = blueGlintIvy96x32;
	
	b_inventoryArea.text = " ";
	b_inventoryArea.state = UP;
	b_inventoryArea.font = NULL;
	b_inventoryArea.textOffset.x = 0;
	b_inventoryArea.textOffset.y = 0;
	b_inventoryArea.colorUp = b_inventoryArea.colorDown = b_inventoryArea.colorOver = colorBlack;
	
	b_inventoryArea.pos.x = SCREEN_WIDTH - ( INVENTORY_TILE_SIZE * INVENTORY_WIDTH ) - 24;
	b_inventoryArea.pos.y = 32;
	b_inventoryArea.pos.w = INVENTORY_WIDTH * 32 + 8*2;
	b_inventoryArea.pos.h = INVENTORY_HEIGHT* 32 + 8*2;
	
	b_inventoryArea.over = b_inventoryArea.up = b_inventoryArea.down = NULL;
	
	
	b_mmItems.text = "Items";
	b_mmItems.state = UP;
	b_mmItems.font = sansFont2;
	b_mmItems.textOffset.x = 30;
	b_mmItems.textOffset.y = 2;
	b_mmItems.colorOver = whiteButtonColorOver;
	b_mmItems.colorUp = b_mmItems.colorDown = colorBlack;
	
	b_mmItems.pos.y = 0;
	b_mmItems.pos.w = 96;
	b_mmItems.pos.h = 32;
	b_mmItems.pos.x = SCREEN_WIDTH - b_mmItems.pos.w * 2;
	
	b_mmItems.over = b_mmItems.up = b_mmItems.down = blueGlintIvy96x32;
	
	
	//--------------------------------------------------------------------------------------------------
	// titleScreenButtons
	//--------------------------------------------------------------------------------------------------

//buttonSet
	titleScreenButtons.buttons[0] = &b_play;
	titleScreenButtons.buttons[1] = &b_mapMaker;
	titleScreenButtons.buttons[2] = &b_quit;
	titleScreenButtons.buttons[3] = &b_options;
	titleScreenButtons.buttons[4] = &b_help;
	titleScreenButtons.totalButtons = 5;

//buttons
	b_options.pos.w = b_play.pos.w = b_mapMaker.pos.w = b_quit.pos.w = b_help.pos.w = 256;
	b_options.pos.h = b_play.pos.h = b_mapMaker.pos.h = b_quit.pos.h = b_help.pos.h =  48;
	b_options.pos.x = SCREEN_WIDTH/2 - b_options.pos.w/2;
	b_play.pos.x = SCREEN_WIDTH/2 - b_play.pos.w/2;
	b_mapMaker.pos.x = SCREEN_WIDTH/2 - b_mapMaker.pos.w/2;
	b_quit.pos.x = SCREEN_WIDTH/2 - b_quit.pos.w/2;
	b_help.pos.x = SCREEN_WIDTH/2 - b_help.pos.w/2;
	
	b_play.pos.y = 		SCREEN_HEIGHT/2 - b_play.pos.h/2 - 150 - 48;
	b_mapMaker.pos.y = 	SCREEN_HEIGHT/2 - b_mapMaker.pos.h/2 - 150;
	b_help.pos.y = 		SCREEN_HEIGHT/2 - b_help.pos.h/2    + 150;
	b_options.pos.y =   SCREEN_HEIGHT/2 - b_options.pos.h/2 + 150 + 48;
	b_quit.pos.y = 		SCREEN_HEIGHT/2 - b_quit.pos.h/2    + 150 + 48 + 48;
	
	
	b_play.textOffset.x = b_play.pos.w/2 - 56;
	b_mapMaker.textOffset.x = b_mapMaker.pos.w/2 - 56;
	b_quit.textOffset.x = b_quit.pos.w/2 - 24;
	b_options.textOffset.x = b_options.pos.w/2 - 40;
	b_help.textOffset.x = b_help.pos.w/2 - 24;
	b_options.textOffset.y = b_play.textOffset.y = b_mapMaker.textOffset.y = b_quit.textOffset.y = b_help.textOffset.y = 3;
	
	
	b_help.over = b_options.over = b_play.over = b_mapMaker.over = b_quit.over = blueButtonOver;
	b_help.up =   b_options.up   = b_play.up   = b_mapMaker.up   = b_quit.up   = blueButtonUp;
	b_help.down = b_options.down = b_play.down = b_mapMaker.down = b_quit.down = blueButtonDown;
	
	b_help.font = b_options.font = b_play.font = b_mapMaker.font = b_quit.font = sansFont;
	
	b_help.colorUp =   b_options.colorUp =   b_play.colorUp =   b_mapMaker.colorUp =   b_quit.colorUp =   colorBlack;
	b_help.colorDown = b_options.colorDown = b_play.colorDown = b_mapMaker.colorDown = b_quit.colorDown = colorBlack;
	b_play.colorOver = b_mapMaker.colorOver = buttonColorUpRed;
	b_help.colorOver = b_options.colorOver = b_quit.colorOver = buttonColorUpPurple;
	
	b_options.state = b_play.state = b_mapMaker.state = b_quit.state = b_help.state = UP;
	
	b_play.text =		(char*) "Play Game";
	b_mapMaker.text =	(char*) "Map Maker";
	b_quit.text =		(char*) "Quit";
	b_options.text =	(char*) "Options";
	b_help.text = 		(char*) "Help";
	
}

void un_init_buttons(){
	
	
	
	
	
	
}


int apply_button( struct button *but ){
	if(but->state == OVER)
		apply_surface(but->pos.x, but->pos.y, but->over, screen);
	else if(but->state == UP)
		apply_surface(but->pos.x, but->pos.y, but->up, screen);
	else
		apply_surface(but->pos.x, but->pos.y, but->down, screen);
	if(but->state == OVER)
		apply_text(but->pos.x + but->textOffset.x, but->pos.y + but->textOffset.y, but->font, but->text, but->colorOver);


	else if(but->state == DOWN)
		apply_text(but->pos.x + but->textOffset.x, but->pos.y + but->textOffset.y, but->font, but->text, but->colorDown);
	else 
		apply_text(but->pos.x + but->textOffset.x, but->pos.y + but->textOffset.y, but->font, but->text, but->colorUp);
	return 1;
};



/*
inputs the coordinates of the mouse. the mouse state is meant to reflect the mouse's current and previous state
returns -1 if no button was pressed.
returns a number from 0 to (n-1) for a list of buttons that contains n buttons.
what number is returned depends on which button was pressed.
mouseStatePrev is the previous mouse state.
mouseStateCurr is the  current mouse state.
*/
int render_buttons(int x, int y, int mouseStatePrev, int mouseStateCurr, struct buttonSet *butSet){
	int i;
	int ret_val = -1; // returns -1 by default. this shows that no buttons were clicked.
	//struct button tempBut;
	for(i = 0; i < butSet->totalButtons; i++){
		
		if( within_rect(x, y, &butSet->buttons[i]->pos) == 0) // mouse outside the button
			butSet->buttons[i]->state = UP;
		else if( mouseStateCurr == UP) // mouse inside and up
			butSet->buttons[i]->state = OVER;
		else						   // mouse is inside and down.
			butSet->buttons[i]->state = DOWN;
		
		apply_button(butSet->buttons[i]); // place it here
		
		// if the mouse was just released then the user clicked this point
		if(mouseStatePrev == DOWN && mouseStateCurr == UP){
			if( within_rect(x, y, &butSet->buttons[i]->pos) ){
				ret_val = i;
				PlaySound("resources\\sounds\\_button_click.wav", NULL, SND_ASYNC);
			}
		}
	}
	return ret_val;
}


//checks to see if the mouse is hovering over any buttons.
int over_button(int x, int y, struct buttonSet *butSet){
	int i;
	for(i = 0; i < butSet->totalButtons; i++){
		if( within_rect(x, y, &butSet->buttons[i]->pos) == 1 )
			return i;
	}
	return -1; // if the mouse isn't over any buttons, return -1
}




