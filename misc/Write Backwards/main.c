#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "cursor.h"


int main()
{
	system("color 8a");
	cursor_info(1, 16);
	set_screen_size(80, 51);
	system("cls");
	
	int x, y;
	char input;
	for(x = 79, y = 49; y >= 0; x--)
	{
		put_cursor(x, y);
		input = getche();
		if(input == '\b')
		{
			x++;
			if(x >= 80)
			{
				x = 0;
				y++;
			}
			put_cursor(x, y);
			putch(' ');
			x++;
		}
		if(x == 0 && y == 0) break;
		
		if(x == 0)
		{
			y--;
			x = 80;
		}
	}
	system("pause>nul");
	return 0;
}
