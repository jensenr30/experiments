
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



void set_screen_size(short x, short y)
{
	//create the rectangle
	SMALL_RECT size;
	size.Left   = 1;
	size.Top    = 1;
	size.Right  = x;
	size.Bottom = y;
	
	//set window size
	SetConsoleWindowInfo( GetStdHandle(STD_OUTPUT_HANDLE), 1, &size);
}




void cursor_info(short int visible, short int size)
{
	
	
	//make a new console cursor info structure for hiding the cursor
	CONSOLE_CURSOR_INFO my_cursor_info;
	//set cursor to invisible
	my_cursor_info.bVisible = visible;
	//set cursor to 3/10 of the character spot. this variable has to be between 1 and 100 for SetConsoleCursorInfo to work properly.
	my_cursor_info.dwSize = size;
	//refresh cursor info (this actually makes the screen refelct the changes made to the members of the my_cursor_info structure.
	SetConsoleCursorInfo( GetStdHandle(STD_OUTPUT_HANDLE), &my_cursor_info );
	
	
}


