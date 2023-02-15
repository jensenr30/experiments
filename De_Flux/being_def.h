


///----------------------------------------------------------------------------------------
/// BEINGS
///----------------------------------------------------------------------------------------
#define MAX_NUMBER_OF_BEINGS 0x10000 // 256 max beings. this can be changed later if need be.
#define MAX_BEING_WEAPONS 2 // maximum weapons beings can carry.
#define MAX_BEING_ARMOR 4 // maximum number of armor items beings can wear
#define MAX_BEING_DROPS 4 // maximum number of items the enemy can drop.

///these definiteions index into the being_set surface.
//the first two hex bits specify the x location, the second two hex bits specify the y location.
//because the being_set
#define b_NO_BEING 			0x0000 // there is no being here.
#define b_EOB 				0x0000 // this is basically a flag that says, "hey! this is an invalid being!" It can also be used to denote the end of being in an array of being.
#define b_flame_monster		0x0100
#define b_tree				0x0200



struct being{
	
	// this is the hexID of the being.
	// this is used to index into the being_set image to find the appropriate image.
	int hexID;
	// points to a string
	char *name;
	// points to a string
	char *description;
	
	// this is the type the monster is. use types 
	int type;
	// these are things like i_stun_gun, i_sword, etc...
	int weapons[MAX_BEING_WEAPONS];
	// these are the corresponding uses left for the weapons
	int weaponUses[MAX_BEING_WEAPONS];
	
	// these are just numbers that will index into the itemAtt array.
	int armor[MAX_BEING_ARMOR];
	// these are the corresponding uses left for the armor
	int armorUses[MAX_BEING_ARMOR];
	
	// these are the items that the being will have a chance of dropping
	int drops[MAX_BEING_DROPS];
	// these are the percent chances (out of 100,000) that the being will drop the "drop" corresponding items in the drops[] array upon dying.
	int dropChances[MAX_BEING_DROPS];
	
	// sound effect the being makes.
	Mix_Chunk *soundEffect;
	
}beingAtt[MAX_NUMBER_OF_BEINGS]; // this holds all the attributes of all the beings.



