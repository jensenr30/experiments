
/*
///the inventory version of the dropdown menu.
///this was specilly made for the dropdown menus when you are looking at items in your inventory.
short dropdown_inventory(int x, int y){
	static const char iopts = 4; // different number of options for the items' dropdown menu
	char *ios[iopts]; // item optionStrings
	
	ios[0] = "eat";
	ios[1] = "equip weapon";
	ios[2] = "equip armor";
	ios[3] = "toss";
	
	// items icons' dropdown menu.
	return dropdown(x, y, iopts, ios);
	
	//if something goes wrong, return -1.
	return -1;
}

*/


///this function will generate a dropdown menu for item datitem at x,y.
//equipped = 0: equipped as weapon
//equipped = 1: equipped as armor
//equipped = 2: in inventory (not equipped)
//return value meanings:
//0: eat
//1: unequip
//2: equip weapon
//3: equip armor
//4: throw away
short dropdown_item(struct item *datitem, int x, int y, bool equipped){
	char *ios[MAX_DROPDOWN_OPTIONS];
	int i=0; // used for indexing through the ios array.
	int actionArray[MAX_DROPDOWN_OPTIONS];
	
	if(datitem->health || datitem->attack || datitem->thirst){
		ios[i] = "eat";
		actionArray[i] = 0;
		i++;
	}
	if(equipped == 0 || equipped == 1){
		ios[i] = "unequip";
		actionArray[i] = 1;
		i++;
	}
	if(datitem->attack || datitem->health || datitem->thirst){
		ios[i] = "equip weapon";
		actionArray[i] = 2;
		i++;
	}
	if(datitem->defense){
		ios[i] = "equip armor";
		actionArray[i] = 3;
		i++;
	}
	ios[i] = "toss";
	actionArray[i] = 4;
	i++;
	
	// items icons' dropdown menu.
	i = dropdown(x, y, i, ios);
	//if the return value is valid, return the action.
	if(i >= 0) return actionArray[i];
	//however, if the user did not choose a valid option, return -1.
	return -1;
}




///this handles the inventory.
/// it shows one what one has in one's inventory.
/// it will also show the weapons and armor one has equipped.
/// in addition, it shows one's player avatar and status (health, thirst, xp, etc...)
//returns -1 if it needs to quit.
int inventory(){
	int i,j; // loop variables
	
	
	/// variables for the user-input loop.
	//does the user want to quit the game?
	//bool quit = false;
	//does the user have the alt key pressed?
	//alt shows how many alt keys are pressed. therefore, if you want to check to see if the alt key is pressed, do if(alt).
	bool alt = 0;
	// [1][0] is current mousebutton1 position (UP or DOWN) [1][1] is previous mousebutton1 position (UP or DOWN)
	bool mouse[6][2] = { {UP,UP}, {UP,UP}, {UP,UP}, {UP,UP}, {UP,UP}, {UP,UP} }; // which mouse buttons are pressed down? 1=left mouse button. 2 = middle. 3 = right. 4 = scroll up. 5 = scroll down.
	bool mClicked[6] = { UP, UP, UP, UP, UP, UP}; // use UP and DOWN.
	int x=0,y=0; // coordinates of the mouse pointer.
	// this detects if a change has ocurred since the last run of the inventory code.
	//it is incremented by things that change things.
	//it is decremented once at the end of each cycle of the inventory code.
	bool changeOcurred = 1;
	// this is the number that indexes into the player inventory
	static int invi = 0;
	//this records the previous state of the invi
	static int lastInvi = 0;
	//this is the type of invi the user has selected
	static int inviType = 2;
	//this records the inviType
	static int lastInviType = 2;
	//this is the selected item.
	static struct item *currItem = &emptyItem;
	//this is the rectangle of the currently selected item.
	static SDL_Rect currItemIcon;
	
	
	
	///COLORS HERE
	const static int background	= 0x9a9a9a;
	const static int previewBackground = 0x6a6a6a;
	const static int iconSpaceColor = 0x808080;
	//colors for the health/thirst bars
	const static int healthColor = DF_COLOR_RED;
	const static int thirstColor = DF_COLOR_BLUE;
	const static int outlineColor = 0x000000;
	//sizes
	static short borderThickness = 8;
	static short iconSize = 32;
	static short previewSize = 128;
	
	///variables about the size of objects.
	// how far from the top of the window to where we start displaying the player's inventory (the inventory icons)
	// general purpose rect that data will be shoved into
	SDL_Rect myRect;
	//rectangle used specifically for grabbing the item textures from the item_set_32.
	SDL_Rect itemRect;
	//for the character's avatar
	SDL_Rect avatarSpace;
	avatarSpace.y = avatarSpace.x = borderThickness;
	avatarSpace.w = 128;
	avatarSpace.h = 256;
	//this is the rect for the big 128x128 preview
	SDL_Rect previewSpace;
	previewSpace.x = SCREEN_WIDTH - 2*previewSize - borderThickness;
	previewSpace.y = borderThickness;
	previewSpace.w = previewSize;
	previewSpace.h = previewSize;
	//this is where the name goes
	const char textHeightOffset = -5;
	const char textWidthOffset = 2;
	SDL_Rect nameSpace;
	nameSpace.h = sansFontSize;
	nameSpace.x = previewSpace.x;
	nameSpace.y = previewSpace.y + previewSpace.h + textHeightOffset;
	//the rectangle that is the size of strictly the area for the display of the contents of the inventory. this is where all the 32x32 icons get printed.
	SDL_Rect iconSpace;
	iconSpace.x = previewSpace.x;
	iconSpace.y = nameSpace.y + nameSpace.h;
	char columns = (SCREEN_WIDTH - iconSpace.x)/iconSize;
	char rows = (SCREEN_HEIGHT - iconSpace.y)/iconSize;
	iconSpace.w = columns*iconSize;
	iconSpace.h = rows*iconSize;
	//these are for the health and thirst icons
	SDL_Rect healthIcon, thirstIcon;
	healthIcon.x = avatarSpace.x + avatarSpace.w + borderThickness;
	healthIcon.y = avatarSpace.y;
	healthIcon.w = iconSize;
	healthIcon.h = iconSize;
	thirstIcon.x = healthIcon.x;
	thirstIcon.y = healthIcon.y + healthIcon.h;
	thirstIcon.w = healthIcon.w;
	thirstIcon.h = healthIcon.h;
	//these are for the health and thirst bars
	SDL_Rect healthBar, thirstBar;
	short barWidth = 2*iconSize;
	healthBar.x = healthIcon.x + healthIcon.w;
	healthBar.y = healthIcon.y + healthIcon.h/4;
	healthBar.w = barWidth;
	healthBar.h = healthIcon.h/2;
	thirstBar.x = thirstIcon.x + thirstIcon.w;
	thirstBar.y = thirstIcon.y + thirstIcon.h/4;
	thirstBar.w = barWidth;
	thirstBar.h = healthBar.h;
	//these are for the weapons
	SDL_Rect weaponIcon[MAX_PLAYER_WEAPONS], weaponBar[MAX_PLAYER_WEAPONS];
	//these are for the armor
	SDL_Rect armorIcon[MAX_PLAYER_ARMOR], armorBar[MAX_PLAYER_ARMOR];
	//this initializes the armor and weapon icons / spaces
	for(i=0; i<MAX_PLAYER_WEAPONS; i++){
		weaponIcon[i].x = healthIcon.x;
		weaponIcon[i].y = thirstIcon.y + thirstIcon.h + i*iconSize;
		weaponIcon[i].w = weaponIcon[i].h = iconSize;
		weaponBar[i].x = weaponIcon[i].x + weaponIcon[i].w;
		weaponBar[i].y = weaponIcon[i].y + weaponIcon[i].h/4;
		weaponBar[i].w = barWidth;
		weaponBar[i].h = healthBar.h;
	}
	for(i=0; i<MAX_PLAYER_ARMOR; i++){
		armorIcon[i].x = healthIcon.x;
		armorIcon[i].y = weaponIcon[MAX_PLAYER_WEAPONS-1].y + weaponIcon[MAX_PLAYER_WEAPONS-1].h + i*healthIcon.h;
		armorIcon[i].w = armorIcon[i].h = iconSize;
		armorBar[i].x = armorIcon[i].x + armorIcon[i].w;
		armorBar[i].y = armorIcon[i].y + armorIcon[i].h/4;
		armorBar[i].w = barWidth;
		armorBar[i].h = healthBar.h;
	}
	
	
	//player stuff background space
	short maxTextWidth = 80;
	SDL_Rect playerStuffSpace;
	playerStuffSpace.x = healthIcon.x;
	playerStuffSpace.y = healthIcon.y;
	playerStuffSpace.w = healthIcon.w + healthBar.w + maxTextWidth;
	playerStuffSpace.h = healthIcon.h + thirstIcon.h + iconSize*(MAX_PLAYER_ARMOR + MAX_PLAYER_WEAPONS);
	
	
	//the inventory user-input loop.
	do{
		while(SDL_PollEvent(&event)){
			switch(event.type){
			case SDL_QUIT:
				return -1;
				break;
			case SDL_MOUSEBUTTONDOWN:
				x = event.button.x;
				y = event.button.y;
				if(event.button.button >= 1 && event.button.button <= 5)
					mouse[event.button.button][0] = DOWN;
				break;
			case SDL_MOUSEBUTTONUP:
				x = event.button.x;
				y = event.button.y;
				if(event.button.button >= 1 && event.button.button <= 5)
					mouse[event.button.button][0] = UP;
				break;
			case SDL_MOUSEMOTION:
				x = event.button.x;
				y = event.button.y;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
				case SDLK_e:
					return 0; // leave the inventory if the user so commands.
					break;
				case SDLK_RALT:
					alt++;
					changeOcurred++;
					break;
				case SDLK_LALT:
					alt++;
					break;
				case SDLK_F4:
					if(alt) return -1;
					break;
				case SDLK_w:
					if(invi >= columns){
						invi-=columns;
						changeOcurred++;
					}
					break;
				case SDLK_a:
					if(invi%columns == 0){
						invi += columns -1;
						changeOcurred++;
					}else if(invi > 0){
						invi--;
						changeOcurred++;
					}
					break;
				case SDLK_s:
					if(invi < MAX_PLAYER_ITEMS - columns - 1){
						invi+=columns;
						changeOcurred++;
					}
					break;
				case SDLK_d:
					if(invi%columns == columns-1){
						invi += 1-columns;
						changeOcurred++;
					}else if(invi<MAX_PLAYER_ITEMS-1){
						invi++;
						changeOcurred++;
					}
					break;
				default:
					break;
				}
				break;
			case SDL_KEYUP:
				switch(event.key.keysym.sym){
				case SDLK_RALT:
					alt--;
					break;
				case SDLK_LALT:
					alt--;
					break;
				default:
					break;
				}
			default:
				break;
			}
		}
		
		
		//evaluate if mouse buttons were just clicked
		for(i=1; i<=5; i++){
			if(mouse[i][0] == DOWN && mouse[i][1] == UP) mClicked[i] = DOWN;
			else mClicked[i] = UP;
		}
		
		
		//fill background 
		myRect.x = 0;//borderThickness;
		myRect.y = 0;//borderThickness;
		myRect.w = SCREEN_WIDTH ;//- 2*borderThickness;
		myRect.h = SCREEN_HEIGHT ;//- 2*borderThickness;
		SDL_FillRect(screen, &myRect, background);
		
		//create dark frame behind the user
		SDL_FillRect(screen, &avatarSpace, background - (5*contrast)/4);
		myRect.x = avatarSpace.x;
		myRect.y = avatarSpace.y + (3*avatarSpace.h)/4;
		myRect.w = avatarSpace.w;
		myRect.h = avatarSpace.h/4;
		SDL_FillRect(screen, &myRect, background - (3*contrast)/2);
		
		//apply avatar
		apply_surface(avatarSpace.x, avatarSpace.y, playerAvatarInventory, screen);
		//outline of avatar
		apply_border(screen, &avatarSpace, outlineColor);
		
		//apply background color of the player's stats/stuff
		SDL_FillRect(screen, &playerStuffSpace, previewBackground);
		//apply border to the background of the player's stats/stuff
		apply_border(screen, &playerStuffSpace, 0);
		
		//player health and thirst icons
		apply_item_coor_inventory(ib_health, healthIcon.x, healthIcon.y);
		apply_item_coor_inventory(ib_thirst, thirstIcon.x, thirstIcon.y);
		//apply the outline of the health and thirst bars
		myRect.x = healthBar.x;
		myRect.y = healthBar.y;
		myRect.w = (healthBar.w*player.health)/player.healthFull;
		myRect.h = healthBar.h;
		SDL_FillRect(screen, &myRect, healthColor);
		apply_border(screen, &healthBar, outlineColor);
		//apply the thirst bar
		myRect.x = thirstBar.x;
		myRect.y = thirstBar.y;
		myRect.w = (thirstBar.w*player.thirst)/player.thirstFull;
		myRect.h = thirstBar.h;
		SDL_FillRect(screen, &myRect, thirstColor);
		apply_border(screen, &thirstBar, outlineColor);
		
		
		//print the inventory iconSpace rectangle
		SDL_FillRect(screen, &iconSpace, iconSpaceColor);
		//if the user clicked
		if(mouse[1][0] == DOWN || mClicked[3] == DOWN){
			//if the user pressed inside the icon area
			if(within_rect(x,y,&iconSpace)){
				myRect.w = myRect.h = iconSize;
				for(j=0; j<rows; j++){
					for(i=0; i<columns; i++){
						//find the rectangle where the item is going to be placed
						myRect.x = iconSpace.x  + i*iconSize;
						myRect.y = iconSpace.y + j*iconSize;
						//check to see if the user has pressed the item. if so, select it.
						if(within_rect(x,y,&myRect)){
							// record that a change ocurred
							changeOcurred++;
							// record invi
							invi = j*columns + i;
							//record inventory type
							inviType = 2;
							// only play music if the user clicked on a new item.
							if(invi != lastInvi || inviType != lastInviType)
								Mix_PlayChannel(-1, a_button_click, 0);
							//store current item
							currItem = &player.items[invi];
							//store current rectangle
							copy_rect(&myRect, &currItemIcon);
							// exit loop.
							j = rows; break;
						}
					}
				}
			}
			//check to see if the user clicked on an equipped piece of armor
			for(i=0; i<MAX_PLAYER_ARMOR; i++){
				if(within_rect(x,y,&armorIcon[i])){
					changeOcurred++; // log the change
					invi = i;
					inviType = 1;
					// only play music if the user clicked on a new item.
					if(invi != lastInvi || inviType != lastInviType)
						Mix_PlayChannel(-1, a_button_click, 0);
					currItem = &player.armor[i];
					copy_rect(&armorIcon[i], &currItemIcon);
					break;//done searching
				}
			}
			//check to see if the user clicked on an equipped weapon
			for(i=0; i<MAX_PLAYER_WEAPONS; i++){
				if(within_rect(x,y,&weaponIcon[i])){
					changeOcurred++; // log the change
					invi = i;
					inviType = 0;
					// only play music if the user clicked on a new item.
					if(invi != lastInvi || inviType != lastInviType)
						Mix_PlayChannel(-1, a_button_click, 0);
					currItem = &player.weapons[i];
					copy_rect(&weaponIcon[i], &currItemIcon);
					break;//done searching
				}
			}
		}
		
		//if there is a valid inventory index, print the darkness behind the selected item (behind invi)
		if(invi >= 0)
			SDL_FillRect(screen, &currItemIcon, previewBackground - contrast);
		
		//apply the weapon icons and bars
		for(i=0; i<MAX_PLAYER_WEAPONS; i++){
			//if weapon is valid
			if(player.weapons[i].hexID != i_EOI && player.weapons[i].hexID != i_SKIP){
				apply_item_coor_inventory(player.weapons[i].hexID, weaponIcon[i].x, weaponIcon[i].y);
				myRect.x = weaponBar[i].x;
				myRect.y = weaponBar[i].y;
				myRect.w = (weaponBar[i].w*player.weapons[i].uses)/player.weapons[i].usesFull;
				myRect.h = weaponBar[i].h;
				SDL_FillRect(screen, &myRect, DF_COLOR_GREEN);
				apply_border(screen, &weaponBar[i], 0);
			}
		}
		//apply the armor icons and bars
		for(i=0; i<MAX_PLAYER_ARMOR; i++){
			//if armor is ivalid
			if(player.armor[i].hexID != i_EOI && player.armor[i].hexID != i_SKIP){
				//apply_item_coor_inventory(ib_defense, armorIcon[i].x, armorIcon[i].y);
				apply_item_coor_inventory(player.armor[i].hexID, armorIcon[i].x, armorIcon[i].y);
				myRect.x = armorBar[i].x;
				myRect.y = armorBar[i].y;
				myRect.w = (armorBar[i].w*player.armor[i].uses)/player.armor[i].usesFull;
				myRect.h = armorBar[i].h;
				SDL_FillRect(screen, &myRect, DF_COLOR_YELLOW);
				apply_border(screen, &armorBar[i], 0);
			}
		}
		
		
		//this prints the small icons of your inventory
		int invSpace;// invSpace keeps track of what inventory slot we are on. it goes from 0 to MAX_PLAYER_ITEMS if it can get that far.
		myRect.w = myRect.h = itemRect.w = itemRect.h = iconSize; // 32
		for(j=0, invSpace=0; j<rows; j++){
			for(i=0; i<columns; i++, invSpace++){
				// exit the for loop if you have reached the end of the items
				if(invSpace >= MAX_PLAYER_ITEMS || invSpace >= player.isp){j=rows; break;}
				//continue if you find an empty item
				if(player.items[invSpace].hexID == i_EOI || player.items[invSpace].hexID == i_SKIP) continue;
				//find correct place on the item_set_32 where the hexID item is located.
				itemRect.x = (player.items[invSpace].hexID / 0x100) * iconSize;
				itemRect.y = (player.items[invSpace].hexID % 0x100) * iconSize;
				//find the rectangle where the item is going to be placed
				myRect.x   = iconSpace.x + i*iconSize;
				myRect.y   = iconSpace.y + j*iconSize;
				//apply item texture to the screen
				apply_surface_clips(myRect.x, myRect.y, item_set_32, screen, &itemRect);
			}
		}
		//print outline of the iconspace
		apply_border(screen, &iconSpace, outlineColor);
		
		
		
		//fill preview background (behind the 128x128 size of the selected item
		myRect.x = previewSpace.x;
		myRect.y = previewSpace.y;
		myRect.h = previewSpace.h;
		myRect.w = SCREEN_WIDTH - previewSpace.w - borderThickness;
		SDL_FillRect(screen, &myRect, previewBackground);
		apply_border(screen, &myRect, outlineColor);
		
		//find the icon of the currently selected item on the 128x128 item_set. do this ONLY if there is a valid tile at player.items[invi] AND if it is selected.
		if(currItem->hexID != i_EOI && currItem->hexID != i_SKIP){
			myRect.x = (currItem->hexID / 0x100) * previewSize;
			myRect.y = (currItem->hexID % 0x100) * previewSize;
			myRect.w = myRect.h = previewSize; // width of 128
			//print the 128x128 tile in the upper right hand corner of the inventory gui
			apply_surface_clips(previewSpace.x, previewSpace.y, item_set_128, screen, &myRect);
		}
		
		//apply item name and information only if there is an item selected
		SDL_Color nameColor = {0x00, 0x00, 0x00};
		SDL_Rect itemSelectorClip;
		itemSelectorClip.y = 3*iconSize;
		itemSelectorClip.w = itemSelectorClip.h = iconSize;
		static SDL_Surface *nameText		= NULL;
		static SDL_Surface *healthText		= NULL;
		static SDL_Surface *thirstText		= NULL;
		static SDL_Surface *attackText		= NULL;
		static SDL_Surface *defenseText		= NULL;
		static SDL_Surface *repairText		= NULL;
		static SDL_Surface *playerHealthText		= NULL;
		static SDL_Surface *playerThirstText	= NULL;
		int infoWidth = previewSpace.x + previewSpace.w + iconSize;
		char textString[20];
		char textString2[20];
		short infoTextHeightOffset = 2;
		short secondLineInfo = 2.2*iconSize;
		//print info icons
		if(currItem->health != 0) apply_item_coor_inventory(ib_health, previewSpace.x + previewSpace.w, borderThickness + 0*iconSize);
		if(currItem->thirst != 0) apply_item_coor_inventory(ib_thirst, previewSpace.x + previewSpace.w, borderThickness + 1*iconSize);
		if(currItem->attack != 0) apply_item_coor_inventory(ib_attack, previewSpace.x + previewSpace.w, borderThickness + 2*iconSize);
		if(currItem->defense !=0) apply_item_coor_inventory(ib_defense,previewSpace.x + previewSpace.w, borderThickness + 3*iconSize);
		if(currItem->repair != 0) apply_item_coor_inventory(ib_repair, previewSpace.x + previewSpace.w + secondLineInfo, borderThickness + 0*iconSize);
		
		//inventory stuff
		if(invi >= 0 && invi < MAX_PLAYER_ITEMS && currItem->hexID != i_EOI && currItem->hexID != i_SKIP){
			//only re-render text if a different item has been selected.
			if(changeOcurred){
				//item info
				nameText = TTF_RenderText_Blended(sansFont2, currItem->name, nameColor);
				itoa(currItem->health,  textString, 10);
				healthText  = TTF_RenderText_Blended(sansFont2, textString, nameColor);
				itoa(currItem->thirst,  textString, 10);
				thirstText  = TTF_RenderText_Blended(sansFont2, textString, nameColor);
				itoa(currItem->attack,  textString, 10);
				attackText  = TTF_RenderText_Blended(sansFont2, textString, nameColor);
				itoa(currItem->defense, textString, 10);
				defenseText = TTF_RenderText_Blended(sansFont2, textString, nameColor);
				itoa(currItem->repair, textString, 10);
				repairText = TTF_RenderText_Blended(sansFont2, textString, nameColor);
			}
			//apply item name
			apply_surface(nameSpace.x, nameSpace.y, nameText, screen);
			//apply the info of the item
			if(currItem->health != 0) apply_surface(infoWidth, borderThickness + 0*iconSize + infoTextHeightOffset, healthText,  screen);
			if(currItem->thirst != 0) apply_surface(infoWidth, borderThickness + 1*iconSize + infoTextHeightOffset, thirstText,  screen);
			if(currItem->attack != 0) apply_surface(infoWidth, borderThickness + 2*iconSize + infoTextHeightOffset, attackText,  screen);
			if(currItem->defense !=0) apply_surface(infoWidth, borderThickness + 3*iconSize + infoTextHeightOffset, defenseText, screen);
			if(currItem->repair != 0) apply_surface(infoWidth+ secondLineInfo, borderThickness + 0*iconSize + infoTextHeightOffset, repairText, screen);
		}
		
		//player stuff
		if(changeOcurred){
			//player health and thirst
			itoa(player.health, textString, 10);
			itoa(player.healthFull, textString2, 10);
			strcat(textString, "/");
			strcat(textString, textString2);
			playerHealthText = TTF_RenderText_Blended(sansFont2, textString, nameColor);
			itoa(player.thirst, textString, 10);
			itoa(player.thirstFull, textString2, 10);
			strcat(textString, "/");
			strcat(textString, textString2);
			playerThirstText = TTF_RenderText_Blended(sansFont2, textString, nameColor);
		}
		//player health and thirst text
		apply_surface(healthBar.x+healthBar.w+textWidthOffset, healthBar.y+textHeightOffset, playerHealthText, screen);
		apply_surface(thirstBar.x+thirstBar.w+textWidthOffset, thirstBar.y+textHeightOffset, playerThirstText, screen);
		
		
		
		
		SDL_Flip(screen);
		
		//dropdown menu for the selected item.
		if(currItem->hexID != i_EOI && currItem->hexID != i_SKIP && mouse[3][0] == DOWN){
			// used for storing the return value of the dropdown menu for items.
			int invret;
			invret = dropdown_item(currItem, x, y, inviType);
			mouse[3][0] = UP;
			mouse[3][1] = UP;
			switch(invret){
			case 0: // eat
				item_eat(currItem); // eat the item
				changeOcurred++;
				break;
			case 1: // unequip
				if(add_item(currItem->hexID)){
					item_erase(currItem);
					changeOcurred++;
				}
				break;
			case 2: // equip weapon
				// if you successfully equip the item as a weapon, then a change ocurred.
				changeOcurred += item_equip(0, currItem);
				break;
			case 3: // equip armor
				// if you successfully equip the item as armor, then a change ocurred.
				changeOcurred += item_equip(1, currItem);
				break;
			case 4: // toss
				item_erase(currItem);
				changeOcurred++;
				break;
			}
		}
		
		//old mouse states equal new
		for(i=1; i<=5; i++)
			mouse[i][1] = mouse[i][0];
		 // reset change
		if(changeOcurred > 0) changeOcurred--; else changeOcurred = 0;
		// record lastInvi
		lastInvi = invi;
		//record lastInviType
		lastInviType = inviType;
	}while(1);
	
	// return from whence you came.
	return 0; // normal exit. nothing to see here.
}



