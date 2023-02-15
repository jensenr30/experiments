#include "materials_and_cells.h"

void mat_erase(struct matData *mat){
	mat->name = NULL;
	mat->desc = NULL;
	mat->color = 0x00ff00ff;					// pink. materials that shouldn't be there are pink by default. this stands out and will draw attentions to any bugs
	mat->solid = false;					// you cannot walk through things by default
}


void init_mats(){
	
	//erase all mats
	int m;
	for(m=0; m<MAX_NUMBER_OF_UNIQUE_MATERIALS; m++){
		mat_erase(&mats[m]);
	}
	
	mats[m_earth].name = "Earth";
	mats[m_earth].desc = "Probably not edible.";
	mats[m_earth].color = 0xff855C33;
	mats[m_earth].solid = true;
	
	mats[m_rock].name = "Rock";
	mats[m_rock].desc = "This is rock. That is all. Thanks for your attention.";
	mats[m_rock].color = 0xff606060;
	mats[m_rock].solid = true;
	
	mats[m_water].name = "Water";
	mats[m_water].desc = "H20";
	mats[m_water].color = 0x4d4dff;
	mats[m_water].solid = false;
	
}







