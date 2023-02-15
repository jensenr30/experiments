#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "rand.h"
#include "life.h"
#include "stats.h"



int main(int argc, char *argv[]){
	
	
	
	// for debugging only
	rand_test(100);
	
	
	// random seed based on what time it is.
	sgenrand(time(NULL));
	
	
	// initialize the necessary globals
	init_life();
	init_stats();
	
	
	
	// make a test lifeform
	struct lifeformData *test1, *test2, *child;
	// generate two parents
	test1 = lifeform_generate();
	
	//printf("test1 pointer = %d\n",(int)test1);
	test2 = lifeform_generate();
	//printf("test2 pointer = %d\n",(int)test2);
	child = lifeform_mate(test1, test2, false);
	
	
	
	
	
	FILE *printfile;
	
	printfile = fopen("test1.txt", "w");
	print_lifeformData(printfile, test1);
	//if(test1 != NULL)free(test1);//lifeform_kill(test1);
	fclose(printfile);
	
	printfile = fopen("test2.txt", "w");
	print_lifeformData(printfile, test2);
	//if(test2 != NULL)free(test2);//lifeform_kill(test2);
	fclose(printfile);
	
	printfile = fopen("child.txt", "w");
	print_lifeformData(printfile, child);
	//if(child != NULL)free(child);//lifeform_kill(child);
	fclose(printfile);
	
	/*
	struct lifeformData *genLife = lifeform_generate();
	FILE *printfile;
	printfile = fopen("new.txt", "w");
	print_lifeformData(printfile, genLife);
	fclose(printfile);
	
	free(genLife);
	
	printf("sucess!");
	char dummy;
	scanf("%c",&dummy);
	*/
	
	
	
	// quit
	return 0;
}
