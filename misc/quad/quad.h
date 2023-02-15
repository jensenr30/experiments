#include <stdio.h>

// define the quad variable type
typedef long long int quad;
// define how many elements each quad array will have
const short int quadarraysize  = 12;
// this should generate a element resolution (how many decimal places of information we can store in each element of the quad arrays.
const quad maxnumber = 999999999;  // 999,999,999 (9 decimal places per element in the quad array) maxnumber must be a number with 9's in all places.
//this is how many decimal places each element of the quad array can store
const quad decimal_places = 9;


// function prototypes
// executes the operation on two quad numbers and returns pointer to the quad array
quad addq(  quad* a, quad* b, quad* c );  // a + b = c
quad subq(  quad* a, quad* b, quad* c );  // a - b = c
quad multq( quad* a, quad* b, quad* c ); // a * b = c
quad divq(  quad* a, quad* b, quad* c );  // a / b = c
quad modq(  quad* a, quad* b, quad* c );  // a % b = c

quad  printq ( quad* a); // prints a quad
quad scanq  ( quad* a); // inputs a quad
quad  fprintq( FILE* filename, quad* a ); // prints a quad from file
quad fscanq ( FILE* filename, quad* a ); // inputs a quad from file


quad printq(quad* a)
{
    //print the first element
    printf( "%ld", a[0] );

    //figure out where the trailing zeros are
    short int trailing_zeros = quadarraysize;
    for( ; trailing_zeros > 0; trailing_zeros--)
        if( a[ trailing_zeros-1 ] != 0 ) break;
    //returning 1 mean that there were all decimal places equal zero.
	if( trailing_zeros == 1) return 1;
	printf("."); //print the decimal point

    //print the decimal places (the elements of the quad a[] array)
    int i = 1;
    for( ; i < trailing_zeros; i++ )
    {
        if( a[i] >= 0 && a[i] <= maxnumber )
            printf("%.9ld ", a[i]);
        else
            printf(" ERROR: a[%d] = %ld ", i, a[i]);
    }
    return 0;
}


quad scanq(quad* a)
{
	//whore variable
	int i;
	//keeps track of how many periods the user enters. (it only acknowledges the leftmost period entered if there are more than 1)
	int decimal_point_count = 0;
	// this is double the number of decimal places a quad array has (double the length is for safety)
	const quad input_quad_string_length = (quadarraysize*decimal_places + 2) * 2;
	//declare string
    char input_char[ input_quad_string_length ];

    for( i = 0; i < input_quad_string_length; i++ )
    {
    	//input character from user
    	input_char[i] = getchar();
    	// if input_char is numeric, do nothing. simply write let that numeric character stay in the array and move on to the next character
    	if(input_char[i] >= '0' && input_char[i] <= '9');
    	//if the user enters a period
    	if(input_char[i] == '.')
    	{
    		//if the user has entered a period before...
			if(decimal_point_count)
				//overwrite the current character on the next go around
				i--;
			// increment the deciaml_point_count
			decimal_point_count++;
    	}
		//if getchar() produces a newline or a NULL character, stop the input
    	else if(input_char[i] == '\n' || input_char[i] == '\0')
    		break;
    	//if the character isn't numeric or something that would stop the input, just ignore it. overwrite it from the array next go around.
    	else i--;

    }
    //safety precaution. we want to have an end of our string, don't we?  :P
    input_char[i] = '\0';

    printf("\n%s\n", input_char);
}

quad addq( quad* a, quad* b, quad* c )
{
	int i;

	/*
	quad term_a[quadarraysize], term_b[quadarraysize], sum[quadarraysize];
	&term_a[0] = a;
	&term_b[0] = b;
	&sum[0] = c;
	*/

	// set the sum to 0 initially
	for(i = 0; i < quadarraysize; i++ ) c[i] = 0;


	for( i = quadarraysize - 1; i >= 0; i-- )
	{
		// the sum of a and b is stored in c
		c[i] += a[i] + b[i];

		if( c[i] > maxnumber )
		{
			if( i == 0)
			{
				quad overflow = c[i] / (maxnumber + 1);
				printf("\n error in printq(): overflow = %ld billion >= 1 billion! \n", overflow );
				return overflow;
			}
			c[i] -= (maxnumber + 1);
			c[i-1]++;
		}
	}
	return 0;
}
