#include <stdio.h>
#include <conio.h>

int main(void)
{
	//declare input character variable
	char input;
	
	//just keep doing it over and over
	while(1)
	{
		//input a character from the user
		input = getche();
		//print it
		printf( "\b%u\n", input );
	}
	
	//end program
	return 0;	
}
