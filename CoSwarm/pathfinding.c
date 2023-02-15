#include "pathfinding.h"
#include "bool.h"
#include "materials_and_cells.h"

// returns if the material is walkable or not on cell [x][y]
bool is_cell_walkable(int x, int y){
	if(grid[y][x].mat == m_earth) return true;
	else return false;
}

// x1,y1 is the current point
// x2,y2 is the goal point
// xn and yn are the next points to variables (external variables not locally in this function. they would be either globals or locals in another function)
// returns whether there are any valid moves
bool best_next_step(int x1, int y1, int x2, int y2, int *xdiff, int *ydiff){
	int xd,yd;
	xd=x2-x1;
	yd=y2-y1;
	if(xd!=0) xd/=abs(xd);	// xd is now equal to either -1, 0, or 1
	if(yd!=0) yd/=abs(yd);	// yd is now equal to either -1, 0, or 1
	if(is_cell_walkable(x1+xd,y1+yd)){
		*xdiff = xd;
		*ydiff = yd;
		return true;
	}
	else if(xd==0){
		
	}
	else if(yd==0){
		
	}
	return false;
}

// the purpose of this pathfinding function is to simply prove a concept
bool pathfind(int x1, int y1, int x2, int y2){
	struct pathStepData steps[MAX_PATH_STEPS];
	struct pathStepData ends[MAX_PATH_STEPS];
	
	int stepsTaken=0;
	int xd, yd;	// the difference between the current point and the next one
	// the first step
	steps[0].x = x1;
	steps[0].y = y1;
	steps[0].prev = NULL;
	
	while(1){
		best_next_step(steps[stepsTaken].x, steps[stepsTaken].y, x2, y2, &xd, &yd);
		
	}
	return true;
}
