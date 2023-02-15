

#define MAX_PARTY_MEMBERS_FRIENDLY 7
#define MAX_PARTY_MEMBERS_HOSTILE 10
#define MAX_PARTY_MEMBERS_DEPLOYED_FRIENDLY 3
#define MAX_PARTY_MEMBERS_DEPLOYED_HOSTILE 6
#define MAX_PARTY_MEMBERS MAX_PARTY_MEMBERS_HOSTILE
#define MAX_PARTY_MEMBERS_DEPLOYED MAX_PARTY_MEMBERS_DEPLOYED_HOSTILE

/*
//these take care of determining which of the two is bigger. it is fool-proof having these #if statements here.
#if MAX_PARTY_MEMBERS_FRIENDLY > MAX_PARTY_MEMBERS_HOSTILE
const int MAX_PARTY_MEMBERS = MAX_PARTY_MEMBERS_FRIENDLY;
#else
const int MAX_PARTY_MEMBERS = MAX_PARTY_MEMBERS_HOSTILE;
#endif

#if MAX_PARTY_MEMBERS_IN_BATTLE_FRIENDLY > MAX_PARTY_MEMBERS_IN_BATTLE_HOSTILE
const int MAX_PARTY_MEMBERS_IN_BATTE = MAX_PARTY_MEMBERS_IN_BATTLE_FRIENDLY;
#else
const int MAX_PARTY_MEMBERS_IN_BATTE = MAX_PARTY_MEMBERS_IN_BATTLE_HOSTILE;
#endif 
*/


///simple definition here
//pt stands for party type
#define pt_friendly 0
#define pt_hostile 1



/// this is a party. this holds beings and data on your party.
// the player and beings can be "deployed".
// a player/being is said to be "deployed" when they are ready to fight.
// only so many beings/players can fight in a party at one time. (MAX_PARTY_MEMBERS_DEPLOYED)
struct party {
	
	//this keeps track of is the party is hostile or not. it is either pt_friendly or pt_hostile.
	bool partyType;
	
	//this keeps track of if the player is deployed. either true or false
	bool playerDeployed;
	
	//this is an array of beings that are in your party.
	//they help you fight battles.
	struct being beings[MAX_PARTY_MEMBERS];
	
	
	//this keeps track of which beings are deployed (ready to fight)
	int deployed[MAX_PARTY_MEMBERS_DEPLOYED];
	
} playerParty;

