

int options( void )
{
	int render_buttons_return_value;
	int i; // whore variable
	// this holds which mouse button was pressed
	int mouse[5][2]; // mouse[0][0] == left mouse button's current state, mouse[0][1] = left mouse button's previous state
	for(i = 0; i < 5; i++) mouse[i][0] = mouse[i][1] = UP; // init all mouse variables to UP
	int x = 0, y = 0;
	
	do{
		while( SDL_PollEvent(&event) ){
			if(event.type == SDL_QUIT)
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
				if(event.key.keysym.sym == SDLK_ESCAPE) // left click
					return 0;
			}
			else if(event.type == SDL_KEYUP){
				if(event.key.keysym.sym == SDLK_h){
					PlaySound("resources\\sounds\\_button_click.wav", NULL, SND_ASYNC);
					system("resources\\help_files\\options.txt");
					
				}
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
			} // end switch statement
			
			 // check to see if you need to resize the screen
			if(render_buttons_return_value >= 0 && render_buttons_return_value <= 3)
				set_screen_size();
				
			
			SDL_Flip( screen );
			SDL_FreeSurface( screen );
			mouse[0][1] = mouse[0][0]; // archive the current mouse state
		}//while( SDL_PollEvent(&event) )
		Sleep(10);
	}while(1); // end do{}
	return 0;
}


