#include <stdio.h>


int main(void)
{
	/*
	int shift = 3;
	int result = ( 1<<shift ) - 1;
	
	printf("( 1<<%d ) - 1 = %d\n", shift, result);
	
	int i;
	for(i=0; i<16; i++)
	{
		printf("%d", ( result & (1<<(15-i)) ) > 0 );
	}
	
	return 0;
	*/
	
	double a = 1.23456;
	char str[13];
	sprintf(str, "%.5e", a);
	
	printf(str);
	
	return 0;
}
