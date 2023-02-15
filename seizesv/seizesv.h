#ifndef SEIZESV_DEFINED


#include <inttypes.h>
#include <stdio.h>
#define SEIZESV_DEFINED 1

//------------------------------------------------------------------------------
// DEFINITIONS
//------------------------------------------------------------------------------

// this is how the floating point NAN value is generated:
#define SSV_NAN (0.0/0.0)
// this is how many data points are stored per block
#define SSV_BLOCK_VALS 500
// the maximum number of characters that can be input as a single variable
#define SSV_MAX_INPUT_LENGTH (50000+1)
// checks if the input value was interpreted as a number (successfully numerically decoded)
// if it was NOT interpreted as a number, it would have been set to SSV_NAN
#define IS_NUM(n) ( n == n )
// this will free a value of memory 
#define SSV_FREE_VALUE(v) 	\
	if(v->str != NULL)  { 	\
		free(v->str);		\
	}

//------------------------------------------------------------------------------
// TYPE DEFINITIONS
//------------------------------------------------------------------------------
	
// this is the default type used for enumerating things insize seizesv structures:
typedef uint64_t ssv_type;


//------------------------------------------------------------------------------
// STRUCTURES
//------------------------------------------------------------------------------

/// this struct contains a single value from a csv file
// ALL data points have their ORIGIANL TEXT stored in a location pointed to by
// the [str] variable.
// However, if the data can be decoded into a numerical format, that number will
// be stored in the [num] variable as  BONUS to the original text.
struct ssv_value {
	
	// this is where the numerical data is stored if there is any
	// by default, this should be set to SSV_NAN (floating point nan, 0.0/0.0)
	double num;
	
	// this is a pointer to the string
	// by default, this should be a NULL pointer
	char  *str;
	
	
};


/// this is a collection of data points
// this block type is intended to be part of a linked list.
// each block represents some number of rows in a SINGLE column.
// the top block in any column points to the next block on it's right.
// each block points to the block below it.
// the block list will be as wide and as long as it needs to be.
// [ ]--->[ ]--->[ ]--->  ...
//  |      |      |
//	V      V      V    
// [ ]    [ ]    [ ]
//  |      |      |
//	V      V      V    
// [ ]    [ ]    [ ]
//         .
//         .
//         .
// NOTE: the following members of ssv_block are ONLY STORED IN THE TOP (FIRST)
// BLOCK of an ssv_file:
	// title
	// col_is_const
	// cmax
	// cmin
	// ssv_blockRight
// the above members will exist in all blocks, but they should only be treated
// as being valid when the block is at the top of a column
struct ssv_block {
	
	// this is the title of the column
	char *title;
	// this indicates whether or not the ENTIRES column (not just this block) is constant
	// 0 = the column is not constant
	// 1 = the column is constant
	char col_is_const;
	
	// this is the maximum numerical value found in the column
	double cmax;
	// this is the minimum numerical value found in the column
	double cmin;
	
	// these are the data points contained in this block
	struct ssv_value vals[SSV_BLOCK_VALS];
	
	// this is the block to the right
	struct ssv_block *blockRight;
	// this is the block below
	struct ssv_block *blockDown;
	
};


struct ssv_file {
	
	// this contains the file name (including the path) of the .csv that was parsed
	char *file_name;
	
	// each file has an origin block.
	// from the origin, all other blocks can be reached.
	struct ssv_block origin;
	
	// this is the number of columns a csv file has
	ssv_type columns;
	// this is the number of rows a csv file has
	ssv_type rows;
	
};

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

char ssv_value_is_nan(struct ssv_value *v);
int ssv_read_value_from_csv(FILE *fp, struct ssv_value *v);
int ssv_file_read(char *file_name, struct ssv_file *f);
struct ssv_block *ssv_block_create(void);
int ssv_block_init(struct ssv_block *b);
int ssv_file_set_value(struct ssv_file *f, ssv_type column, ssv_type row, struct ssv_value *v);
int ssv_file_get_value(struct ssv_file *f, ssv_type column, ssv_type row, struct ssv_value *v);
int ssv_file_row_create(struct ssv_file *f, ssv_type r);
int ssv_file_write(struct ssv_file *f, char *file_name);
ssv_type ssv_file_find_constants_max_min(struct ssv_file *f) ;
struct ssv_block *ssv_file_get_column_top(struct ssv_file *f, ssv_type col);



#endif
