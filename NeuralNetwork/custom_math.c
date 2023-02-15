#include <stdio.h>
#include "custom_math.h"

/// this will sort the data you send it.
// the data will be overwritten
// stuff[0] will be the minimum value, stuff[elements-1] will be the maximum value.
// returns 0 on success
// *stuff is a pointer to an array of floats with [elements] number of elements.
// *ord is an array that returns the change in position of elements in the stuff array.
short bubble_sort_f(float *stuff, unsigned int elements, unsigned int *ord)
{
	// handle bad input data
	if(stuff == NULL) return 1;
	if(elements < 1) return 2;
	if(elements == 1) return 0;
	
	// initialize the variables that will be used to sort the data
	int i,j,cmin;
	float temp;
	int tempOrd;
	
	// initialize the order of the elements
	for(j=0; j<elements; j++)
	{
		ord[j] = j;
	}
	
	// for every element,
	for(j=0; j<elements-1; j++)
	{
		// initialize the minimum.
		cmin = j;
		// for every element after this one,
		for(i=j+1; i<elements; i++)
		{
			// if it is smaller than current minimum,
			if(stuff[i] <= stuff[cmin])
			{
				// re-record the current minimum as the ith element
				cmin = i;
			}
		}
		
		// swap the minimum value found for the jth element.
		temp = stuff[j];
		stuff[j] = stuff[cmin];
		stuff[cmin] = temp;
		// record the motion in the order array
		tempOrd = ord[j];
		ord[j] = ord[cmin];
		ord[cmin] = tempOrd;
	}
	
	// success
	return 0;
}


/// this will sort things probably faster than a bubble sort.
// < insert better sorting algorithm here >


