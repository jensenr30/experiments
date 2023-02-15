#include <stdio.h>
#include <math.h>


int main(){
	
	double result = (double)1 - exp(0.5);
	printf("1 - e^(-1/10 ) = %f\n", (double)1 - exp(-1/10.0));
	printf("1 - e^(-1/5.0) = %f\n", (double)1 - exp(-1/5.0));
	printf("1 - e^(-1/2.0) = %f\n", (double)1 - exp(-1/2.0));
	printf("1 - e^(-1/1.0) = %f\n", (double)1 - exp(-1/1.0));
	printf("1 - e^(-1/0.5) = %f\n", (double)1 - exp(-1/0.5));
	printf("1 - e^(-1/0.2) = %f\n", (double)1 - exp(-1/0.2));
	printf("1 - e^(-1/0.1) = %f\n", (double)1 - exp(-1/0.1));
	
	system("pause>nul");
	return 0;
}
