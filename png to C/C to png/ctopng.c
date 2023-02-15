#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//picture data
#include "simon.h"

#define PICTURE_PATH "Gurren Lagann.png"

#define MAX_CORRUPTIONS 500



int main(){
	srand(time(NULL));
	
	int opened = 0;
	int elements = sizeof(simon_png)/sizeof(simon_png[0]);
	int corruptions = 0;
	int i;
	
	
	while(1){
		
		FILE *myfile = fopen(PICTURE_PATH, "wb");
		if(myfile == NULL){
			printf("Failure to create new file");
			return -1;
		}
		
		
		unsigned int index;
		unsigned char data;
		//.unsigned int original[MAX_CORRUPTIONS][2]; // [][0] = index, [][1] = data
		//corruption
		for(i=0; i<corruptions; i++){
			//generate index and corrupt data 
			index = rand()%elements;
			data = rand()%256;
			
			//save original data
			//original[i][0] = index;
			//original[i][1] = simon_png[index];
			
			//corrupt the data.
			simon_png[index] = data;
		}
		
		//write data to file
		fwrite(simon_png, sizeof(simon_png[0]), sizeof(simon_png)/sizeof(simon_png[0]), myfile); 
		//close file
		fclose(myfile);
		if(opened == 0) {system("\"Gurren Lagann.png\""); opened =1;}
		
		/*
		//uncorrupt
		for(i=0; i<corruptions; i++){
			index = original[i][0];
			data = (unsigned char)original[i][1];
			simon_png[index] = data;
		}
		*/
		
		
		
		//wait for user input
		printf("How many corruptions? ");
		scanf("%d", &corruptions);
		
		if(corruptions < 0) break;
		else if(corruptions == 0){
			printf("Original image.\n");
			continue;
		}
		else{
			if(corruptions>=MAX_CORRUPTIONS) corruptions = MAX_CORRUPTIONS-1;
		}
		
		
	}
	
	return 0;
}
