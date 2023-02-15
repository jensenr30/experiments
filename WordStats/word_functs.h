#define WORD_FILES_PATH "words\\"
// I don't think most words are going to be longer than 512 characters :P
#define MAX_WORD_LENGTH 64
//the maximum number of relationships that a word can have (the number of different words that it can point to.
#define MAX_WORD_RELATIONSHIPS 10000
//maximum number of unique words
#define MAX_UNIQUE_WORDS 1000

//used for storing data on words.
struct wordData {
	//how many times has this word been found?
	unsigned short occurances;
	char wordName[MAX_WORD_LENGTH];
	
	struct wordData *nextWords[MAX_WORD_RELATIONSHIPS];
} myWordData[MAX_UNIQUE_WORDS];

/// returns true or false whether the input char is an acceptable word-type character.
bool isValidWordChar( unsigned char inputChar ){
	if(       (inputChar >= 'A' &&inputChar <= 'Z')	// uppercase letters
			||(inputChar >= 'a' &&inputChar <= 'z')	// lowercase letters
			||(inputChar >= '0' &&inputChar <= '9')	// numbers
			|| inputChar == '-'						// dashes for hyphonated words
			|| inputChar == '_'						// underscores for analyzing programming stylized documents
			|| inputChar == '\''					// apostrophes for contractions
			|| inputChar == 145						// right apostrophe
			|| inputChar == 146 					// left  apostrophe
	){
		return true; // valid character, return true
	}
	else return false; // invalid character, return false.
}

void add_word_relationship(char * wordCurr, char * wordPrev){
	//generate a file name for this word
	char wordPrevFileName[MAX_WORD_LENGTH+10];
	strcpy(wordPrevFileName, WORD_FILES_PATH);
	strcat(wordPrevFileName, wordPrev);
	strcat(wordPrevFileName, ".txt");
	
	FILE *wordPrevFile = fopen(wordPrevFileName, "a");
	if(wordPrevFile == NULL) {
		printf("failed to open %s\n",wordPrevFileName);
		return; // quit if you cannot open it.
	}
	
	//assuming the file is open, add the current word to the list
	fprintf(wordPrevFile, "%s\n", wordCurr);
	fclose(wordPrevFile);
}






FILE *choose_file(){
	OPENFILENAME ofn;
	char szFileName[MAX_PATH] = "";

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrDefExt = "txt";
	ofn.lpstrInitialDir = ".";
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR | OFN_FILEMUSTEXIST;

	if(GetOpenFileName(&ofn))
	{
		printf("Analyzing %s\n", szFileName);
	    return fopen(szFileName, "r");
	}
	else return NULL;
}


///returns true if there is at least 1 lowercase letter.
///returns false otherwise.
bool has_some_lowercase_letter(char *inputstr){
	int length = strlen(inputstr);
	int i;
	for(i=0; i<length; i++){
		if(inputstr[i] >= 'a' && inputstr[i] <= 'z') return true;
	}
	return false;
}





