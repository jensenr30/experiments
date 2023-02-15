//standard header files
#include <stdio.h>
#include <Windows.h>
#include <string.h>

//definitions
#define ARG_AMOUNT 4
#define ARG_LENGTH 16
#define NUMBER_OF_COMMANDS 10

//prototypes
int input_command();
int check_command();
int run_command();
void p();
void c();
void die();
void suck();
void hello();
void moo();
void copypasta();
void deathnote();
void spoonbash();
void beep();
void minecraft();
void portal();

//global variables
char command_list[NUMBER_OF_COMMANDS][ARG_LENGTH] = {
	"die",			// 0
	"suck",			// 1
	"hello",		// 2
	"moo",			// 3
	"copypasta",	// 4
	"deathnote",	// 5
	"spoonbash",	// 6
	"beep",			// 7
	"minecraft",	// 8
	"portal"		// 9
};
char command[ARG_AMOUNT][ARG_LENGTH];
int number_of_errors = 0;
int current_line_number = 0;
FILE* script = NULL;

//header files 
#include "functions.h"
#include "commands.h"
