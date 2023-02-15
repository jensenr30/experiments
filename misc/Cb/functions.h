
/* input_command() documentation:
	|---------------------------------------------------------------|
	|	    what		|	should i try	|	   should i			|
	|	input_command()	|	to run/check	|	  try to input		|
	|	   returns		|	this command?	|	another command?	|
	|-------------------|-------------------|-----------------------|
	|	0				|		yes			|		yes				|
	|	1				|		yes			|		no				|
	|	2				|		no			|		yes				|
	|	3				|		no			|		no				|
	|---------------------------------------------------------------|
*/
int input_command()
{
	int i, j;
	char input;
	//blank the command array
	for(j = 0; j < ARG_LENGTH; j++) command[j][0] = '\0';
	//input the line of text
	for(j = 0; j < ARG_AMOUNT ; j++)
	{
		for(i = 0; i < ARG_LENGTH ; i++)
		{
			//input a character from the text file
			input = fgetc(script);
			
			//if there is an End Of File character
			if(input == EOF)
			{
				command[j][i] = '\0';
				//if the EOF was the first character of this command, just quit (return 2).
				if(j == 0 && i == 0) return 3;
				//command[j][i] = '\0';
				return 1;
			}
			//if the line ends or if there is a comment
			else if(input == '\n')
			{
				//if this was the first character on the line
				if(j == 0 && i == 0) return 2;
				//otherwise, make that character a null character
				command[j][i] = '\0';
				//and go about your business.
				return 0;
			}
			//if there is a comment
			else if(input == '-' && command[j][i-1] == '-')
			{
				//make this argument string begin with a NULL character
				command[j][i-1] = '\0';
				//go to the next line
				while(input != '\n' && input != EOF) input = fgetc(script);
				//if the end of the comment happens to be the end of the file, quit everthing with return 3
				if(input == EOF) return 3;
				//then stop inputting this command (move on to the next one)
				//if the first character on the line was the start of a comment, return 2
				if(j == 0 && i-1 == 0) return 2;
				//if there was a command before the comment, continue on as normal
				return 0;
			}
			//if there is a space character
			else if(input == ' ')
			{
				//move on to the next argument
				break;
			}
			else command[j][i] = input;
		}
		//make sure the string has an ending
		if(i < ARG_LENGTH) command[j][i] = '\0';
		//if 
		if(i == ARG_LENGTH)
		{
			command[j][ARG_LENGTH -1] = '\0';
			printf("line %3d: argument too long:\t%s\n", current_line_number, &command[j][0]);
			number_of_errors++;
			//wait for the next argument/command
			while(input != ' ' && input != '\n' && input != EOF)
				input = fgetc(script);
				//if we reached the end of the line,
				//check to see if the command is valid and keep getting more commands
			if(input == '\n')
				return 0;
			//if we reached the end of the script,
			//check to see if the argument is valid, but after that, quit.
			else if(input == EOF)
				return 1;
			//if input was a space, move on to the next argument.
		}
	}
	if(j == ARG_AMOUNT)
	{
		printf("line %3d: Too many arguments\n", current_line_number);
		number_of_errors++;
		//wait for a new command
		while(input != '\n' && input != EOF) input = fgetc(script);
	}
	return 0;
}


//this command checks to see if commands ar valid. returns 0 if valid. returns 1 otherwise.
//note: the return value isn't used currently. it is just there because i may need it sometime down the road.
int check_command()
{
	int i;
	for(i = 0; i < NUMBER_OF_COMMANDS; i++)
	{
		//if the user-entered command matches any known commands, return 0
		if( strcmp( &command[0][0], &command_list[i][0] ) == 0 ) return 1;
	}
	number_of_errors++;
	printf("line %3d: unknown command:\t%s\n", current_line_number, &command[0][0]);
	return 0;
}

//returns 1 if command is not recognized. returns 0 if all is right with the world
int run_command()
{
	int i;
	for(i = 0; i < NUMBER_OF_COMMANDS; i++)
	{
		if( strcmp( &command[0][0], &command_list[i][0] ) == 0 ) break;
	}
	switch(i)
	{
		case 0:
			die();
			break;
		case 1:
			suck();
			break;
		case 2:
			hello();
			break;
		case 3:
			moo();
			break;
		case 4:
			copypasta();
			break;
		case 5:
			deathnote();
			break;
		case 6:
			spoonbash();
			break;
		case 7:
			beep();
			break;
		case 8:
			minecraft();
			break;
		case 9:
			portal();
			break;
		default:
			printf("line %3d: command passed command_check()\n", current_line_number);
			printf("  but was not recognized: %s\n", &command[0][0]);
			number_of_errors++;
			return 1;
			break;
	}
	return 0;
}


//pause function
void p() { system("pause>nul"); }
//clear screen function
void c() { system("cls"); }


