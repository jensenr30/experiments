
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define bool char
#define true  1
#define false 0

#define debug 1


#include "word_functs.h"
int main(void){
	int i,j;
	printf("Choose a file to analyze...\n");
	//load the document to analyze
	FILE *document = choose_file();
	//if the file was unsucessfully loaded, quit the program.
	if(document == NULL){
		printf("Failed to load file\n");
		return 0;
	}
	system("rmdir \"words\" /q /s"); // quietly removes the words directory
	//create word files directory
	CreateDirectory(WORD_FILES_PATH, NULL);
	
	//open debug file
	#if debug
	FILE *debugFile = fopen("debug.txt", "w");
	if(debugFile == NULL) printf("Couldn't open debug.txt file.\n");
	#endif
	
	
	
	//these are two arrays to hold the current word and the previous word that the program analyzed.
	//words[0][] = current word
	//words[1][] = previous word
	char words[2][MAX_WORD_LENGTH] = {"",""};
	
	//this keeps track of the frequency of each chracter
	unsigned long int freq[256];
	for(i=0; i<256; i++) freq[i] = 0; // reset freq elements.
	unsigned long int charactersAnalyzed=0; // keeps track of how many characters have been analyzed
	
	int wordsAnalyzed=0; // this tells us how many words we have analyzed.
	
	time_t startTime = time(NULL);
	i=0;
	char temporaryStorage;
	
	//main word loop
	while(1){
		
		
		//get a word from file
		i=0; // reset index.
		while(2){
			
			//if you have run out of space in words[0][], then get to the end of the word and move on to the next one
			if(i>=MAX_WORD_LENGTH){
				//end the current word
				words[0][MAX_WORD_LENGTH-1] = '\0'; // end the word
				
				//move to the next word
				j=0;
				while(3){
					temporaryStorage = fgetc(document); // advance character
					freq[(unsigned char)temporaryStorage]++; // increment this character's frequency (we don't want our results to be fraudulant!  :S
					if(temporaryStorage == false)// if you find the end of the word...
						break; // stop advancing characters. You have found the end of the current word.
					j++;
				}
				break; // stop inputting the current word.
			}
			
			
			words[0][i] = fgetc(document); //get character from the document.
			freq[(unsigned char)words[0][i]]++; // increment this character's frequency.
			charactersAnalyzed++; // increment the number of characters analyzed
			
			//if the character input was a valid word-character
			if(isValidWordChar((unsigned char)words[0][i])){
				//if the character is uppercase
				if(words[0][i]>='A'&&words[0][i]<='Z')
					// make it lowercase (by adding 32)
					words[0][i]+= 0x20;
				//increment index
				i++;
			}
			else{
				break; // if the character you input is invalid, stop inputting the word.
			}
		}
		
		
		//if you have reached this point, that means that you are going to end the word, crunch some data, and then get memory ready to input another word.
		//end the word
		words[0][i] = '\0';
		//if this word is at least a character long and it has at least one alphabetic letter (a-z)
		if(i>0 && has_some_lowercase_letter(words[0])){
			//if the previous word is valid
			if(words[1][0] != '\0')
				//add relationship
				add_word_relationship(words[0], words[1]);
			//increment words analyzed
			wordsAnalyzed++;
			#if debug
			fprintf(debugFile, "%6.6d %s\n", wordsAnalyzed, words[0]);
			#endif // debug
			//copy the current word into the last word.
			strcpy(words[1], words[0]);
		}
		//if you reached the end of the document stop reading in the document
		if(feof(document)) break;
	}
	
	//calculate time it took.
	time_t executionTime = difftime(time(NULL), startTime);
	if(executionTime<1)executionTime = 1; // this solves the divide by zero errors
	
	
	
	
	printf("\nFinished analyzing document.\nAnalysis took %d seconds.\nAnalyzed %d words.\nAnalyzed %lu characters.\n\n", (int)executionTime, wordsAnalyzed, charactersAnalyzed);
	float averageWordLength = ((float)charactersAnalyzed)/((float)wordsAnalyzed);
	int wordsPerSecond = wordsAnalyzed/executionTime;
	int charactersPerSecond = charactersAnalyzed/executionTime;
	printf("On average, the words were %.2f characters long.\nAnalysis ran at %d words per second.\nAnalysis ran at %d characters per second.\n", averageWordLength, wordsPerSecond, charactersPerSecond);
	
	//print character frequency results to a file
	FILE *charFreqFile = fopen("Character Frequency.txt", "w");
	if(charFreqFile != NULL){
		fprintf(charFreqFile,"#character number - character - number of times the character appears\n");
		for(i=0; i<256; i++){
			fprintf(charFreqFile, "#%d - %c - %lu\n",i, (char)i, freq[i]);
		}
		fclose(charFreqFile);
	}
	
	#if debug
	fclose(debugFile);
	#endif // debug
	//close the document file
	if(document != NULL) fclose(document);
	return 0;
}

