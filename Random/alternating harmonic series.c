#include <stdio.h>

double alt_harm(unsigned long int n){
	// used to store the sign
	int sign;
	
	//determine sign of the element. even numbers are negative. odd numbers are positive.
	if(n%2 == 0) sign = -1;
	else sign = 1;
	
	// last result in the series (or first depending on how you look at it.
	if(n == 1) return 1.0f;
	// return the current numbers reciprocal plus the rest of the terms
	if(n >  1) return  ( sign / ((float)n) ) + alt_harm(n-1);
	
	// something REALLY FUCKED UP if you got a negative value here. jesus christ.
	exit(101);
	// return a really screwed up value if you have really screwed up input. you have to get the programmer's attention somehow...
	return -10.0f;
}



int main(void){
	unsigned long int alt_harm_term = 1;
	
	while(alt_harm_term != 0){
		printf("Enter n to calculate the nth term of the alternating harmonic series (enter 0 to quit)\n");
		scanf("%Lu", &alt_harm_term);
		printf("Alt Harm(%d) = %f\n\n",alt_harm_term, alt_harm(alt_harm_term));
	}
	return 0;
}
