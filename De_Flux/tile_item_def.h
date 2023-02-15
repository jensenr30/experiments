///----------------------------------------------------------------------------------------
/// TILES
///----------------------------------------------------------------------------------------


/// standard tile definition format:
/// #define t_

//SPECIAL TILES IN ALL CAPS
#define t_EOT					0x0000 // end of the tiles
#define t_SKIP					0x0001 // skip a tile in a map
#define t_SPAWN					0x0002 // the palce where a player will spawn by default
//standard stuff
#define t_dirt					0x0100
//stone and stone quarter blocks
#define t_stone					0x0200
#define t_stone_up_right		0x0a00
#define t_stone_down_right		0x0b00
#define t_stone_down_left		0x0c00
#define t_stone_up_left			0x0d00
//portals
#define t_portal_green			0x0300
#define t_portal_red			0x0400
//boxes and chests
#define t_box_closed			0x0101
#define t_box_opened			0x0201
#define t_chestClosed			0x0301
#define t_chestOpenEmpty		0x0401
#define t_chestOpenGold			0x0501
//studded & studded quarter blocks
#define t_studded				0x0500
#define t_studded_up_right		0x0600
#define t_studded_down_right	0x0700
#define t_studded_down_left		0x0800
#define t_studded_up_left		0x0900
// bridges & bridge psots
#define t_bridgeHoriz				0x0601
#define t_bridgeVert				0x0701
#define t_bridgePostsUp				0x0801
#define t_bridgePostsLeft			0x0901
#define t_bridgePostsDown			0x0a01
#define t_bridgePostsRight			0x0b01
#define t_bridgePostsMiddleHoriz	0x0c01
#define t_bridgePostsMiddleVert		0x0d01
//wood floor stuff
#define t_wood				0x0203
#define t_wood_bottom		0x0204
#define t_wood_top			0x0202
#define t_wood_right		0x0303
#define t_wood_right_top	0x0302
#define t_wood_right_bottom	0x0304
#define t_wood_left			0x0103
#define t_wood_left_top		0x0102
#define t_wood_left_bottom	0x0104

//darkbrick stuffs
#define t_darkbrick					0x0503
#define t_darkbrick_top				0x0502
#define t_darkbrick_bottom			0x0504
#define t_darkbrick_right			0x0603
#define t_darkbrick_right_top		0x0602
#define t_darkbrick_right_bottom	0x0604
#define t_darkbrick_left			0x0403
#define t_darkbrick_left_top		0x0402
#define t_darkbrick_left_bottom		0x0404



struct tile {
	//walkOn: 0 = cannot walk on. 1 = can walk on. 2 = impartial. 2 doesn't affect whether or not you can walk on it.
	char walkOn;
} tileAtt[MAX_NUMBER_OF_TILES]; // this holds all of the tile attributes that will be used in the game.




///----------------------------------------------------------------------------------------
/// ITEMS
///----------------------------------------------------------------------------------------


#define NUMBER_OF_TYPES 30
#define MAX_ITEM_TYPE_DYNAMICS 6 // this is how many advantages one type may have over another
///different types of weapons/amor
#define ty_none 0		//this is basically a flag that says that the weapon type has no advantages against any armor type.
#define ty_fire 1
#define ty_electric 2
#define ty_gun 3
#define ty_knife 4
#define ty_cloth 5
#define ty_plant 7
#define ty_water 8

struct itemType{
	// specifying type is required for both weapons and armor
	short type; // the type of the item. i.e. ty_none, ty_electric, etc...
	
	// this array holds the types of armor that this weapon is good against.
	// the first elements [i][0] are for the type of the armor you are attacking.
	// the second elements [i][1] are for the percentage scaling of your attack.
	// this array is only necessary for weapons.
	// example weapon:
		// type = ty_electric;
		// effAgainst[0][0] = ty_water;
		// effAgainst[0][1] = 150;
		// effAgainst[1][0] = ty_cloth;
		// effAgainst[1][1] = 67;
		// effAgainst[2][0] = ty_reflector;
		// effAgainst[2][1] = -100;
	// so your weapon is an electric type.
	// it will do 150% its normal damage on water type armor (pretty effective)
	// it will do 67% its normal damage on cloth type armor  (not that effective)
	// it will do -100% its nroaml damage on reflector type armor. (your attack hurts you)
	/// effAgainst is only applicable TO WEAPONS!!
	//  Armor does not have effAgainst.
	//  it just has a type and possibly a sound effect.
	//  But it doesn't have any effAgainst.
	//  All the of the type-on-type advantages are described in the weapons' attributes.
	short effAgainst[MAX_ITEM_TYPE_DYNAMICS][2];
	
	Mix_Chunk *soundEffect; // this is the sound effect that plays when
	
	
}itemTypeAtt[NUMBER_OF_TYPES];





/// standard item definition format:  #define i_			0xXXXX
//the hexadecimal number you assign an item will tell De_flux where to look on the item_set.
//it is important that you choose your number correctly or for the graphics you may get the wrong item, or no item at all.

//SPECIAL ITEMS IN CAPS
#define i_EOI			0x0000
#define i_SKIP			0x0001
#define i_UNKNOWN		0x0002
//GAK
#define i_GAK_blue		0x0100
#define i_GAK_orange	0x0200
#define i_GAK_green		0x0300
#define i_GAK_yellow	0x0400
#define i_GAK_pink		0x0500
//misc crap
#define i_scroll			0x0600
#define i_bananas			0x0700
#define i_laptop_SWAG		0x0800
#define i_laptop_twilight	0x0900
#define i_dat_cereal_bawx	0x0701
#define i_cereal_bawx		0x0701 // this is the same item as before. I simply added two definitions for sake of convenience
//weapons
#define i_stun_gun			0x0a00
#define i_fireball			0x0b00
//computer
#define i_computer_motherboard	0x0101
#define i_computer_tower		0x0201
#define i_computer_monitor		0x0301
#define i_computer_keyboard		0x0401
#define i_computer_mouse		0x0501
#define i_computer_hard_drive	0x0601
#define i_computer_processor	0x0102
#define i_computer_RAM			0x0202
#define i_computer_power_supply	0x0302
#define i_computer_power_cable	0x0402
#define i_computer_SATA_cable	0x0502
#define i_computer_DVD_drive	0x0602
//buttons (these are not items. they are only included here because of convenience
// ib_ for item buttons
#define ib_empty	0x0003
#define ib_health	0x0103
#define ib_thirst	0x0203
#define ib_attack	0x0303
#define ib_defense	0x0403
#define ib_repair	0x0503
#define ib_health_alone		0x0104
#define ib_thirst_alone		0x0204
#define ib_attack_alone		0x0304
#define ib_defense_alone	0x0404
#define ib_repair_alone		0x0504



struct item {
	// the type of item it is. WEAPON, ARMOR, CONSUME, TOOL, etc...
	//short type; // possibly not needed

	//the hexadecimal ID of the item (as listed above). these values are auto filled in in the init_item_attributes() function.
	int hexID;
	// the name of the item.
	char *name;
	//this holds a description of the item. this is a single string. but make the string a few sentences at most.
	char *description;

	// how much damage you do other beings?
	short attack;
	// how much damage can the armor protect against
	short defense;
	//how many times per fight-cycle can you attack with this weapon?
	// 16 is the default speed. that is medium speed. 32 is double speed. 8 is half speed. etc...
	short speed;
	//what type of weapon/armor is this?
	int type;
	// how many uses does the item have left?
	short uses;
	//how many uses does the item have by default?
	short usesFull;
	// how many uses will the item repair of another item?
	short repair;

	// how much will the item heal the user when it is used on the user?
	short health;
	// how much thirst will this item quench when used on the player?
	short thirst;


} itemAtt[MAX_NUMBER_OF_ITEMS]; // this holds all of the tile attributes that will be used in the game.

struct item emptyItem; // this is always empty. I can point to it with other things to keep things safe.



