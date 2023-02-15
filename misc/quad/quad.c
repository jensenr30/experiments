/* Ryan Jensen // July 17th, 2012 // "Quad"
 * This program was written to allow computations with numbers with lots of decimal places.
 * I plan to calculate pi to 1000 places using my quad.h header file.
 * I plan to calculate the alternating harmonic series to 1000 decimal places using my quad.h header file.
 * I plan to calculate e to 1000 decimal places with my quad.h header file
 *
 *
 */




#include <stdio.h>
#include <Windows.h>
#include "quad.h"

//define useful functions for pausing
void pn(void) {  system("pause>nul");  }
void p(void)  {  system("pause");      }

int main()
{
	// whore variable
	int i;
    // define quads
    quad my_quad[quadarraysize];
    quad input_quad[quadarraysize];
    quad sum_quad[quadarraysize];
    quad scanning_quad[quadarraysize];

    //set to 0 initially
    for(i = 0; i < quadarraysize; i++ ) my_quad[i] = 0;
    for(i = 0; i < quadarraysize; i++ ) input_quad[i] = 0;
    for(i = 0; i < quadarraysize; i++ ) sum_quad[i] = 0;

    /*//set some values
    my_quad[0]  = 123456789;
    my_quad[1]  = 0;
    my_quad[2]  = 0;
    my_quad[3]  = 0;
    my_quad[4]  = 0;
    my_quad[5]  = 0;
    my_quad[6]  = 0;
    my_quad[7]  = 0;
    my_quad[8]  = 0;
    my_quad[9]  = 0;
    my_quad[10] = 0;
    my_quad[11] = 1;*/

    my_quad[0] = 20000000;
    my_quad[1] = 500000000;
    my_quad[2] = 500000001;
    input_quad[0] = 20000000;
    input_quad[1] = 500000000;
    input_quad[2] = 500000001;
    int x = addq(my_quad, input_quad, sum_quad);

    //show user what the value of quad a is

    //scanq(my_quad);
    printq(sum_quad);
    printf("\nEnter a positive number from 0 up to 1 billion with up to 100 decimal points\n");
    scanq(scanning_quad);

    //pause>nul
    pn();

    return 0;

}
