
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "life.h"

#include "rand.h"

#include "error.h"
#include "bool.h"




void init_life(){
	
	lifeDir = "life\\";
	lifeExt = ".life";
	
	ecosys = fopen("ecosys.txt", "r");
	
	// the valid character in 
	validLifeChars = "-_0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	
}


bool print_geneData(FILE *dest, struct geneData *dat, int indents){
	if(dest == NULL || dat == NULL){
		return false;
	}
	int i;
	for(i=0; i<indents; i++) fprintf(dest,"\t");
	fprintf(dest,"attack[0] = %d\n",dat->attack[0]);
	for(i=0; i<indents; i++) fprintf(dest,"\t");
	fprintf(dest,"attack[1] = %d\n",dat->attack[1]);
	
	for(i=0; i<indents; i++) fprintf(dest,"\t");
	fprintf(dest,"defense[0] = %d\n",dat->defense[0]);
	for(i=0; i<indents; i++) fprintf(dest,"\t");
	fprintf(dest,"defense[1] = %d\n",dat->defense[1]);
	
	for(i=0; i<indents; i++) fprintf(dest,"\t");
	fprintf(dest,"speed[0] = %d\n",dat->speed[0]);
	for(i=0; i<indents; i++) fprintf(dest,"\t");
	fprintf(dest,"speed[1] = %d\n",dat->speed[1]);
	
	for(i=0; i<indents; i++) fprintf(dest,"\t");
	fprintf(dest,"size[0] = %d\n",dat->size[0]);
	for(i=0; i<indents; i++) fprintf(dest,"\t");
	fprintf(dest,"size[1] = %d\n",dat->size[1]);
	
	for(i=0; i<indents; i++) fprintf(dest,"\t");
	fprintf(dest,"strength[0] = %d\n",dat->strength[0]);
	for(i=0; i<indents; i++) fprintf(dest,"\t");
	fprintf(dest,"strength[1] = %d\n",dat->strength[1]);
	
	for(i=0; i<indents; i++) fprintf(dest,"\t");
	fprintf(dest,"intelligence[0] = %d\n",dat->intelligence[0]);
	for(i=0; i<indents; i++) fprintf(dest,"\t");
	fprintf(dest,"intelligence[1] = %d\n",dat->intelligence[1]);
	
	
	// if all went well, return true
	return true;
}

// this will print a lifeform to a file you choose.
bool print_lifeformData(FILE *dest, struct lifeformData *dat){
	if(dest == NULL || dat == NULL){
		return false;
	}
	
	fprintf(dest,"name = %s\n",dat->name);
	fprintf(dest,"species = %s\n",dat->species);
	fprintf(dest,"age = %d\n",dat->age);
	fprintf(dest,"sex = ");
	if(dat->sex == sex_male) fprintf(dest,"male\n");
	else fprintf(dest,"female\n");
	fprintf(dest,"father = %s\n",dat->parents[sex_male]);
	fprintf(dest,"mother = %s\n",dat->parents[sex_female]);
	//fprintf(dest,"name = %s\n"dat->);
	
	fprintf(dest,"\nPhenotype:\n");
	print_geneData(dest,&dat->pheno,1);
	
	fprintf(dest,"\nPaternal Genes:\n");
	print_geneData(dest,&dat->genesParental[sex_male],1);
	
	fprintf(dest,"\nMaternal Genes:\n");
	print_geneData(dest,&dat->genesParental[sex_female],1);
	
	
	
	// if all went well, return true
	return true;
}







/// this calculates the phenotype of a lifeform.
// as of now, the phenotype is randomly generated from one's parental genes.
void lifeform_calculate_phenotype(struct lifeformData *dat){
	int i;
	for(i=0; i<2; i++){
		dat->pheno.attack[i]		= rand_either(dat->genesParental[sex_male].attack[i],		dat->genesParental[sex_female].attack[i]);
		dat->pheno.defense[i]		= rand_either(dat->genesParental[sex_male].defense[i],		dat->genesParental[sex_female].defense[i]);
		dat->pheno.speed[i] 		= rand_either(dat->genesParental[sex_male].speed[i],			dat->genesParental[sex_female].speed[i]);
		dat->pheno.size[i]	 		= rand_either(dat->genesParental[sex_male].size[i],			dat->genesParental[sex_female].size[i]);
		dat->pheno.strength[i] 		= rand_either(dat->genesParental[sex_male].strength[i],		dat->genesParental[sex_female].strength[i]);
		dat->pheno.intelligence[i] 	= rand_either(dat->genesParental[sex_male].intelligence[i],	dat->genesParental[sex_female].intelligence[i]);
	}
}



/// this creates an entirely new set of genes from scratch randomly.
// This function is used just to generate an initial population of lifeforms.
void lifeform_generate_genes(struct lifeformData *dat){
	
	//----------------------------------------------------------------------------------
	// determine genes
	//----------------------------------------------------------------------------------
	int j;
	for(j=0; j<2; j++){
		dat->genesParental[j].attack[0]			= rand_gene();
		dat->genesParental[j].defense[0]		= rand_gene();
		dat->genesParental[j].speed[0]			= rand_gene();
		dat->genesParental[j].size[0]			= rand_gene();
		dat->genesParental[j].strength[0] 		= rand_gene();
		dat->genesParental[j].intelligence[0]	= rand_gene();
		
		dat->genesParental[j].attack[1]			= rand_ht();
		dat->genesParental[j].defense[1]		= rand_ht();
		dat->genesParental[j].speed[1]			= rand_ht();
		dat->genesParental[j].size[1]			= rand_ht();
		dat->genesParental[j].strength[1] 		= rand_ht();
		dat->genesParental[j].intelligence[1]	= rand_ht();
	}
	//----------------------------------------------------------------------------------
	// determine phenotype
	//----------------------------------------------------------------------------------
	lifeform_calculate_phenotype(dat);
}






char get_valid_lifeform_character(){
	/*unsigned int rnumb = genrand();
	unsigned index = rnumb%LIFE_UNIQUE_CHARACTERS;
	char retchar = validLifeChars[index];
	int i = 10;
	i+= 5;
	printf("i = %d",i);
	return retchar;*/
	return validLifeChars[genrand()%LIFE_UNIQUE_CHARACTERS];
}

void lifeform_generate_name(struct lifeformData *dat){
	int i;
	for(i=0; i<NAME_LENGTH; i++){
		dat->name[i] = get_valid_lifeform_character(); // fill up with random characters from validLifeChars
	}
	dat->name[NAME_LENGTH] = '\0'; // terminate with a null character
}

// to generate a species, you use the same process that is used to generate an individuals name.
// this is only used when a new lifeform is generated, NOT birthed through sexual reproduction.
void lifeform_generate_species(struct lifeformData *dat){
	int i;
	for(i=0; i<SPECIES_LENGTH; i++){
		dat->species[i] = get_valid_lifeform_character(); // fill up with random characters from validLifeChars
	}
	dat->species[SPECIES_LENGTH] = '\0'; // terminate with a null character
}



/// this creates a new lifeform. This is NOT sexual reproduction.
// this might be called spontaneous generation.
// This function is used just to generate an initial population of lifeforms.
// this function will allocate the needed memory for the lifeform.
/// REMEMBER to free lifeform data when you are done using the lifeforms with lifeform_kill()
void *lifeform_generate(){
	// allocate memory for the new lifeform.
	struct lifeformData *genLife = malloc(sizeof(struct lifeformData));
	//debugging
	//printf("genLife pointer = %d\n",(int)genLife);
	//printf("sizeof( struct lifeformData ) = %d\n",sizeof(struct lifeformData));
	if(genLife == NULL){
		//debugging
		//printf("genLife pointer is NULL\n");
		handle_error(e_malloc,NULL);
		return NULL;
	}
	
	// generate name
	lifeform_generate_name(genLife);
	
	// generate species
	lifeform_generate_species(genLife);
	
	// generate sex
	genLife->sex = rand_range(sex_male,sex_female);
	
	// age starts at 0
	genLife->age = 0;
	
	// generate random parental genes (as it has no parents, we will emulate the effect of parents on this lifeform's genes)
	lifeform_generate_genes(genLife);
	
	// set blank parents (as the lifeform has no true parents)
	genLife->parents[sex_male][0] = '\0';
	genLife->parents[sex_female][0] = '\0';
	
	// no file is null to begin with
	genLife->dataFile = NULL;
	
	//debugging
	//printf("Returning genLife = %d\n",(int)genLife);
	
	// return a pointer to the newly generated lifeform
	return genLife;
}



/// This is SEXUAL reproduction. NOT spontaneous generation.
// returns a pointer to a sexually produced lifeform.
// father is the dad of the lifeform
// mother is the mom of the lifeform
void *lifeform_mate(struct lifeformData *father, struct lifeformData *mother, bool speciesMix){
	
	//----------------------------------------------------------------------------------
	// allocating memory
	//----------------------------------------------------------------------------------
	
	// allocate memory for new lifeform
	struct lifeformData *newLife = malloc(sizeof(struct lifeformData));
	
	// if you failed to create memory for a lifeform, return a null pointer.
	if(newLife == NULL){
		return NULL;
		handle_error(e_malloc,"Couldn't create new lifeform. malloc() returned NULL");
	}
	
	//----------------------------------------------------------------------------------
	// generate name
	//----------------------------------------------------------------------------------
	
	int nameGetAttempts = 0;
	int maxAttempts = 20;
	
	while(1){
		// get the lifeform a name
		lifeform_generate_name(newLife);
		
		// generate relative lifeform file path
		char path[2*NAME_LENGTH];
		strcpy(path, lifeDir);			// directory
		strcat(path, newLife->name);	// file name
		strcat(path, lifeExt);			// extension
		
		// if the newLife name does not already exist, good. Move on. we have found a good, yet-unused name.
		if(fopen(path, "r") == NULL) break;
		// increment the number of times you have tried to get a name for the newLife
		nameGetAttempts++;
		// if you can't get a name that has not already been used, then quit I guess.
		if(nameGetAttempts >= maxAttempts){
			return NULL;
			handle_error(e_failure_to_find_new_name, NULL);
		}
	}
	
	//----------------------------------------------------------------------------------
	// setting child age and parent's name
	//----------------------------------------------------------------------------------
	newLife->age = 0;
	strcpy(newLife->parents[0], father->name);
	strcpy(newLife->parents[0], mother->name);
	
	//----------------------------------------------------------------------------------
	// pass on species 
	//----------------------------------------------------------------------------------
	
	int i;
	// this picks whether you get your species from your mother or father
	// the child will have EITHER its mother's OR its father's species. There is no mixing.
	if(speciesMix){
		for(i=0; i<NAME_LENGTH; i++){
			if(rand_bool())
				newLife->species[i] = father->species[i];
			else
				newLife->species[i] = mother->species[i];
		}
	}
	// this mixes the species of the mother and father.
	// With this method, the species of the child can be some random mixture of the parent's species string.
	else{
		bool speciesInheritance = rand_bool();
		for(i=0; i<NAME_LENGTH; i++){
			if(speciesInheritance)
				newLife->species[i] = father->species[i];
			else
				newLife->species[i] = mother->species[i];
		}
	}
	newLife->species[SPECIES_LENGTH] = '\0';
	
	/// add a gene mixing function here.
	/// build it to have multiple modes (i.e. random assignment, different gender's pass on specific genes
	/// genes_mix(father, mother, &newLife, gmix_random);
	
	return newLife;
	
	/// THIS IS THE OLD TRAIT DISTRIBUTION SYSTEM THAT WAS PRONE TO ERROR AND SEGMENTATION FAULTS
	/** 
	//----------------------------------------------------------------------------------
	// pass on paternal traits
	//----------------------------------------------------------------------------------
	for(i=0; i*sizeof(int)<sizeof(struct geneData); i+=2*sizeof(int) ){
		// paternal grandfather's traits.
		if(rand_bool()){
			*((&newLife->genesParental[sex_male])+i)   = *((&father->genesParental[sex_male])+i);
			*((&newLife->genesParental[sex_male])+i+1) = *((&father->genesParental[sex_male])+i+1);
		}
		// paternal grandmother's traits.
		else{
			*((&newLife->genesParental[sex_male])+i)   = *((&father->genesParental[sex_female])+i);
			*((&newLife->genesParental[sex_male])+i+1) = *((&father->genesParental[sex_female])+i+1);
		}
	}
	//----------------------------------------------------------------------------------
	// pass on maternal traits
	//----------------------------------------------------------------------------------
	for(i=0; i*sizeof(int)<sizeof(struct geneData); i+=2*sizeof(int) ){
		// maternal grandfather's traits.
		if(rand_bool()){
			*((&newLife->genesParental[sex_female])+i)   = *((&father->genesParental[sex_male])+i);
			*((&newLife->genesParental[sex_female])+i+1) = *((&father->genesParental[sex_male])+i+1);
		}
		// maternal grandmother's traits.
		else{
			*((&newLife->genesParental[sex_female])+i)   = *((&father->genesParental[sex_female])+i);
			*((&newLife->genesParental[sex_female])+i+1) = *((&father->genesParental[sex_female])+i+1);
		}
	}
	// return a pointer to the newly created life.
	return newLife;
	**/
}



// this kills a lifeform
// returns true if the lifeform was valid and was deleted (memory freed)
// returns false if the lifeform was not deleted or was invalid from the start
bool lifeform_kill(struct lifeformData *dat){
	
	if(dat == NULL) return false;
	//----------------------------------------------------------------------------------
	// save lifeform to a genetic record on the hard disk
	//----------------------------------------------------------------------------------
	
	
	
	//----------------------------------------------------------------------------------
	// remove lifeform from memory
	//----------------------------------------------------------------------------------
	free(dat);
	
	return true;
}



// this evaluates what happens to a lifeform and how it handles its situation
bool lifeform_evaluate(struct lifeformData *dat){
	
	return false;
}




