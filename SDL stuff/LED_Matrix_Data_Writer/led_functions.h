
void turn_on_LED( int, int );




//if type == 3, turn led off
//if type == 1, turn led on
//if type == 2, toggle led
void LED_press_check( int x, int y, int type)
{
	int row, column;
	int x_coor_LED, y_coor_LED;
	
	y_coor_LED = 50;
	for(row = 0; row < 9; row++, y_coor_LED += 50)
	{
		x_coor_LED = 50;
		for(column = 0; column < 9; column++, x_coor_LED += 50)
		{
			if( x > x_coor_LED && x < x_coor_LED + 50 && y > y_coor_LED && y < y_coor_LED + 50 )
			{
				if(type == 3)
					LEDs[row][column] = 0;	// turn off LED
				else if(type == 1)
					LEDs[row][column] = 1;	//  turn on LED
				else if(type == 2)
				{							//   toggle LED
					if( LEDs[row][column] ) LEDs[row][column] = 0;
					else					LEDs[row][column] = 1;
				}
			}
		}
	}
	
	
	
	
}


void print_LEDs()
{
	int x_coor_LED, y_coor_LED;
	int row, column;
	
	y_coor_LED = 50;
	for(row = 0; row < 9; row++, y_coor_LED += 50)
	{
		x_coor_LED = 50;
		for(column = 0; column < 9; column++, x_coor_LED += 50)
		{
			if(LEDs[row][column])
				apply_surface( x_coor_LED, y_coor_LED, LED, screen );
		}
	}
	
	
	
	
}



void print_to_file()
{
	FILE *pattern;
	int row, column, sum;
	
	pattern = fopen("Pattern Data.txt", "a");
	
	for(row = 0; row < 9; row++)
	{
		sum = 0;
		for(column = 0; column < 8; column++)
		{
			sum <<= 1; // bit shift left
			sum += LEDs[row][column];
		}
		fprintf(pattern, "dispdata[%d] = (2 * 0x", row);
		if(sum < 0x10) fprintf(pattern, "0");
		fprintf(pattern, "%x) + %d;\t//  ", sum, LEDs[row][8]);
		
		for(column = 0; column < 9; column++)
		{
			if(LEDs[row][column])
				fprintf(pattern, " O");
			else
				fprintf(pattern, " -");
		}
		fprintf(pattern, "\n");
	}
	fprintf(pattern, "\ndisp(10);\n\n");
	
	
	fclose(pattern);
}


// inverts all LED data
void invert_LEDs()
{
	int row, column;
	for(row = 0; row < 9; row++)
	{
		for(column = 0; column < 9; column++)
		{
			if( LEDs[row][column] ) LEDs[row][column] = 0;
			else LEDs[row][column] = 1;
		}
	}
}



// checks to see if the saved button is up ro down (if the user is pressing the button)
SDL_Surface *SavedUorD(int button)
{
	
	if( button )	return SaveDOWN;
	else			return SaveUP;
	
}




int withing_region(int xpos, int ypos, int xmin, int ymin, int xmax, int ymax)
{
	if(xpos >= xmin && xpos <= xmax && ypos >= ymin && ypos <= ymax)
		return 1;
	else
		return 0;
}



void print_save_button(int buttonUp)
{
	if(buttonUp == 1)
		apply_surface(75, 5, SaveUP, screen);
	else
		apply_surface(75, 5, SaveDOWN, screen);
}
