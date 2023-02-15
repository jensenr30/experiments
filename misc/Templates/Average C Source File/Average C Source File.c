#include <stdio.h>
#include <Windows.h>

int main(void)
{
	int i;
	for(i = 0; i < 256; i++)
	{
		if( !(i % 4) ) printf("\n\n");
		printf("%d. %c\t\t", i, i);
	}
	printf("\n");
	system("pause>nul");
}
