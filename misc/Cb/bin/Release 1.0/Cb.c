/*
Cb language and engine was written by Ryan Jensen.
It is open source code.
If you have any comments or suggestions, email me at JensenR30@Gmail.com
This Cb script engine is by no means complete.

To do:
- write the function to run script commands.
- make the script user defined (not what i have currently, "C:\\Users\\...")
- ditribute to JP, Rellik, Domo, Jake, and anyone else who dares try it.

*/


/*
  "Cb header.h" handles:
  declaration of global variables, declaration of function prototypes,
  including header files, definitions, and everything else that you
  would expect to find at the beginning of a program.
*/
#include "Cb header.h"

int main(int argc, char* argv[])
{
	//make the command prompt window look nice
	system("color F0");
	//tell the user what file is being opened
	printf( "opening %s\n\n", argv[1] );
	script = fopen(argv[1], "r");
	//this is useful for debugging
	//script = fopen("C:\\Users\\Ryan\\Programming\\Cb\\bin\\Debug\\Cb script.txt", "r");
	if(script == NULL)
	{
		printf("ERROR: file could not be opened.");
		p();
		return 0;
	}
	//look at the top of functions.h to see what the return values of input_command represent.
	//there is a table of values
	//begin error checking commands from script
	int a = 0;
	while(a == 0 || a == 2)
	{
		current_line_number++;
		a = input_command();
		if(a == 0 || a == 1) check_command();
	}
	
	//reopen the script file
	fclose(script);
	script = fopen(argv[1], "r");
	//start running commands from script
	a = 0;
	current_line_number = 0;
	while(a == 0 || a == 2)
	{
		current_line_number++;
		a = input_command();
		if(a == 0 || a == 1) run_command();
	}
	
	
	
	if(number_of_errors)
	{
		printf("\nThe end of your script has been reached with %d errors.\n", number_of_errors);
		printf("  Read the \"Cb READ ME.txt\" file to learn how to solve these problems.\n");
		printf("  Press any key to quit.\n");
	}
	else
	{
		c();
		printf("Your program ran without any errors.\nPress any key to quit.\n");
	}
	p();
	return 0;
}
