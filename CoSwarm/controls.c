#include "controls.h"
#include <SDL\SDL.h>
#include "graphics.h"

void init_controls(){
	
	controlsGame.pan[d_up] = 		SDLK_UP;
	controlsGame.pan[d_down] =		SDLK_DOWN;
	controlsGame.pan[d_left] =		SDLK_LEFT;
	controlsGame.pan[d_right] =		SDLK_RIGHT;
	
	controlsGame.options =			SDLK_ESCAPE;
	controlsGame.pause =			SDLK_SPACE;
	
	controlsGame.menu[d_up] =		SDLK_UP;
	controlsGame.menu[d_down] =		SDLK_DOWN;
	controlsGame.menu[d_left] =		SDLK_LEFT;
	controlsGame.menu[d_right] =	SDLK_RIGHT;
	controlsGame.menu_select =		SDLK_RETURN;
	
	controlsGame.debug = 			SDLK_F3;
	
}
