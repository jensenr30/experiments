#include <stdio.h>

int main(void){
	
	int usersNumber;
	
	//input user number
	printf("Enter a decimal number and I'll tell you your fortune: ");
	scanf("%d", &usersNumber);
	
	
	
	//check to see if the number is positive
	if(usersNumber > 0){
		printf("Your number is positive.\n");
	}
	
	//check to see if the number is negative
	if(usersNumber < 0){
		printf("Your number is negative.\n");
	}
	
	//check to see if the number is zero
	if(usersNumber == 0){
		printf("Your number is zero.\n");
	}
	
	
	
	system("pause>nul");
    return 0;
}
