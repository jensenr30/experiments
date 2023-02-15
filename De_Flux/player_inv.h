
/// definitions pertaining to the player's data.
#define MAX_PLAYER_NAME_LENGTH 20
#define MAX_PLAYER_SPEED 30
#define DEFAULT_PLAYER_SPEED  7

#define DEFAULT_PLAYER_HEALTH 60
#define DEFAULT_PLAYER_THIRST 40
#define MAX_PLAYER_ITEMS 120 // 8x12 (8 columns 12 rows) for a 8x12 item icon grid in the inventory.
#define MAX_PLAYER_WEAPONS 2
#define MAX_PLAYER_ARMOR 4



/// this holds all of the player's data.
struct playerVariables {
	//the player's name
	char name[MAX_PLAYER_NAME_LENGTH+1];
	
	int x, y;// player's coordinates on the map
	char direction; // where is the user looking? use UP, DOWN, LEFT, and RIGHT.
	int speed; // how fast the player moves
	
	int health; // player health
	int healthFull; // this value is the full player health. This is the maximum health the player can have (this will change when the player levels up)
	int thirst; // player thirst
	int thirstFull; // this value is the full player thirst. This is the maximum thirst the player can have (this will change when the player levels up)
	
	int isp; // item stack pointer. points to an open inventory space ALWAYS.
	struct item items[MAX_PLAYER_ITEMS]; // the player's item inventory
	struct item weapons[MAX_PLAYER_WEAPONS]; // the player's two weapons. the effects of each add vectorially-ish. sqrt(a^2 + b^2);
	struct item armor[MAX_PLAYER_ARMOR]; // the player's four pieces or armor. the defense of this armor adds normally. a + b + c + d.
	
} player;






