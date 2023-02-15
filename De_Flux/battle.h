


#define debugbattle ture

void battle(struct party *hostile){
	
	
	// -------------------------------------------
	// USER-INPUT VARIABLES
	// -------------------------------------------
	
	/* MOUSE DATA SYSTEM
	[0][] is ignored.
	[1][] = SDL_BUTTON_LEFT
	[2][] = SDL_BUTTON_MIDDLE
	[3][] = SDL_BUTTON_RIGHT
	[4][] = SDL_BUTTON_WHEELDOWN
	[5][] = SDL_BUTTON_WHEELUP
	[][0] = current state
	[][1] = pervious state */
	bool mouse[6][2];
	/* keeps track of if the mouse buttons were just clicked
	[0] is ignored
	*/
	bool mClicked[6];
	//keeps track of if the alt key is pressed
	int alt;
	//these are the user's mouse coordinates
	int x,y;
	// loop variables
	int i;
	//keeps track of if the user wants to quit or not.
	bool quit = false;
	
	
	
	
	// -------------------------------------------
	// GRAPHICS VARIABLES
	// -------------------------------------------
	//color of the background
	int backgroundColor = 0x9a9a9a;
	//general purpose SDL rectangle.
	SDL_Rect myRect;
	
	#if debugbattle
	printf("SDL_BUTTON_LEFT = %d", SDL_BUTTON_LEFT);
	printf("SDL_BUTTON_MIDDLE = %d", SDL_BUTTON_MIDDLE);
	printf("SDL_BUTTON_RIGHT = %d", SDL_BUTTON_RIGHT);
	printf("SDL_BUTTON_WHEELDOWN = %d", SDL_BUTTON_WHEELDOWN);
	printf("SDL_BUTTON_WHEELUP = %d", SDL_BUTTON_WHEELUP);
	#endif
	
	
	
	
	
	//the battle system user-input loop.
	do{
		while(SDL_PollEvent(&event)){
			switch(event.type){
			case SDL_QUIT:
				quit = 1;
				break;
			case SDL_MOUSEBUTTONDOWN:
				x = event.button.x;
				y = event.button.y;
				if(event.button.button >= 1 && event.button.button <= 5)
					mouse[event.button.button][0] = DOWN;
				break;
			case SDL_MOUSEBUTTONUP:
				x = event.button.x;
				y = event.button.y;
				if(event.button.button >= 1 && event.button.button <= 5)
					mouse[event.button.button][0] = UP;
				break;
			case SDL_MOUSEMOTION:
				x = event.button.x;
				y = event.button.y;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
				case SDLK_RALT:
					alt++;
					break;
				case SDLK_LALT:
					alt++;
					break;
				case SDLK_F4:
					if(alt) quit = true;
					break;
				default:
					break;
				}
				break;
			case SDL_KEYUP:
				switch(event.key.keysym.sym){
				case SDLK_RALT:
					alt--;
					break;
				case SDLK_LALT:
					alt--;
					break;
				default:
					break;
				}
			default:
				break;
			}
			if(quit)break;
		} // end user-input loop
		if(quit)break;
		
		
		
		//evaluate if mouse buttons were just clicked
		for(i=1; i<=5; i++){ if(mouse[i][0] == DOWN && mouse[i][1] == UP) mClicked[i] = DOWN; else mClicked[i] = UP; }
		
		
		//fill background 
		myRect.x = 0;//borderThickness;
		myRect.y = 0;//borderThickness;
		myRect.w = SCREEN_WIDTH ;//- 2*borderThickness;
		myRect.h = SCREEN_HEIGHT ;//- 2*borderThickness;
		SDL_FillRect(screen, &myRect, backgroundColor);
		
		/* working on this
		//print playerParty
		int wsofar;
		for(wsofar=0,i=0; i<MAX_PARTY_MEMBERS_DEPLOYED; i++){
			apply_surface_clips(SCREEN_HEIGHT-256, 
		}
		*/
		
		
		
		SDL_Flip(screen);
	}while(!quit); // end the do{} loop. we are done battling.
}
