// ryan's program to help with physics calculations  :)


#include <stdio.h>
#include <math.h>


int main(){
	
	
	float R1;
	float R2;
	float n = 1.5;
	float s = 17.5;	
	float f;
	float s_prime;
	
	while(1){
		printf("R1 (cm) = ");
		scanf("%f", &R1);
		
		printf("R2 (cm) = ");
		scanf("%f", &R2);
		
		f = (0.5) * ( (1/R1)  -  (1/R2) );
		f = (1/f);
		
		printf("f = %f\n", f);
		
		s_prime = (1/f) - (1/s);
		s_prime = 1 / s_prime;
		
		printf("s' (cm) = %f\n\n\n", s_prime);
	}
	
	return 0;
}
