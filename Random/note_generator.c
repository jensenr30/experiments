/* note_generator.c
 * Ryan Jensen
 * 2013-12-4
 * This program generates a list of definitions for tone frequencies and tone enumerations to go along with it.
 * 
 * 
 */



#include <stdio.h>
#include <windows.h>
#include <math.h>

int main(){
	FILE *keys = fopen("keys.h","w");
	if(keys == NULL){
		printf("Error creating keys.h\n");
		system("pause");
		return 0;
	}
	// comment header of the header file
	fprintf(keys, "/* keys.h\n");
	fprintf(keys, " * Ryan Jensen\n");
	fprintf(keys, " * Date:\n");
	fprintf(keys, " * This header file contains definitions for all 88 keys on a traditional piano.\n");
	fprintf(keys, " * The n_A4, n_C2, n_f5, etc... definitions are just for enumeration. They fit into a char data type\n");
	fprintf(keys, " * \n");
	fprintf(keys, " */\n");
	
	fprintf(keys,"\n\n/// KEY ENUMERATION DEFINITIONS\n\n");
	char keyChar = 'A';		// starting point
	int keyNumb = 0;		// starting point
	int i;
	for(i=1; i<=88; i++){
		if(keyChar == 'H') keyChar = 'A';		// increment the note
		if(keyChar == 'C') keyNumb++;			// increment the note number
		fprintf(keys, "#define n_%c%d  %d\n", keyChar, keyNumb, i);
		if(keyChar != 'E' && keyChar != 'B' && i+1 <= 88){	// if the key is one that has a sharp, then print a sharp.
			fprintf(keys, "#define n_%c%ds %d\n", keyChar, keyNumb, ++i);
		}
		keyChar++;
	}
	
	fprintf(keys,"\n\n/// KEY FREQUENCY DEFINITIONS\n\n");
	keyChar = 'A';		// starting point
	keyNumb = 0;		// starting point
	float freq;
	for(i=1; i<=88; i++){
		freq = 440.0 * pow(2.0, ((double)i - 49.0)/12.0 );
		if(keyChar == 'H') keyChar = 'A';		// increment the note
		if(keyChar == 'C') keyNumb++;			// increment the note number
		fprintf(keys, "#define f_%c%d  %f\n", keyChar, keyNumb, freq);
		if(keyChar != 'E' && keyChar != 'B' && i+1 <= 88){	// if the key is one that has a sharp, then print a sharp.
			i++;
			freq = 440.0 * pow(2.0, ((double)i - 49.0)/12.0 );
			fprintf(keys, "#define f_%c%ds %f\n", keyChar, keyNumb, freq);
		}
		keyChar++;
	}
	
	fprintf(keys,"\n\n/// KEY CASES\n\n");
	keyChar = 'A';		// starting point
	keyNumb = 0;		// starting point
	for(i=1; i<=88; i++){
		if(keyChar == 'H') keyChar = 'A';		// increment the note
		if(keyChar == 'C') keyNumb++;			// increment the note number
		fprintf(keys, "\tcase n_%c%d:  return f_%c%d;\n", keyChar, keyNumb, keyChar, keyNumb);
		if(keyChar != 'E' && keyChar != 'B' && i+1 <= 88){	// if the key is one that has a sharp, then print a sharp.
			i++;
			fprintf(keys, "\tcase n_%c%ds: return f_%c%ds;\n", keyChar, keyNumb, keyChar, keyNumb);
		}
		keyChar++;
	}
	
	return 0;
}
