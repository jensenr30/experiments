

int options( void )
{
	int quit = 0; // set to 1 if you want to exit the entire program.
	int alt = 0; // this variable is used to keep track of if the alt keys are pressed.
	int render_buttons_return_value = 0;
	int i; // whore variable
	// this holds which mouse button was pressed
	int mouse[5][2]; // mouse[0][0] == left mouse button's current state, mouse[0][1] = left mouse button's previous state
	for(i = 0; i < 5; i++) mouse[i][0] = mouse[i][1] = UP; // init all mouse variables to UP
	int x = 0, y = 0;
	int key; // this will hold the value of event.key.keysym.sym. using "key" is easier than writing "event.key.keysym.sym" everytime. :P

	char speedString[4]; // for the input of the speed of the player.
	// get the player's speed in string format
	itoa(player.speed, speedString, 10);

	do{
		while( SDL_PollEvent(&event) ){
			if(event.type == SDL_QUIT || quit)
				quit_game();
			if(event.type == SDL_MOUSEBUTTONDOWN){
				x = event.button.x;
				y = event.button.y;
				if(event.button.button == 1) // left click
					mouse[0][0] = DOWN; // store current mosue state
			}
			else if(event.type == SDL_MOUSEMOTION){
				x = event.button.x;
				y = event.button.y;
			}
			else if(event.type == SDL_MOUSEBUTTONUP){
				x = event.button.x;
				y = event.button.y;
				if(event.button.button == 1) // left click
					mouse[0][0] = UP; // store current mosue state
			}
			else if(event.type == SDL_KEYDOWN){
				key = event.key.keysym.sym;

				if(key == SDLK_ESCAPE) return 0; // escape leaves options
				else if(key == SDLK_RALT || key == SDLK_LALT) alt = 1;
				else if(key == SDLK_F4 && alt) quit = 1;
			}
			else if(event.type == SDL_KEYUP){
				key = event.key.keysym.sym;
				if(key == SDLK_h){
					Mix_PlayChannel(-1, a_button_click, 0);
					help("options.txt");
				}
				else if(key == SDLK_RALT || key == SDLK_LALT) alt = 0;
			}

			blank_screen();

			render_buttons_return_value = render_buttons(x, y, mouse[0][1], mouse[0][0], &optionsButtons);
			switch ( render_buttons_return_value ){
			case -1:  // no button pushed
				break;
			case 0: // width++
				SCREEN_WIDTH += PIXELS_PER_SCREEN_DIVISION;
				break;
			case 1: // width--
				SCREEN_WIDTH -= PIXELS_PER_SCREEN_DIVISION;
				break;
			case 2: // height++
				SCREEN_HEIGHT += PIXELS_PER_SCREEN_DIVISION;
				break;
			case 3: // height--
				SCREEN_HEIGHT -= PIXELS_PER_SCREEN_DIVISION;
				break;
			case 4:
				if( input_string(speedString, 4) == 0 ) break;
				player.speed = atoi(speedString);
				if(player.speed > MAX_PLAYER_SPEED) player.speed = MAX_PLAYER_SPEED;
				if(player.speed < 1) player.speed = 1;
				itoa(player.speed, speedString, 10);
				break;
			} // end switch statement

			//apply the speed of the player here
			apply_text(optionsButtons.buttons[4]->pos.x + optionsButtons.buttons[4]->pos.w, optionsButtons.buttons[4]->pos.y, sansFont, speedString, colorWhite);

		}//while( SDL_PollEvent(&event) )

		 // check to see if you need to resize the screen
		if(render_buttons_return_value >= 0 && render_buttons_return_value <= 3)
			set_screen_size();

		SDL_Flip( screen );
		SDL_FreeSurface( screen );
		mouse[0][1] = mouse[0][0]; // archive the current mouse state
		Sleep(10);
	}while(1); // end do{}
	return 0;
}


