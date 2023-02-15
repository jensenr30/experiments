

struct controlData{
	
	int pan[4];			// this is an array. it gets indexed with d_up, d_down, d_left, and d_right.
	
	int pause;			// pause the game
	int options;		// open options menu
	
	int menu[4];		// this is an array. it gets indexed with d_up, d_down, d_left, and d_right.
	int menu_select;	// select an option in menus
	
	int debug;			// the key that controls the debug information
	
};

// these are the main part of the game's controls
struct controlData controlsGame;

void init_controls();
