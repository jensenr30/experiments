#include <stdio.h>
#include "Windows.h"

int main(){
	int i;
	for(i=0 ; i<40 ; i++)
		printf("%d\n", get_rand(0,2500));
	return 0;
}

// returns a random number between low_bound and _highbound
int get_rand(lowBound, highBound){
	int diff = highBound - lowBound;
	return ( rand() % (diff+1) ) + lowBound;
}
