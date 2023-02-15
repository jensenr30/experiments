#include "gen_world.h"
#include "materials_and_cells.h"
#include "rand.h"


// recursive function for generating clusters
void gen_cluster(int x, int y, int prob, float decayFactor, int mat){
	// only change the grid element if the x and y coordinates are inside the grid.
	if(within_grid_elements(x,y)) grid[y][x].mat = mat;
	
	if(rand_ht()<=prob){
		gen_cluster(x-1,y,prob*decayFactor,decayFactor,mat);
	}
	if(rand_ht()<=prob){
		gen_cluster(x+1,y,prob*decayFactor,decayFactor,mat);
	}
	if(rand_ht()<=prob){
		gen_cluster(x,y-1,prob*decayFactor,decayFactor,mat);
	}
	if(rand_ht()<=prob){
		gen_cluster(x,y+1,prob*decayFactor,decayFactor,mat);
	}
}



void gen_world(){
	int i,j;
	// plaster the world with earth
	for(j=0; j<GRID_HEIGHT_ELEMENTS; j++){
		for(i=0; i<GRID_WIDTH_ELEMENTS; i++){
			grid[j][i].mat = m_earth;
		}
	}
	// generate rock clusters randomly
	for(j=0; j<GRID_HEIGHT_ELEMENTS; j++){
		for(i=0; i<GRID_WIDTH_ELEMENTS; i++){
			if( rand_ht()<=gwp_rock_cluster_start ){
				gen_cluster(j, i, gwp_rock_cluster_spread, gwp_rock_cluster_decay, m_rock);
			}
		}
	}
	for(j=0; j<GRID_HEIGHT_ELEMENTS; j++){
		for(i=0; i<GRID_WIDTH_ELEMENTS; i++){
			if(rand_ht() <= gwp_lake_start)
				gen_cluster(i, j, gwp_lake_spread, gwp_lake_decay, m_water);
		}
	}
}
