#include <stdio.h>
#include <stdlib.h>
#include "beast.h"
#include "materials_and_cells.h"

// initialize all beast related things
void init_beasts(){
	
	// no beasts exist yet.
	beastsNumberOf = 0;
	
	// make all beast data NULL
	int i;
	for(i=0; i<BEASTS_BLOCK_SIZE; i++){
		beasts.bp[i] = NULL;
	}
	beasts.next = NULL;
	
}

void beasts_free_list(){
	int b;
	for(b=0; b<BEASTS_BLOCK_SIZE; b++){
		beast_free(beasts.bp[b]);
	}
}



// adds a beast to the beast linked list
bool beast_add_to_list(struct beastData *beast){
	int i;
	for(i=0; i<BEASTS_BLOCK_SIZE; i++){
		/// this section of the code does not account for linked list style beast architecture yet.
		if(beasts.bp[i] == NULL){
			beasts.bp[i] = beast;
			beastsNumberOf++;
			return true;
		}
	}
	return false;
}

// removes a beast from the beast linked list
bool beast_remove_from_list(struct beastData *beast){
	int i;
	for(i=0; i<BEASTS_BLOCK_SIZE; i++){
		/// this section of the code does not account for linked list style beast architecture yet.
		if(beasts.bp[i] == beast){
			beasts.bp[i] = NULL;
			beastsNumberOf--;
			return true;
		}
	}
	return false;
}


// returns true if the copying is successful.
// returns false otherwise.
bool beast_copy(struct beastData *sour, struct beastData *dest){
	
	// make sure neither the source or destination beast is NULL
	if(sour == NULL || dest == NULL) return false;
	
	// copy variables
	dest->x = sour->x;
	dest->y = sour->y;
	dest->target[0] = sour->target[0];
	dest->target[1] = sour->target[1];
	dest->targetActive = sour->targetActive;
	
	return true;
}


// creates a new beast using malloc and returns a pointer to the beast.
// if the function fails to create a new beast, NULL is returned.
struct beastData *beast_create(struct beastData *beast){
	// allocate memory for a new beast
	struct beastData *newBeast = malloc(sizeof(struct beastData));
	
	// if you failed to allocate a new beast, return NULL.
	if(newBeast == NULL) return NULL;
	beast_add_to_list(newBeast);
	// if beast was NULL, that means we don't need to copy attributes from beast into newBeast.
	// simply erasing the beast to default state will safice
	if(beast == NULL){
		beast_erase(newBeast);
		return newBeast;
	}
	else{
		beast_copy(beast, newBeast);
		return newBeast;
	}
}

// this sets beast data to default state
bool beast_erase(struct beastData *beast){
	beast->x = 0;
	beast->y = 0;
	beast->targetActive = false;
	return true;
}

// returns if true the beast memory was freed
// otherwise, returns false
bool beast_free(struct beastData *beast){
	if(beast == NULL) return false;
	free(beast);
	beast_remove_from_list(beast);
	return true;
}

//returns if the beast has a valid target
bool closest_mat(int x, int y, int mat, int *targetX, int *targetY, int maxRadius){
	int r,j,i,iStep;
	// if the beast is already standing on a valid target, return true
	if(grid[y][x].mat == mat){
		return false;
		//*targetX = x;
		//*targetY = y;
	}
	// otherwise, search for a proper target
	for(r=1; r<=maxRadius; r++){
		for(j=-r; j<=r; j++){
			if(j == -r || j == r)iStep = 1;
			else iStep = 2*r;
			for(i=-r; i<=r; i+=iStep){
				if(within_grid_elements(i+x,j+y)){
					if(grid[j+y][i+x].mat == mat){
						*targetX = x + i;
						*targetY = y + j;
						return true;
					}
				}
			}
		}
	}
	// if you couldn't find a proper target within the radius, quit and return false
	return false;
}



/// returns a pointer to the beast at location x,y.
/// if there is no beast at x,y, the function returns NULL
struct beastData *beast_find_at_cell(int x, int y){
	int b;
	for(b=0; b<BEASTS_BLOCK_SIZE; b++){
		if(beasts.bp[b] == NULL)
			continue;	// if the beast at index b is invalid, continue
		if(beasts.bp[b]->x == x && beasts.bp[b]->y == y)
			return beasts.bp[b];
	}
	return NULL;
}


void beasts_evaluate(){
	int b;
	int x,y; // these are for keeping track of what direction the beast wants to go
	struct beastData *beast;
	// this is a pointer to the beast that is in our current beast's way
	struct beastData *beastAtXY;
	//int i,j;
	for(b=0; b<BEASTS_BLOCK_SIZE; b++){
		beast = beasts.bp[b];	// this is where the beast pointer gets stored (this is simply for ease of writing this section)
		if(beast != NULL){			// if the beast at index i is NOT NULL
			if(beast->targetActive == false){		// if there is no target
				beast->targetActive = closest_mat(beast->x, beast->y, m_water, &(beast->target[0]), &(beast->target[1]), 50);
			}
			if(beast->targetActive==true){
				if(beast->target[0]-beast->x > 0){
					x=1;
				}
				else if(beast->target[0]-beast->x < 0){
					x=-1;
				}
				else{
					x=0;
				}
				if(beast->target[1]-beast->y > 0){
					y=1;
				}
				else if(beast->target[1]-beast->y <0){
					y=-1;
				}
				else{
					y=0;
				}
				beast->x+=x;
				beast->y+=y;
				/*
				// make sure there is no beast at (x,y) before you move the beast there
				beastAtXY = beast_find_at_cell(beast->x+x,beast->y+y);
				if(beastAtXY == NULL){
					beast->x+=x;
					beast->y+=y;
				}
				else{
					beastAtXY->x = beast->x-x;
					beastAtXY->y = beast->y-y;
					beast->x+=x;
					beast->y+=y;
				}
				*/
				
				if(beast->target[0] == beast->x && beast->target[1] == beast->y){
					beast->targetActive = false;
					grid[beast->y][beast->x].mat = m_rock;
				}
			}
		}
	}
}



