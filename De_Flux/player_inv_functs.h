

/// resets the playerVariables structure that you send to it.
void reset_playerVariables(struct playerVariables *datPlayer){ 
	
	// reset name
	strcpy(datPlayer->name, "BittenChad");
	
	
	//set coordinates to 0
	datPlayer->x = datPlayer->y = 0;
	// the speed at which the player moves
	datPlayer->speed = DEFAULT_PLAYER_SPEED;
	
	// the default health for a player.
	datPlayer->healthFull = DEFAULT_PLAYER_HEALTH*2; datPlayer->health = DEFAULT_PLAYER_HEALTH;
	// default player thirst
	datPlayer->thirstFull = DEFAULT_PLAYER_THIRST*3; datPlayer->thirst = DEFAULT_PLAYER_THIRST;
	
	// blank items
	int i; for(i = 0; i < MAX_PLAYER_ITEMS; i++) item_erase(&datPlayer->items[i]);
	// set item stack pointer to 0
	datPlayer->isp = 0;
	//blank weapons
	for(i=0; i<MAX_PLAYER_WEAPONS; i++) item_erase(&datPlayer->weapons[i]);
	//blank armor
	for(i=0; i<MAX_PLAYER_ARMOR; i++) item_erase(&datPlayer->armor[i]);
}


///adds an item to the player's inventory
/// returns 1 on success. returns 0 if it failed.
int add_item(int itemValue){
	// if the player has too many items, tell the player to drop something else
	if(player.isp >= MAX_PLAYER_ITEMS){
		handle_error(10, "Too many items. Make room by tossing or eating something.");
		return 0;
	}
	int i;
	for(i=0; i<MAX_PLAYER_ITEMS; i++){
		if(player.items[i].hexID == i_EOI || player.items[i].hexID == i_SKIP){
			// copy that item.
			item_copy(&itemAtt[itemValue], &player.items[i]);
			// increment the item stack poitner if need be.
			if(i == player.isp)player.isp++;
			return 1;
		}
	}
	return 0;
}



void item_eat(struct item *datitem){
	if(datitem->health == 0 && datitem->attack == 0) return;
	//add to player health.
	player.health += datitem->health;
	//subtract the item's attack*3 from the player's health.
	player.health -= 3 * datitem->attack;
	//check to see if the player health is too high
	if(player.health > player.healthFull) player.health = player.healthFull;
	//check to see if the player health is too low
	if(player.health < 0) player.health = 0;
	
	//take away one use of the item.
	datitem->uses--;
	//if there are no uses left of the item, delete it.
	if(datitem->uses == 0) item_erase(datitem);
}


///returns 1 upon sucessfully equipping weapon. returns 0 upon unsuccessful equip.
//equip as weapon:	weaponArmor = 0
//equip as armor:	weaponArmor = 1
int item_equip(int weaponArmor, struct item *datitem){
	bool success = false;
	int i; //looping variable
	//weapon
	if(weaponArmor == 0){
		for(i=0; i<MAX_PLAYER_WEAPONS; i++){
			//if the weapon spot is empty
			if(player.weapons[i].hexID == i_EOI || player.weapons[i].hexID == i_SKIP){
				//play music
				//Mix_PlayChannel(-1, a_equip_weapon, 0);
				//copy item into weapon slot [i]
				item_copy(datitem, &player.weapons[i]);
				//erase original item
				item_erase(datitem);
				//leave for loop.
				break;
			}
		}
	}
	//armor
	else if(weaponArmor == 1){
		for(i=0; i<MAX_PLAYER_ARMOR; i++){
			//if the weapon spot is empty
			if(player.armor[i].hexID == i_EOI || player.armor[i].hexID == i_SKIP){
				//play music
				//Mix_PlayChannel(-1, a_equip_armor, 0);
				//copy item into weapon slot [i]
				item_copy(datitem, &player.armor[i]);
				//erase original item
				item_erase(datitem);
				//leave for loop.
				break;
			}
		}
	}
	return success;
}







