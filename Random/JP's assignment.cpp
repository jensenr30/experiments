#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

//begin main loop
int main(void){
    
    srand(time(NULL));
    
    //declare number
    int inputNumber;
    
    while(1){ // infinite loop
    	//prompt
    	cout << "\nEnter a number: ";
    	
	    //input number
	    cin >> inputNumber;
	    
	    //switch statement
	    switch(inputNumber){
		case 1:
			cout << "You have only " << inputNumber * 10 << "ballsachs\n";
			break;
		case 2:
			cout << inputNumber * 3.5 << "\n";
			break;
	    case 3:
			cout << inputNumber * (rand()%40) << "\n";
			break;
	    case 4:
			cout << "this is the fourth one: " << inputNumber << "\n";
			break;
	    case 5:
			cout << inputNumber * 0 << "\n";
			break;
	    case 6:
			cout << inputNumber * 0x80000 << "\n";
			break;
	    case 7:
			cout << inputNumber * 90 << "\n";
			break;
	    case 8:
			cout << inputNumber * 23 + 32 << "\n";
			break;
	    case 9:
			cout << inputNumber * 23 << "\n";
			break;
	    case 10:
			cout << "The tenth one: " << inputNumber * 13 << "\n";
			break;
	    default:
			cout << "You suck at this\n";
			break;
		}
	    
	}//while(1)
	
	//the program will never get here.
    return 0;
}
