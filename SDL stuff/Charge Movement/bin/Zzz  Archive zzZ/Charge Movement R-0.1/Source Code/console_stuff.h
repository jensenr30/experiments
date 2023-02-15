/*
void c()
{
	system("cls");
}
void p()
{
	system("pause>nul");
}




void edit_charge(int cn)
{
	int result;
	char chargeMenu[8][100];
	char numberString[50];
	
	strcpy( chargeMenu[0], "Charged Particle Number " );
	strcat( chargeMenu[0], itoa(cn, numberString, 10) );
	
	strcpy( chargeMenu[1], "Sign " );
	if(charges[cn].charge > 0)
	{
		strcat( chargeMenu[1], "(+) positive" );
	}
	else if(charges[cn].charge < 0)
	{
		strcat( chargeMenu[1], "(-) negative" );
	}
	else
	{
		strcat( chargeMenu[1], "(n) no charge" );
	}
	
	strcpy( chargeMenu[2], "Charge " );
	strcat( chargeMenu[2], itoa(charges[cn].charge, numberString, 10) );
	strcat( chargeMenu[2], " uC" );
	
	strcpy( chargeMenu[3], "X pos " );
	strcat( chargeMenu[3], itoa(charges[cn].position[0], numberString, 10) );
	strcat( chargeMenu[3], " m" );
	
	strcpy( chargeMenu[4], "Y pos " );
	strcat( chargeMenu[4], itoa(charges[cn].position[1], numberString, 10) );
	strcat( chargeMenu[4], " m" );
	
	strcpy( chargeMenu[5], "X Speed " );
	strcat( chargeMenu[5], itoa(charges[cn].speed[0], numberString, 10) );
	strcat( chargeMenu[5], " m/s" );
	
	strcpy( chargeMenu[5], "Y Speed " );
	strcat( chargeMenu[5], itoa(charges[cn].speed[1], numberString, 10) );
	strcat( chargeMenu[5], " m/s" );
	
	strcpy( chargeMenu[7], "Mass " );
	strcat( chargeMenu[7], itoa(charges[cn].mass, numberString, 10) );
	strcat( chargeMenu[7], " kg" );
	
	char *chargeMenu2[] =
	{
		chargeMenu[0],
		chargeMenu[1],
		chargeMenu[2],
		chargeMenu[3],
		chargeMenu[4],
		chargeMenu[5],
		chargeMenu[6],
		chargeMenu[7],
	};
	
	//result = menu(1, 1, chargeMenu2, 7);
	
}












void put_cursor(int x, int y)
{
	//make a new console screen buffer to store cursor position
	static CONSOLE_SCREEN_BUFFER_INFO my_console;
	
	//set x and y coordinates
	my_console.dwCursorPosition.X = x;
	my_console.dwCursorPosition.Y = y;
	
	//set cursor position
	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), my_console.dwCursorPosition );
}



//returns the pointer to the beginning of an array that contains a [0] element (x) and a [1] element (y).
int *get_cursor()
{
	static int pos[2];
	
	//make a new console screen buffer
	static CONSOLE_SCREEN_BUFFER_INFO my_console;
	//get coordinates
	GetConsoleScreenBufferInfo( GetStdHandle(STD_OUTPUT_HANDLE), &my_console );
	
	//store the coordinates
	pos[0] = my_console.dwCursorPosition.X;
	pos[1] = my_console.dwCursorPosition.Y;
	
	//return pointer to the first element of the array
	return &pos[0];
}




//menu() is used for making menus that the player can interface with.
int menu( int clear_screen, int beginning_option_line, char *opt[], int opts_numb )
{
	//line will be used to see what line the player is on. i is used in the for loop as the incremental variable.
	int line[2], i; line[1] = 1;
	// *pos this is used to store the pointer returned from get_cursor();
	int *pos;
	if(beginning_option_line >= 1 || beginning_option_line <= opts_numb) line[0] = beginning_option_line;
	else line[0] = 1;
	//these will be used for storing the coordinates of each choice. the last element will be where the cursor is normally.
	int x[opts_numb], y[opts_numb];
	//this is used for player input
	char input, input2;
	//clear screen if need be
	if(clear_screen) c();
	
	if(opt[0][0] != '\0')
	{
		printf("%s\n\n", opt[0]);
	}
	//print options
	for(i = 1; i <= opts_numb; i++)
	{
		//get coordinates for the beginning of each option line
		pos = get_cursor();
		//store the [0] and [1] elements of the array that pos points to in the x[] and y[] arrays respectively.
		x[i] = pos[0];
		y[i] = pos[1];
		//print a little arrow on the line that the user is on.
		if(i == line[0]) putch(26);
		else putch(' ');
		//print this line's option.
		printf(" %s\n", opt[i]);
	}//done printing options
	//get coordinates one last time. this records the coordinates of the final cursor placement. it is the 0th element of the x and y arrays
	pos = get_cursor();
	x[0] = pos[0];
	y[0] = pos[1];
	
	//this is where the player inputs key strokes.
	while(1)
	{
		//enter user keystroke
		input = getche();
		printf("\b \b");
		if(input == 13) break;
		//if the user presses escape, return 0
		else if(input == 27) return 0;
		//if the user trys to go up or down
		
		//copy current line into last line
		line[1] = line[0];
		if(input == 'w' || input == 'W') line[0]--;
		if(input == 's' || input == 'S') line[0]++;
		if(input == -32)
		{
			input2 = getche();
			if(input2 == 72) line[0]--;
			else if(input2 == 80) line[0]++;
		}
		//make sure your line is in bounds (error check the line value)
		if(line[0] < 1)
		{
			line[0] = opts_numb;
		}
		else if(line[0] > opts_numb)
		{
			line[0] = 1;
		}
		//make coordinates mark the old line
		put_cursor( x[line[1]], y[line[1]] );
		//remove the arrow character
		putch(' ');
		//move the corsor to the newly selected option line
		put_cursor(x[line[0]], y[line[0]]);
		//put the little arrow character
		putch(26);
		//move the cursor back to the end (bottom) of the screen.
		put_cursor(x[0], y[0]);
	}
	return line[0];
}


*/



