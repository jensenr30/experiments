#include <stdio.h>
#include <math.h>

int main(void)
{
	double decimal;								// this stores the user's input 
	double error_target;						// the target error is 1 part per million
	double error;								// current error calculation
	double error_min;							// this is the best error that has been found so far
	
	
	long long unsigned int numer;				// this is the numerator   of our integer fraction approximation
	long long unsigned int denom;				// this is the denominator of our integer fraction approximation
	double approx;								// this is the approximation formed by dividing numer by denom.
	unsigned char reciprocal;					// when the magnitude of the decimal number is less than 1, this is set to 1
	unsigned char invert;						// when the decimal number is negative, this will be set to 1.
	printf("fraction-calculator 0.1.\n");		// print information
	printf("This program converts decimal numbers into fractions.\n");
	printf("Valid inputs look like:\n");
	printf("(e.g. 0.12345, 3.92e-4, 12.54e6, etc...)\n\n\n");
	
	while(1)									// keep asking for user input
	{
		error_target = 1e-6;						// setup initial conditions
		error = 1;									// "
		error_min = 1;								// "
		denom = 1;									// "
		reciprocal = 0;								// "
		invert = 0;									// "
		
		printf("Please enter a decimal number\n>> ");
		
		scanf("%lf",&decimal);						// input number from user
		printf("You entered %f\n\n",decimal);		// tell the user how the input was interpreted
		
		
		
		if(fabs(decimal) < 1)						// if the decimal number's magnitude is less than 1,
		{
			reciprocal = 1;								// record that you are taking the reciprocal.
			decimal = ((double)1.0)/decimal;			// take the reciprocal (this simplifies code that finds fractions)
		}
		
		if(decimal < 0)								// if the number is negative
		{
			invert = 1;									// record that you are inverting the number
			decimal = -decimal;							// invert the number
		}
		
		
		printf("| %9s / %-9s | ","numer","denom");	// print table header
		printf("%15s | %15s | ","approx","error");	// "
		printf("\n");								// "
		printf("|-------------------");				// "
		printf("--------------------");				// "
		printf("--------------------|");			// "
		printf("\n");								// "
		
		denom = 1;
		while(error_min > error_target)				// until you have found a precise-enough fraction to approximate the decimal number,
		{
			numer = roundl(denom*decimal);				// compute what the numerator should be for the perfect fraction,
														// then round the numerator to the nearest integer
														// (to minimize the error for this particular integer denominator
			approx = (double)numer/(double)denom;		// calculate the approximation that is made by the numerator and the denominator 
			
			if(!reciprocal)								// if the number is not a reciprocal,
				error = (approx-decimal)/decimal;			// calculate the error between the current approximation and the desired decimal number.
			else										// otherwise,
				error = (1/approx-1/decimal)*decimal;		// calculate the error of the reciprocals
			
			if(fabs(error) < error_min)					// if the current error is the lowest one found so far,
			{
															// print approximation calculation info
				if(!reciprocal)								// if the number is not a reciprocal,
				{
					printf("| %9llu / %-9llu | ",numer,denom);	
				}
				else
				{
					printf("| %9llu / %-9llu | ",denom,numer);
					approx = 1/approx;						// 
				}
				
				printf("%15g | %15g | ",approx,error);		// "
				printf("\n");								// "
			}
			error_min = fmin(error_min,fabs(error));			// calculate the minimum error that has been found so far
			
			
			denom = denom + 1;							// during the next loop iteration, test the next denominator.
		}
		
		printf("\n\n");								// separate these calculations from the next number the user will enter
	}
	return 0;
}
