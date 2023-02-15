




//this describes a tile.  we can set its values to put any tile anwhere on the map.
//this is for MAP USE ONLY.
struct oneTile {
	int x;
	int y;
	unsigned short type;
};
//this describes an item. we can set its values to put any item anywhere on the map.
//this is for MAP USE ONLY.
struct oneItem {
	int x;
	int y;
	unsigned short type;
};

//this structure describes a portal. it tells us where the portal's entrance is and where it's exit is.
struct mapPortal{
	// these are the coordinates that you come from. x=oldCoor[0], y=oldCoor[1]
	int oldCoor[2];
	// these are the coordinates that you go to. x=newCoor[0], y=newCoor[1]
	int newCoor[2];
	// this is the name of the map you go to when you teleport. the map is loaded upon entry into that map.
	// initially undefined.
	char nextMapName[MAX_MAP_NAME_LENGTH];
};

///this is a region in which certain beings can spawn.
struct beingRegion {
	// the size and location of the spawning region
	int x,y,w,h;
	
	// this is the being that can spawn in this area.
	// this is a number that indexes into the beingAtt[] array.
	int being[MAX_PARTY_MEMBERS];
	
	// this is the percent chance that the being will spawn when the player steps on this tile. it is a chance/100000
	// examples:
	// if chance = 5000, there is a 5000/100000 chance (5% chance)
	// if chance = 75000, there is a 75% chance
	// if chance = 50, there is a 0.05% chance (50 milli percents)
	unsigned int chance[];
};


//try to only have a few maps open at a time to conserve memory.
/// this is a map. this has all the necessary information to describe the environment in which the player moves around.
/// this holds tile data, item data, portal data, the name of the map, the spawn location... everything. everything that you need to describe you map is here or goes in here.
struct map{
	// these are portals to other maps. psp is used to keep track of how many portals we have to other maps.
	struct mapPortal portals[MAX_PORTALS_PER_MAP];
	// this is sort of like a tile stack pointer (hence tsp: Tile Stack Pointer)
	// it is normally on the next available spot in the tiles[][] array. to add a tile into this array, simply modify the data and then currentMap.tsp++
	int tsp;
	int isp; // this is like the tile stack pointer but for the items on the map. It will always be at the address of an empty item in the items[] array.
	int psp; // this is the portal stack pointer. It is dynamically kept at an address that is an empty portal.

	// this holds the data for the tiles. this array must end with a t_EOT tile.
	struct oneTile tiles[MAX_TILES_PER_MAP];
	//this holds the data for the items on the map this array must end with a i_EOI item.
	struct oneItem items[MAX_ITEMS_PER_MAP];
	
	// this is the tile that will be the default background tile.
	// this will be displayed everywhere.
	// the tile will not actually be there, but it will show up as the default background tile.
	// set it to t_EOT or t_SKIP to have the background be black.
	// set it to any other tile, e.g. t_stone, to have the background be stone.
	int defaultTile;

	//these are the default spawn coordinates for someone entering the map under normal, non-teleportation conditions.
	int spawnx;
	int spawny;

} currentMap;
