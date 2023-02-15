#include <stdio.h>
#include "bool.h"


//----------------------------------------------------------------------------------
// globals and definitions
//----------------------------------------------------------------------------------

#define sex_male	0
#define sex_female	1


// all lifeforms start out with starts ranging from 1 to 10
#define MIN_initial_stat 1
#define MAX_initial_stat 10
#define rand_gene() rand_range(MIN_initial_stat,MAX_initial_stat)


// this is the length of the lifeform's name in characters (bytes).
#define NAME_LENGTH 64
// this is the length of a lifeform's species in characters (bytes).
#define SPECIES_LENGTH 64
// this is how many different characters there are for lifeform names and species
#define LIFE_UNIQUE_CHARACTERS 64
// these are all of the characters that can be used in a lifeform's name
char *validLifeChars;


// this is where the files pertaining to the life forms will be stored.
const char *lifeDir;//  = "life\\";
const char *lifeExt;//	 = ".life";
// this is the file that contains all of the data about the current nature.
// this describes the ecosystem.
FILE *ecosys;


//----------------------------------------------------------------------------------
// structures
//----------------------------------------------------------------------------------

// these are genes.
// for every gene, there is the actual gene stat, [0], which describes the lifeform's ability to do that thing.
// there is also a meta stat that describes how inclined the lifeform is to use that ability (out of 100,000)
// for example: attack[0] = 10; attack[1] = 50000;
// that means that the lifeform has a decent attack, and the lifeform has a 50.000% chance of using it
// attack[1] = 100,000 means 100.000% chance of using attack.
// attack[1] = 1,000 means 1.000% chance of using attack.
struct geneData {
	
	// this is the lifeform's proficiency in attack
	int attack[2];
	// this is the lifeform's proficiency in defense
	int defense[2];
	// this is the lifeform's speed
	int speed[2];
	// this is how large the lifeform is
	int size[2];
	// this is how strong the lifeform is
	int strength[2];
	
	// this is how intelligent the lifeform is
	int intelligence[2];
	
	
};

// this is the basic outline of a lifeform.
// lifeforms are assumed to reproduce sexually (two parents)
struct lifeformData {
	
	// this is the lifeform's unique name
	char name[NAME_LENGTH+1];
	
	// this is the lifeform's species string.
	// members of the same species will have the same strings
	// members of closely related species will have similar strings
	// lifeforms that are of completely different species
	char species[NAME_LENGTH+1];
	
	// this tells us the number of evaluations this lifeform has gone through
	int age;
	
	// sex_male or sex_female. 0 or 1
	bool sex;
	
	char parents[2][NAME_LENGTH+1];
	
	
	
	// this is the lifeform's expressed genes (it's phenotype). This is the collection of dominant genes from the parental pair it inherited 
	struct geneData pheno;
	
	// these are the two sets of parental genes that the child inherits.
	// [0] is the paternal set
	// [1] is the maternal set
	struct geneData genesParental[2];
	
	
	
	// this is the file (on the hard disk) that holds the data for your lifeform.
	FILE *dataFile;
	
};


//----------------------------------------------------------------------------------
// function prototypes
//----------------------------------------------------------------------------------

void init_life();
bool print_geneData(FILE *, struct geneData *, int );
bool print_lifeformData(FILE *, struct lifeformData *);

void lifeform_calculate_phenotype(struct lifeformData *);
void lifeform_generate_genes(struct lifeformData *dat);

char get_valid_lifeform_character();
void lifeform_generate_name(struct lifeformData *dat);
void lifeform_generate_species(struct lifeformData *dat);

void *lifeform_generate();
void *lifeform_mate(struct lifeformData *, struct lifeformData *, bool);
bool lifeform_kill(struct lifeformData *dat);
bool lifeform_evaluate(struct lifeformData *dat);







