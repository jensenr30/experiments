/* Ryan Jensen
 * Sorting an array of positive integers and finding the one with greatest occurances (the mode of the set).
 * 2013-05-07
 * This program does not support finding multiple modes like it would in a perfect world. Instead, if you have an array with three 1's and three 2's, the mode will be determined by which of these numbers comes first in the array. That is what will determine it and that alone.
 */

#include <stdio.h>

#define NUMBER_OF_ELEMENTS_TO_SORT 10

int main(){
	
	int i, j; // whores.
	
	int inputArray[NUMBER_OF_ELEMENTS_TO_SORT] = {1,2,2,4,5,6,7,8,9,10}; // this is your input (obviously)
	
	int sortedArray[NUMBER_OF_ELEMENTS_TO_SORT][2]; // NUMBER_OF_ELEMENTS_TO_SORT x 2 array.
	
	// fill up the array with the proper initial data. {-1, 0} will be the default. that allows us to check if the lot has been filled up with number data from the array because from the project description, you are only accepting POSITIVE integers. that helps a lot. however, there would be a way around it if your prof wanted the full range of integers... but i digress.
	for(i=0 ; i<NUMBER_OF_ELEMENTS_TO_SORT ; i++){
		sortedArray[i][0] = -1; // for no place in the array will there be any data on any number to begin with. (-1 signifies that)
		sortedArray[i][1] = 0;  // 0 occurances of each type of number
	}
	
	//ironically, sortedArray starts out completely unsorted. But don't you worry. It gets there.
	
	//SORT ALL THE SHIT
	
	for(i=0 ; i<NUMBER_OF_ELEMENTS_TO_SORT ; i++){ // whore. i indexes into inputArray
		for(j=0 ; j<NUMBER_OF_ELEMENTS_TO_SORT ; j++){ // whore^2. j indexes into the sortedArray
			if(sortedArray[j][0] == inputArray[i]){
				sortedArray[j][1]++;
				break;
			}
			if(sortedArray[j][0] == -1){
				sortedArray[j][0] = inputArray[i]; // reserve this place for the number inputArray[i]
				sortedArray[j][1]++; // record that you found a number.
				break;
			}
		}//end for j
	}//end for i
	
	printf(" number  occurances\n");
	//this prints the contents of the sorted array
	for(i=0 ; i<NUMBER_OF_ELEMENTS_TO_SORT ; i++){
		printf("%5d  %5d\n", sortedArray[i][0], sortedArray[i][1]);
	}
	printf("\n\n"); // finishing move! GIGA! DRILL BREEEEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	//FIND THE BEST SHIT
	int mode = -1; // default to -1 (no mode)
	int occurances = 1; // only look for occuraces greater than one.
	
	for(i=0 ; i<NUMBER_OF_ELEMENTS_TO_SORT ; i++){
		if(sortedArray[i][1] > occurances){
			mode = sortedArray[i][0];
			occurances = sortedArray[i][1];
		}
	}
	
	
	printf("mode = %d\noccurances = %d\n\n", mode,occurances);
	system("pause");
	return 0;
}
