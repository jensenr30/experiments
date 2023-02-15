
#define DEBUG_BATTLE_FROM_MENU 1

int main_menu(){
	blank_screen(); // blank the screen
	Mix_FadeOutMusic(MUSIC_FADE_TIME); // fade out music
	int x = 0, y = 0; // mouse cordinates
	int mousePrev = UP; // the state of the left mouse button from the last itteration of the program.
	int mouseCurr = UP; // the state of the left mouse button now.
	int ret_from_render_buttons = -1; // this is used to store the return value of the ret_from_render_buttons function.
	int key; // this is used to store what key was pressed in the event of a key press event.
	int alt = 0; // keeps track of if the user pressed the alt key.
	int quit = 0; // keeps track of if the user wants to quit. set to 1 to exit the main menu.
	#if DEBUG_BATTLE_FROM_MENU // debug the battle
	struct party hostileParty;
	int partyCount;
	hostileParty.partyType = pt_hostile;
	for(partyCount=0; partyCount<MAX_PARTY_MEMBERS; partyCount++){
		being_erase(&hostileParty.beings[0]);
	}
	being_copy( &beingAtt[b_flame_monster], &hostileParty.beings[0]);
	being_copy( &beingAtt[b_tree], &hostileParty.beings[0]);
	for(partyCount=0; partyCount<MAX_PARTY_MEMBERS_DEPLOYED; partyCount++){
		hostileParty.deployed[partyCount] = partyCount;
	}
	#endif


	//While the user hasn't quit
    do{
    	mousePrev = mouseCurr;
    	//While there's an event to handle
    	while(SDL_PollEvent(&event)){
    		//If the user has Xed out the window
    		if(event.type == SDL_QUIT || quit){
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
				#if DEBUG_BATTLE_FROM_MENU
				else if(key == SDLK_b) battle(&hostileParty);
				#endif
				else if(key == SDLK_f) Mix_PlayChannel(-1, a_find, 0); // test sound "find"
				else if(key == SDLK_RALT || key == SDLK_LALT) alt = 1;
				else if(key == SDLK_F4){
					if(alt){
						quit = 1;
					}
				}
			}
			else if(event.type == SDL_KEYUP){
					key = event.key.keysym.sym;
				if(key == SDLK_h){
					PlaySound("resources\\sounds\\_button_click.wav", NULL, SND_ASYNC);
					help("main_menu.txt");
				}
				else if(key == SDLK_RALT || key == SDLK_LALT) alt = 0;
			}
    	} // while ( SDL_PollEvent(&event) )
    	blank_screen();
    	// apply title image to the middle of the screen
		apply_surface(SCREEN_WIDTH/2 - 672/2 - 16, SCREEN_HEIGHT/2 - 346/2, title_image, screen);
		//apply the "press 'h'" picture at the bottom right corner of the screen
		apply_surface(SCREEN_WIDTH - 328, SCREEN_HEIGHT - 35, pressH, screen);

		ret_from_render_buttons = render_buttons(x, y, mousePrev, mouseCurr, &titleScreenButtons);
		if(ret_from_render_buttons != -1){ // if there was a button pressed, return that button press!
			if(ret_from_render_buttons == 4){
				PlaySound("resources\\sounds\\_button_click.wav", NULL, SND_ASYNC);
				help("main_menu.txt");
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


