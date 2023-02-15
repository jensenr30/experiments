



///----------------------------------------------------------------------------------------
/// BEINGS
///----------------------------------------------------------------------------------------




///erases the being to wich a pointer has been received.
void being_erase(struct being *datbeing){
	int j;
	datbeing->name = '\0'; // no name
	datbeing->description = '\0'; // no description
	datbeing->hexID = b_EOB; // hex ID is the element of the array that you are in.
	for(j=0; j<MAX_BEING_WEAPONS; j++){ // erase weapons
		datbeing->weapons[j] = i_EOI; // no weapon
		datbeing->weaponUses[j] = 0; // no uses left
	}
	for(j=0; j<MAX_BEING_ARMOR; j++){ // erase armor
		datbeing->armor[j] = i_EOI; // no armor
		datbeing->armorUses[j] = 0; // no uses left
	}
	for(j=0; j<MAX_BEING_DROPS; j++){ // erase drops
		datbeing->drops[j] = i_EOI; // no drop
		datbeing->dropChances[j] = 0; // no chance
	}
	datbeing->soundEffect = NULL;
}

void being_copy(struct being *source, struct being *dest){
	int i;
	dest->hexID = source->hexID;
	dest->name = source->name;
	dest->description = source->description;
	
	dest->type = source->type;
	for(i=0; i<MAX_BEING_WEAPONS; i++){
		dest->weapons[i]    = source->weapons[i];
		dest->weaponUses[i] = source->weaponUses[i];
	}
	for(i=0; i<MAX_BEING_ARMOR; i++){
		dest->armor[i]     = source->armor[i];
		dest->armorUses[i] = source->armorUses[i];
	}
	for(i=0; i<MAX_BEING_DROPS; i++){
		 dest->drops[i]      = source->drops[i];
		dest->dropChances[i] = source->dropChances[i];
	}
	
	dest->soundEffect = source->soundEffect;
	
}



///initilizes all the being attributes.
void init_being_attributes(){
	int i,j;
	for(i=0; i<MAX_NUMBER_OF_BEINGS; i++){
		being_erase(&beingAtt[i]);
		beingAtt[i].hexID = i;
	}
	
	beingAtt[b_flame_monster].name = "Flame Monster";
	beingAtt[b_flame_monster].description = "Upwards of 450 degrees celcius! That is hot enough to melt solder!";
	beingAtt[b_flame_monster].weapons[0] = i_fireball;
	beingAtt[b_flame_monster].type = ty_fire;
	beingAtt[b_flame_monster].soundEffect = a_blast;
	beingAtt[b_flame_monster].drops[0] = i_fireball;
	beingAtt[b_flame_monster].dropChances[0] = 2000; // 2% chance
	
	
	//check to see if any weapons/armor were declared
	//this makes sure that if there are any enemies with weapons/armor, you make the uses match the default (full) number of uses.
	for(i=0; i<MAX_NUMBER_OF_BEINGS; i++){
		for(j=0; j<MAX_BEING_WEAPONS; j++){ // erase weapons
			if(beingAtt[i].weapons[j] != b_EOB && beingAtt[i].weaponUses == 0) beingAtt[i].weaponUses[j] = itemAtt[beingAtt[i].weapons[j]].usesFull;
		}
		for(j=0; j<MAX_BEING_ARMOR; j++){ // erase armor
			if(beingAtt[i].armor[j] != b_EOB && beingAtt[i].armorUses == 0) beingAtt[i].armorUses[j] = itemAtt[beingAtt[i].armor[j]].usesFull;
		}
	}
}



