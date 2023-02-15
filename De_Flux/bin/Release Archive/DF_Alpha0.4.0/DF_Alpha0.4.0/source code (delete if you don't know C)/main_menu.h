

int title_screen(){
	blank_screen();
	int x = 0, y = 0;
	int mousePrev = UP;
	int mouseCurr = UP;
	int ret_from_render_buttons = -1;
	int key;
	
	
	
	//While the user hasn't quit
    do{
    	mousePrev = mouseCurr;
    	//While there's an event to handle
    	while(SDL_PollEvent(&event)){
    		//If the user has Xed out the window
    		if(event.type == SDL_QUIT){
				//Quit the program
				quit_game();
			}
			if(event.type == SDL_MOUSEBUTTONDOWN){
				if(event.button.button == 1){
					mouseCurr = DOWN;
					x = event.button.x;
					y = event.button.y;
				}
			}
			else if(event.type == SDL_MOUSEMOTION){
				x = event.button.x;
				y = event.button.y;
			}
			else if(event.type == SDL_MOUSEBUTTONUP){
				if(event.button.button == 1){
					mouseCurr = UP;
					x = event.button.x;
					y = event.button.y;
					
				}
			}
			else if(event.type == SDL_KEYDOWN){
				key = event.key.keysym.sym;
				if(key == SDLK_p) return 0;
				else if(key == SDLK_m) return 1;
				else if(key == SDLK_o) return 3;
				else if(key == SDLK_q) return 2;
			}
			else if(event.type == SDL_KEYUP){
				if(event.key.keysym.sym == SDLK_h){
					PlaySound("resources\\sounds\\_button_click.wav", NULL, SND_ASYNC);
					system("resources\\help_files\\main_menu.txt");
				}
			}
    	} // while ( SDL_PollEvent(&event) )
    	blank_screen();
		apply_surface(SCREEN_WIDTH/2 - 512/2, SCREEN_HEIGHT/2 - 384/2, title_image, screen);
		
		ret_from_render_buttons = render_buttons(x, y, mousePrev, mouseCurr, &titleScreenButtons);
		if(ret_from_render_buttons != -1){ // if there was a button pressed, return that button press!
			if(ret_from_render_buttons == 4){
				PlaySound("resources\\sounds\\_button_click.wav", NULL, SND_ASYNC);
				system("resources\\help_files\\main_menu.txt");
			}
			else
				return ret_from_render_buttons;
		}
		if(SDL_Flip( screen ) == -1) handle_error(0, NULL);
		SDL_FreeSurface( screen );   // clean up (prevent memory leaks)
	} while(1); // end do{}
	
	quit_game();
	// the program will never reach this point
	return -1; // this is here to satisfy the compiler. the program will never actually get here.
	
}


