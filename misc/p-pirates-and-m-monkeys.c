#include <stdio.h>

#define MAX_COCONUTS ((unsigned long long) 1000000 )


int main(void)
{
	
	
	// n is the number of pirates
	// m is the number of monkeys
	unsigned long pirates, monkeys;
	unsigned long maxCoconuts;
	
	printf("How many pirates were there?\n");
	scanf("%u", &pirates);
	printf("How many monkeys were there?\n");
	scanf("%u", &monkeys);
	
	// open the coconut text file. this will be used to record the results of the calculation in.
	FILE *coconutFile = fopen("coconut.txt", "w");
	FILE *coconutFileStrict = fopen("coconutSTRICT.txt", "w");
	
	
	printf("pirates = %u\nmonkeys = %u\n\n\n\n", pirates, monkeys);
	fprintf(coconutFile, "pirates = %u\nmonkeys = %u\n\n\n\n", pirates, monkeys);
	fprintf(coconutFileStrict, "pirates = %u\nmonkeys = %u\n\n\n\n", pirates, monkeys);
	
	
	// check to make sure pirates and monkeys are positive numbers
	if( pirates < 1)
	{
		printf("You have entered a number less than 1 for pirates: %u\n", pirates);
		fprintf(coconutFile, "You have entered a number less than 1 for pirates: %u\n", pirates);
		return 0;
	}
	if( monkeys < 0)
	{
		printf("You have entered a number less than 1 for monkeys: %u\n", monkeys);
		fprintf(coconutFile, "You have entered a number less than 1 for monkeys: %u\n", monkeys);
		return 0;
	}	
	
	
	// coconuts is the number of coconuts currently being evaluated
	unsigned long coconuts;
	// p is the number of pirates
	unsigned long p;
	// cc is used to store the coconut count (as we evaluate whether or not the coconuts can be split up
	unsigned long cococount;
	unsigned long lastCoconuts = 0;
	
	char found = 0;
	char printme = 0;
	
	for(coconuts = 0; coconuts < MAX_COCONUTS; coconuts++)
	{
		// set the current coconut count to the initial coconut number that is being tested
		cococount = coconuts;
		
		if(printme)
		{
			printf("\ncoconuts = %u\n", coconuts);
			fprintf(coconutFile, "\ncoconuts = %u\n", coconuts);
		}
		// loop through each pirate waking up, taking his/her share of the pile, and giving the remainder to the monkey(s)
		for(p = 1; p <= pirates; p++)
		{
			if(printme)
			{
				printf("\tp = %u\n",p);
				fprintf(coconutFile, "\tp = %u\n",p);
			}
			// if the number of coconuts can be divided with exactly the right remainder to give to the monkey(s)
			if(cococount % pirates == monkeys)
			{
				// print saying you found one!!
				if(printme)
				{
					printf("\t\t %12u %% %12u = %12u   ->   %12u\n", cococount, pirates, monkeys, ((cococount-monkeys)*(pirates-1)/pirates));
					fprintf(coconutFile, "\t\t %12u %% %12u = %12u   ->   %12u\n", cococount, pirates, monkeys, ((cococount-monkeys)*(pirates-1)/pirates));
				}
				// one pirate takes his share of the coconuts
				cococount = ((cococount - monkeys)*(pirates-1))/pirates;
				if(p == pirates)
				{
					// if there enough coconuts left in the morning to split between the pirates and give one to each of the monkeys,
					if(cococount % pirates == monkeys)
					{
						if(printme)
						{
							printf("%12u\n", coconuts);
							fprintf(coconutFileStrict, "%12u %12u\n", coconuts, coconuts-lastCoconuts);
							lastCoconuts = coconuts;
						}
						found++;
						// If you just finished calculating a valid coconut number without printing it, then do it again, but print it this time.
						if(!printme)
						{
							printme = 1;
							coconuts--;
						}
						else
						{
							printme = 0;
						}
					}
				}
			}
			// otherwise, this number of coconuts (c) has failed
			else
			{
				break;
			}
		}
	}
	
	if(!found)
	{
		printf("Coconut numbers checked = 1 through %d\n", MAX_COCONUTS);
		printf("No valid coconut numbers were found.\n");
		fprintf(coconutFile, "No valid coconut numbers were found.\n");
		fprintf(coconutFileStrict, "No valid coconut numbers were found.\n");
	}
	
	// close the coconut text file
	fclose(coconutFile);
	fclose(coconutFileStrict);
	return 0;
}
