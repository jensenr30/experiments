#include "bool.h"

struct beastData{
	
	//position in the grid
	int x;
	int y;
	
	// this is the object that the beast is trying to get to
	// target[0] is the y coordinate
	// target[1] is the x coordinate
	int target[2];
	// this variable describes whether or not the beast is currently running towards a target
	bool targetActive;
};

// this defines how many beast pointers can be in one block
#define BEASTS_BLOCK_SIZE 512

// the program keeps track of the beasts in a linked list of groups of pointers to beasts.
struct beastsBlockData{
	// this is a pointer to the next block of beasts.
	struct beastsBlockData *next;
	// the is a pointer to a decent number of beasts. This is called a block of beasts
	struct beastData *bp[BEASTS_BLOCK_SIZE];
};

// this is the starting block of beast data. this is the first block of the linked list
struct beastsBlockData beasts;

// this is how many beasts there are on the map.
// it is nice to keep track of this number for malloc purposes
unsigned int beastsNumberOf;



void init_beasts();
void beasts_free_list();
bool beast_copy();
struct beastData *beast_create(struct beastData *beast);
bool beast_erase(struct beastData *beast);
bool beast_free(struct beastData *beast);
bool closest_mat(int x, int y, int mat, int *targetX, int *targetY, int maxRadius);
struct beastData *beast_find_at_cell(int x, int y);
void beasts_evaluate();
