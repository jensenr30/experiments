/**
keyboard Profiler
Written by Ryan Jensen
2014-06-15
The purpose of this program is to generate statistics about written documents regarding key strokes.
The intended uses for this program are for:
	- generating a profile for the English language so that a program can be written to randomly create words that look "English-like"
	- writing a program that analyzes keyboard layouts and, through a series of genetic algorithms, optimizes a keyboard layout for speed and comfort.
However, I'm sure that anyone with a little bit of creativity could think of a good use for this program.
*/

/*
This program can be used via command line using the following formats:

// For Windows users use

    > keyprof.exe

// For Linux users, use

    $ ./keyprof

// keyprof will compute statistics on the follow document, "myBook.txt"
// the statistics will be written to the default file location (which is in the same directory as keyprof).
// if the default file already has data in it, keyprof will merge (add) the data gathered to any existing

	$ ./keyprof ~/myBook.txt

// keyprof will compute statistics on both documents (the text file and the source code) are save findings in the default file path.

	$ ./keyprof ~/myBook.txt ~/my_source_code.c

// by default, keyprof will merge the data calculated in its current execution to any data that was calculated in a previous execution.
// if you want to make keyprof erase any old data before writing the current data to file, use the option, "--overwrite"

	$ ./keyprof --overwrite ~/myBook.txt

// if you want to specify an output file, then simply use the option, "--output-file"
// note that the argument after "--output-file" is the output path.
// all other arguments will be interpreted as input files for calculating keyboard statistics.

	$ ./keyprof --output-file ~/data_output_file.txt C~/myBook.txt


**/




#include <stdio.h>
#include <string.h>
#include "keyboard_profiler.h"


//--------------------------------------------
// these function log errors
//--------------------------------------------

// logs string to file
void keyprof_log(char *string){
	FILE *log = fopen(KEYPROF_LOG_FILE_NAME, "a");
	if(log != NULL) fprintf(log, "%s\n", string);
	fclose(log);
}
// logs string and integer to file
void keyprof_log_d(char *string, int data){
	FILE *log = fopen(KEYPROF_LOG_FILE_NAME, "a");
	if(log != NULL) fprintf(log, "%s\t%d\n", string, data);
	fclose(log);
}
// logs string and another string to file
void keyprof_log_s(char *string, char *data){
	FILE *log = fopen(KEYPROF_LOG_FILE_NAME, "a");
	if(log != NULL) fprintf(log, "%s\t%s\n", string, data);
	fclose(log);
}



void keyprof_init(){
	// initialize that keyDataString
	keyDataString = "abcdefghijklmnopqrstuvwxyz`-=[];',./ABCDEFGHIJKLMNOPQRSTUVWXYZ~_+{}:\"<>?";
}

/// this will save keyData to file
short keyprof_save_stats(unsigned long long int *keyData, unsigned long long int *keyFrequency, unsigned long long int *keyStartingFrequency, unsigned long long int *wordLength, char *filePath){

	FILE *saveFile = fopen(filePath, "w");
	// make sure the file was opened correctly
	if(saveFile == NULL) return KEYPROF_FILE_NOT_FOUND;

	fprintf(saveFile, "\t");
	int f, s; // these record the character index f=first, s=second.
	for(f=0; f<KEYPROF_KEYS; f++) fprintf(saveFile, "%c\t", keyDataString[f]);
	fprintf(saveFile, "Next Character");
	// f is the cause and s is the effect.
	for(f=0; f<KEYPROF_KEYS; f++){
		fprintf(saveFile, "\n%c\t", keyDataString[f]);
		for(s=0; s<KEYPROF_KEYS; s++){
			// print the data for the number of times that the user presses [f] and then [s]
			/// TODO: figure out how to print unsigned long long
			fprintf(saveFile, "%lu\t", keyData[f*KEYPROF_KEYS+s]);
		}
	}

	// descrbe the y axis
	fprintf(saveFile, "\nGiven Character\n");


	// describe the following table
	fprintf(saveFile, "\n\nWord Length\tFrequency\n");
	// write the word length frequency data to file
	int l;
	for(l=1; l<KEYPROF_WORD_LENGTH_MAX; l++){
		fprintf(saveFile, "%d\t%lu\n", l, wordLength[l]);
	}


	// describe the character frequency table
	fprintf(saveFile, "\n\nCharacter\tFrequency\n");
	// write the character frequency to file
	int c;
	for(c=0; c<KEYPROF_KEYS; c++){
		fprintf(saveFile, "%c%c\t%lu\n", keyDataString[c], keyDataString[c+KEYPROF_KEYS], keyFrequency[c]);
	}

	fprintf(saveFile, "\n\nWord Starting Character\tFrequency\n");
	for(c=0; c<KEYPROF_KEYS; c++){
		fprintf(saveFile, "%c%c\t%lu\n", keyDataString[c], keyDataString[c+KEYPROF_KEYS], keyStartingFrequency[c]);
	}

	// close up shop when you leave
	fclose(saveFile);
	// success
	return 0;
}



/// this will add the statistics from the saved file to the keyData.
// this will NOT overwrite keyData. It will only add to it what was found in the file.
// returns 0 on success
// returns 1 on failure to load file
short keyprof_load_stats(char *filePath, unsigned long long int *keyData){

	FILE *loadFile = fopen(filePath, "w");
	// make sure the file was opened correctly
	if(loadFile == NULL) return KEYPROF_FILE_NOT_FOUND;


	// these are used to process the data from the loadFile
	char charCurrent;
	char charLast;
	char charInput;


	while(1){
		charInput = fgetc(loadFile);

		/// TODO: PROCESS INPUT DATA

		// break because there is nothing written in here yet
		break;
	}

	// close up shop when you leave
	fclose(loadFile);
	// success
	return 0;
}


/// this will perform the statistical number crunching on the input files.
// this will take a text file and reduce it to numbers in an array that describe how it works.
// keyData is a pointer to an array of ULL integers that is KEYPROF_KEYS x KEYPROF_KEYS in size. this records what keys will lead to what keys.
// keyFrequency is a pointer to an array of size KEYPROF_KEYS that record the frequency of each key.
// wordLength is a pointer to an array of length KEYPROF_WORD_LENGTH_MAX that records how many times a word has beeen found that has x number of characters in it (where x is used to index into the array)
// keyData, keyFrequency, and wordLength all must be valid for the function to work. If any are NULL, the program will return 1.
// filePath is the path of the file that will be loaded and crunched (for example: "C:\Users\MyUserName\Documents\MyDoc.txt")
// include symbols will dictate whether or not we use symbols `~-_=+[{]};:'",<.>/?
// keystrokeMode will count the end of words and the beginning of the next word as being related. word mode will restrict letter associations to the words they are found in.
short keyprof_crunch_file(unsigned long long int *keyData, unsigned long long int *keyFrequency, unsigned long long int *keyStartingFrequency, unsigned long long int *wordLength, char *filePath, char includeSymbols, char keystrokeMode){

	// make sure the pointers are all valid.
	if(keyData == NULL || keyFrequency == NULL || wordLength == NULL) return 1;

	// attempt to open the file path
	FILE *inputFile = fopen(filePath, "r");
	// if the file cannot be opened, then report a FILE_NOT_FOUND error.
	if(inputFile == NULL) return KEYPROF_FILE_NOT_FOUND;



	// otherwise, the file should be open and ready for business.

	// these are used to process the data from the loadFile
	char indexCurrent;
	char indexLast = -1; // this is initialized to -1 because there is no lastIndex when you start up the program.
	char charInput;
	int currentWordLength=0;


	// input all characters
	while(1){

		// input a character
		charInput = fgetc(inputFile);


		// if the character input is an uppercase letter,
		if(charInput >= 'A' && charInput <= 'Z'){
			// record it on a scale of 0 to 25 (a through z)
			indexCurrent = charInput-'A';
		}
		// if the character is a lowercase letter,
		else if(charInput >= 'a' && charInput <= 'z'){
			// record it on a scale of 0 to 25 (a through z)
			indexCurrent = charInput-'a';
		}
		// check for symbols
		else if( includeSymbols && (charInput == '`' || charInput == '~') ) indexCurrent = 26;
		else if( includeSymbols && (charInput == '-' || charInput == '_') ) indexCurrent = 27;
		else if( includeSymbols && (charInput == '=' || charInput == '+') ) indexCurrent = 28;
		else if( includeSymbols && (charInput == '[' || charInput == '{') ) indexCurrent = 29;
		else if( includeSymbols && (charInput == ']' || charInput == '}') ) indexCurrent = 30;
		else if( includeSymbols && (charInput == ';' || charInput == ':') ) indexCurrent = 31;
		else if( includeSymbols && (charInput == '\''|| charInput == '"') ) indexCurrent = 32;
		else if( includeSymbols && (charInput == ',' || charInput == '<') ) indexCurrent = 33;
		else if( includeSymbols && (charInput == '.' || charInput == '>') ) indexCurrent = 34;
		else if( includeSymbols && (charInput == '/' || charInput == '?') ) indexCurrent = 35;
		else if(charInput == EOF){
			wordLength[currentWordLength]++;
			break;	// if this is the end of the file, then stop inputting data.
		}
		else{
			// if no valid character was input, that means that there is currently no word being processed.
			// if this iteration marks the end of a word,
			if(currentWordLength != 0){
				// cutoff the word length at KEYPROF_WORD_LENGTH_MAX
				if(currentWordLength > KEYPROF_WORD_LENGTH_MAX) currentWordLength = KEYPROF_WORD_LENGTH_MAX;
				// then record the word length
				wordLength[currentWordLength]++;
				// record that this is the end of the word and don't associate the next letter with the current letter.
				if(!keystrokeMode)indexLast = -2;
			}
			// set word length to 0 because we are no longer processing a word.
			currentWordLength = 0;
			continue;
		}

		// add character to character frequency list
		keyFrequency[indexCurrent]++;

		// if this is the beginning of a word, record that in the keyStartingFrequency array.
		if(currentWordLength == 0) keyStartingFrequency[indexCurrent]++;

		// make sure that this isn't the beginning of the document
		if(indexLast != -1){
			// make sure that you are either in keystroke mode, or the last index was a valid character.
			if(keystrokeMode || indexLast != -2)
			keyData[indexLast*KEYPROF_KEYS+indexCurrent]++;
		}
		// increase the word length
		currentWordLength++;
		// record the current index as the last.
		indexLast = indexCurrent;
	}

	// close up the place on your way out.
	fclose(inputFile);
	return 0;
}





/// this is the workhorse function. Pass it argc and argv from "int main()" and it will take care of everything.
// this interpret the command line arguments sent to the program.
int keyboard_profiler(int argc, char *argv[]){

	// initialize keyboard profiler stuff
	keyprof_init();

	// record what the input arguments were
	keyprof_log_d("Number of Input Arguments =", argc);
	keyprof_log("");
	int arg;
	for(arg = 0; arg<argc; arg++) keyprof_log(argv[arg]);
	keyprof_log("\nEnd of Input Arguments.\n");

	// if the number of arguments was 1 or less, that means that there couldn't possibly have been an input document
	if(argc <= 1) return KEYPROF_NO_INPUT_FILES_PASSED;

	//--------------------------------------------
	// set up input data
	//--------------------------------------------

	// this is the array that will hold all of the key data
	// the first index, keydata[FirstIndex][] is an index into what the previous key was
	// the second index, keyData[][SecondIndex] is an index into what key came after the last key
	// so if you were to record the sentence, "hello", the program would do essentially the following:
	// keyData[h][e]++;
	// keyData[e][l]++;
	// keyData[l][l]++;
	// keyData[l][o]++;
	unsigned long long int keyData[KEYPROF_KEYS][KEYPROF_KEYS];
	// this keeps track of how often each key is found.
	unsigned long long int keyFrequency[KEYPROF_KEYS];
	// this keeps track of how many times words with certain lengths are found.
	// index this array with the length of the word you found, and increment whenever you find a word.
	unsigned long long int wordLength[KEYPROF_WORD_LENGTH_MAX];
	// this keeps track of which letters start words most often
	unsigned long long int keyStartingFrequency[KEYPROF_KEYS];

	// set all keyData elements to 0 initially.
	// set all keyFrequency elements to 0 initially as well
	int f, s;
	for(f=0; f<KEYPROF_KEYS; f++){
		for(s=0; s<KEYPROF_KEYS; s++){
			keyData[f][s] = 0;
		}
		keyFrequency[f] = 0;
		keyStartingFrequency[f] = 0;
	}

	// set all wordLength elements to 0 initially
	int length;
	for(length=0; length<KEYPROF_WORD_LENGTH_MAX; length++){
		wordLength[length] = 0;
	}


	// this is the default output name
	char *outputPath = KEYPROF_OUTPUT_NAME_DEFAULT;
	// normally, the output of this program is added to the output of any previous executions of this program.
	// normally, previously collected data gets merged into the data that is collected by this execution of the program.
	// if this is set to 1, then when this execution of the program is writing statistics to file, it will discard any previous data that was in the output file.
	char outputOverwrite = 0;
	// by default, the program will not include symbols (it will just evaluate alphabetic characters a-z (lowercase and uppercase)).
	// the option KEYPROF_OPT_INCLUDE_SYMBOLS must be used to activate this.
	char includeSymbols = 0;
	// this tells the program to work in keystroke mode if it is 1.
	// if it is 0, it works in word mode.
	char keystrokeMode = 0;

	//--------------------------------------------
	// process input arguments
	//--------------------------------------------
	// arg starts at 1 because the first argument is the file path of keyprof.exe and we don't really care about that here.
	for(arg=1; arg<argc; arg++){

		// record the current argument
		keyprof_log_s("Argument =",argv[arg]);

		// check to see if the argument matches the custom output path option
		if(strcmp(argv[arg], KEYPROF_OPT_OUTPUT_PATH) == 0 || strcmp(argv[arg], KEYPROF_OPT_OUTPUT_PATH_SHORT) == 0){

			// use the next argument as the output file name.
			outputPath = argv[arg+1];
			// skip the next argument (because it was just used to get the output file name)
			arg++;
			// record the next argument as well (because otherwise it would be skipped)
			keyprof_log_s("Argument =",argv[arg]);

			// continue to the next argument
			continue;
		}

		// check to see if the argument matches the overwrite option
		if(strcmp(argv[arg], KEYPROF_OPT_OVERWRITE) == 0 || strcmp(argv[arg], KEYPROF_OPT_OVERWRITE_SHORT) == 0){
			// record that you want to overwrite the output file when the time comes.
			outputOverwrite = 1;
			// continue to the next argument
			continue;
		}

		// check to see if the argument matches the overwrite option
		if(strcmp(argv[arg], KEYPROF_OPT_INCLUDE_SYMBOLS) == 0 || strcmp(argv[arg], KEYPROF_OPT_INCLUDE_SYMBOLS_SHORT) == 0){
			// record that you want to overwrite the output file when the time comes.
			includeSymbols = 1;
			// continue to the next argument
			continue;
		}
		if(strcmp(argv[arg], KEYPROF_OPT_KEYSTROK_MODE) == 0 || strcmp(argv[arg], KEYPROF_OPT_KEYSTROK_MODE_SHORT) == 0){
			// record that the user wants to work in keystroke mode instead of word mode
			keystrokeMode = 1;
			// continue to the next argument
			continue;
		}

		// if this argument is not an option, then it must be an input file path.
		keyprof_crunch_file(&keyData[0][0], &keyFrequency[0], &keyStartingFrequency[0], &wordLength[0], argv[arg], includeSymbols, keystrokeMode);

	}

	// if the we aren't supposed to overwrite the file, we need to read it and record it before we go overwriting it.
	if(!outputOverwrite) keyprof_load_stats(outputPath, &keyData[0][0]);
	// save stats to file
	keyprof_save_stats(&keyData[0][0], &keyFrequency[0], &keyStartingFrequency[0], &wordLength[0], outputPath);

	// successfully computed statistics
	return 0;
}





