

///----------------------------------------------------------------------------------------
/// TILES
///----------------------------------------------------------------------------------------

void init_tile_attributes()
{
	int i;
	for(i = 0; i < MAX_NUMBER_OF_TILES; i++)
		tileAtt[i].walkOn = 0; // cannot walk on tiles by default.

	// walkOn:      0 = cannot walk. 1 = can walk. 2 = impartial (doesn't contribute you walking on the grid space).
//special
	tileAtt[t_EOT].walkOn  = 0;
	tileAtt[t_SKIP].walkOn = 1;
	tileAtt[t_SPAWN].walkOn = 1;
//standard
	tileAtt[t_dirt].walkOn = 1; // dirt
	tileAtt[t_stone].walkOn = 0; // stonetileAtt[t_SPAWN].walkOn = 1; // you should never actually have a spawn tile in your map.
	tileAtt[t_studded].walkOn = 1; // studded
//standard quarter blocks
	tileAtt[t_stone_up_right].walkOn =		2; // stone quarter blocks
	tileAtt[t_stone_down_right].walkOn =	2;
	tileAtt[t_stone_down_left].walkOn =		2;
	tileAtt[t_stone_up_left].walkOn =		2;
	tileAtt[t_studded_up_right].walkOn =	2; // studded quarter blocks
	tileAtt[t_studded_down_right].walkOn =	2;
	tileAtt[t_studded_down_left].walkOn =	2;
	tileAtt[t_studded_up_left].walkOn =		2;
//portals
	tileAtt[t_portal_green].walkOn = 1; // green portal
	tileAtt[t_portal_red].walkOn = 1; // red portal
//boxes and chests
	tileAtt[t_chestClosed].walkOn = 0;
	tileAtt[t_chestOpenEmpty].walkOn = 0;
	tileAtt[t_chestOpenGold].walkOn = 0;
//bridge stuff
	tileAtt[t_bridgeHoriz].walkOn = 1;
	tileAtt[t_bridgeVert].walkOn = 1;
	tileAtt[t_bridgePostsUp].walkOn = 2;
	tileAtt[t_bridgePostsLeft].walkOn = 2;
	tileAtt[t_bridgePostsDown].walkOn = 2;
	tileAtt[t_bridgePostsRight].walkOn = 2;
	tileAtt[t_bridgePostsMiddleHoriz].walkOn = 2;
	tileAtt[t_bridgePostsMiddleVert].walkOn = 2;

	//wood stuffs
	tileAtt[t_wood].walkOn = 1;
	tileAtt[t_wood_top].walkOn = 2;
	tileAtt[t_wood_bottom].walkOn = 2;
	tileAtt[t_wood_right].walkOn = 2;
	tileAtt[t_wood_right_top].walkOn = 2;
	tileAtt[t_wood_right_bottom].walkOn = 2;
	tileAtt[t_wood_left].walkOn = 2;
	tileAtt[t_wood_left_top].walkOn = 2;
	tileAtt[t_wood_left_bottom].walkOn = 2;

	//darkbrick stuffs
	tileAtt[t_darkbrick].walkOn = 1;
	tileAtt[t_darkbrick_top].walkOn = 2;
	tileAtt[t_darkbrick_bottom].walkOn = 2;
	tileAtt[t_darkbrick_right].walkOn = 2;
	tileAtt[t_darkbrick_right_top].walkOn = 2;
	tileAtt[t_darkbrick_right_bottom].walkOn = 2;
	tileAtt[t_darkbrick_left].walkOn = 2;
	tileAtt[t_darkbrick_left_top].walkOn = 2;
	tileAtt[t_darkbrick_left_bottom].walkOn = 2;
}


///----------------------------------------------------------------------------------------
/// ITEMS
///----------------------------------------------------------------------------------------


///sets the item type to default (ty_none)


void item_eraseType(struct itemType *dat){
	//set normal type
	dat->type = ty_none;

	int i;
	for(i=0; i<MAX_ITEM_TYPE_DYNAMICS; i++){
		dat->effAgainst[i][0] = ty_none; // effective against no armor.
		dat->effAgainst[i][1] = 100; // does normal damage
	}
	dat->soundEffect = NULL; // no sound effect. maybe change this to a general sound effect? like a punch?
}


///copies itemType from one to another.
void item_copyType(struct itemType *source, struct itemType *dest){

	//copy type
	dest->type = source->type;

	int i;
	//copy the weapon-armor dynamics of the items
	for(i=0; i<MAX_ITEM_TYPE_DYNAMICS; i++){
		dest->effAgainst[i][0] = source->effAgainst[i][0];
		dest->effAgainst[i][1] = source->effAgainst[i][1];
	}
	//copy sound effect
	dest->soundEffect = source->soundEffect;
}



///copies the contents of one item struct into another item struct
void item_copy(struct item *sourceitem, struct item *destitem){

	//metadata
	destitem->hexID				= sourceitem->hexID;
	destitem->name				= sourceitem->name;
	destitem->description		= sourceitem->description;

	//weapon/armor stuff
	destitem->attack			= sourceitem->attack;
	destitem->defense			= sourceitem->defense;
	destitem->speed				= sourceitem->speed;
	destitem->type				= sourceitem->type;
	destitem->uses				= sourceitem->uses;
	destitem->usesFull			= sourceitem->usesFull;
	destitem->repair			= sourceitem->repair;

	//affect player stats
	destitem->health			= sourceitem->health;
	destitem->thirst			= sourceitem->thirst;
}


///erases the item to which a pointer has been received.
void item_erase(struct item *datitem){
	datitem->hexID = i_EOI;
	datitem->name = "ERROR!"; // by default, it points to this error string.
	datitem->description = "ERROR! Undefined Notes!"; // by default, it points to this error string.

	datitem->attack = 0; // items will not aid in attack by default.
	datitem->defense = 0; // items offer no defensive advantage by default
	datitem->speed = 16; // average speed
	datitem->type = ty_none; // no type. default. normal.
	datitem->uses = 1; // by default, items have one use left.
	datitem->usesFull = 1; // by default, items can be used once before they break.
	datitem->repair = 0; // by default, items cannot add uses to other items.

	datitem->health = 0; // gives no health when consumed
	datitem->thirst = 0; // quenches no thirst when comsumed
}



///initializes all of the itemTypeAtt[] elements.
void init_itemType_attributes(){
	int i;
	//set all the defaults of the itemType attributes to all item types
	for(i=0; i<NUMBER_OF_TYPES; i++){
		item_eraseType(&itemTypeAtt[i]);
	}
	
	itemTypeAtt[ty_fire].effAgainst[0][0] = ty_water; // not effective against water
	itemTypeAtt[ty_fire].effAgainst[0][1] = 50;  // 50% effective
	itemTypeAtt[ty_fire].effAgainst[1][0] = ty_plant; // very effective against plant
	itemTypeAtt[ty_fire].effAgainst[1][1] = 200; // 200% effective
	itemTypeAtt[ty_fire].soundEffect = a_blast;
}




///initializes all the item attributes.
void init_item_attributes(){
	int i;	
	//set the defaults item attributes to all items
	for(i=0; i<MAX_NUMBER_OF_ITEMS; i++){
		item_erase(&itemAtt[i]);
		itemAtt[i].hexID = i;
	}
	
	
	
	item_erase(&emptyItem); // keep the empty item empty.
	
	//now we can specify details of the items here.

	itemAtt[i_EOI].name = "EOI.EndOfItems";
	itemAtt[i_EOI].description = "If you are seeing this, then there is an error. Please take a screenshot of this error and send it to JensenR30@Gmail.com";

	itemAtt[i_SKIP].name = "SKIP";
	itemAtt[i_SKIP].description = "If you are seeing this, then there is an error. Please take a screenshot of this error and send it to JensenR30@Gmail.com";

	itemAtt[i_UNKNOWN].name = "Unknown Item";
	itemAtt[i_UNKNOWN].description = "You do not yet know what this item is.";



	itemAtt[i_GAK_blue].name = "Blue GAK";
	itemAtt[i_GAK_blue].description = "What is Nickelodean GAK!?";
	itemAtt[i_GAK_blue].repair = 16;

	itemAtt[i_GAK_orange].name = "Orange GAK";
	itemAtt[i_GAK_orange].description = "Smoke GAK every day!";
	itemAtt[i_GAK_orange].repair = 2*itemAtt[i_GAK_blue].repair;

	itemAtt[i_GAK_green].name = "Green GAK";
	itemAtt[i_GAK_green].description = "GAK Pack sold separately.";
	itemAtt[i_GAK_green].repair = 4*itemAtt[i_GAK_blue].repair;

	itemAtt[i_GAK_yellow].name = "Yellow GAK";
	itemAtt[i_GAK_yellow].description = "Squashable, Squeezable!";
	itemAtt[i_GAK_yellow].repair = 8*itemAtt[i_GAK_blue].repair;

	itemAtt[i_GAK_pink].name = "Pink GAK";
	itemAtt[i_GAK_pink].description = "GAK ATTACK!";
	itemAtt[i_GAK_pink].repair = 16*itemAtt[i_GAK_blue].repair;

	itemAtt[i_bananas].name = "Bananas";
	itemAtt[i_bananas].health = 25;

	itemAtt[i_scroll].name = "Letter to Princess Celestia";

	itemAtt[i_laptop_SWAG].name = "Laptop With Swag";

	itemAtt[i_laptop_twilight].name = "Laptop With Ponies";



	itemAtt[i_computer_motherboard].name = "Motherboard";
	itemAtt[i_computer_motherboard].description = "An Ultra Durable Gigabyte 970A-UD3 desktop motherboard. ATX model. It runs AM3+ socket processors. SATA 3.0, USB3.0, and USB2.0";

	itemAtt[i_computer_tower].name = "Computer Case";
	itemAtt[i_computer_tower].description = "A standard black desktop computer tower. Fits ATX Motherboards";

	itemAtt[i_computer_monitor].name = "Monitor";
	itemAtt[i_computer_monitor].description = "An LCD 1080p monitor. It has a refresh rate of 60Hz and Contrast ratio of 1:1000000.";

	itemAtt[i_computer_keyboard].name = "Keyboard";
	itemAtt[i_computer_keyboard].description = "Run-of-the-mill Dell keyboard. It's low quality is priceless.";

	itemAtt[i_computer_mouse].name = "Mouse";
	itemAtt[i_computer_mouse].description = "Standard wired optical mouse.";

	itemAtt[i_computer_hard_drive].name = "Hard Disk";
	itemAtt[i_computer_hard_drive].description = "1.5 TB Western Digital hard disk drive. SATA 3.0 interface.";

	itemAtt[i_computer_processor].name = "Processor";
	itemAtt[i_computer_processor].description = "Quad-Core 3.6 GHz FX Processor. AM3+ socket.";

	itemAtt[i_computer_RAM].name = "RAM";
	itemAtt[i_computer_RAM].description = "16 GB DDR3 ram.";

	itemAtt[i_computer_power_supply].name = "Power Supply";
	itemAtt[i_computer_power_supply].description = "ATX power supply unit. 500 watts.";

	itemAtt[i_computer_power_cable].name = "Power Cable";
	itemAtt[i_computer_power_cable].description = "Standard black power supply cable.";

	itemAtt[i_computer_SATA_cable].name = "SATA Cable";
	itemAtt[i_computer_SATA_cable].description = "16' SATA cable.";

	itemAtt[i_computer_DVD_drive].name = "DVD Drive";
	itemAtt[i_computer_DVD_drive].description = "DVD Drive. SATA interface. Standard operation and installation.";

	itemAtt[i_dat_cereal_bawx].name = "Dat Cereal Bawx";
	itemAtt[i_dat_cereal_bawx].description = "EAT DAT CEREAL BAWX.";
	itemAtt[i_dat_cereal_bawx].health = 45;

	itemAtt[i_stun_gun].name = "Stun Gun";
	itemAtt[i_stun_gun].description = "You don't stun-gun a guy who was a GOD DAMN LEGEND.";
	itemAtt[i_stun_gun].attack = 20;
	itemAtt[i_stun_gun].type = ty_knife;
	itemAtt[i_stun_gun].uses = 25;
	itemAtt[i_stun_gun].usesFull = 25;

	itemAtt[i_fireball].name = "Fireball";
	itemAtt[i_fireball].description = "This fireball is ready to dispatch yoru enemies.";
	itemAtt[i_fireball].attack = 15;
	itemAtt[i_fireball].usesFull = itemAtt[i_fireball].uses = 48;
	itemAtt[i_fireball].type = ty_fire;
	
	return;
}




