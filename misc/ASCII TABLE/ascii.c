#include <stdio.h>

int main()
{
	short int i;
	for(i = 0; i < 256; i++)
	{
		printf("\t\t%d %c", i, i);
		if(i % 4 == 3) printf("\n\n");
	}
	printf("\n");
	system("pause>nul");
	return 0;
}
