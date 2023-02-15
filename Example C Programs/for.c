#include <stdio.h>

int main(void){
	system("color 0f");
	//this is the loop variable.
	//it keeps track of how many times we have gone through the loop
	int i;
	
	//this is a for loop
	for(i=0; i<=20; i++){
		printf("%d\n", i); // print numbers
	} 
	//pause
	system("pause>nul");
	
	for(i=0; i<=20; i++){
		printf("%d\n",i*i); // print squares
	}
	system("pause>nul");
	
	//prints characters
	for(i=0; i<=20; i++) printf("%c\n", i);
	
		
	
	
	
	system("pause>nul");
    return 0;
}
