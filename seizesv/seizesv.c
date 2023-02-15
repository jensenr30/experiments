#include "seizesv.h"
#include <string.h>
#include <math.h>
#include "utilities.h"





char ssv_value_is_nan(struct ssv_value *v){
	
	// if the string has any combination of 
	// NAN
	// NAn
	// NaN
	// Nan
	// nAN
	// nAn
	// naN
	// nan
	// plus a terminatin null character,
	if(v->str[0] == 'n' || v->str[0] == 'N'){
		if(v->str[1] == 'a' || v->str[1] == 'A'){
			if(v->str[2] == 'n' || v->str[2] == 'N'){
				if(v->str[3] == '\0'){
					// report a nan entry
					return 1;
				}
			}
		}
	}
	// otherwise, the entry is not nan.
	return 0;
}


/// this will read a value from a csv file
// [fp] is a pointer to a csv file
// [v] is a pointer to the ssv_value structure where the input value will be stored.
// returns:
//	3	found value; terminated with unknown character? weird. This should ABSOLUTELY never happen.
//	2	found value; terminated with EOF. This typically should not happen. Usually csvs are terminated with newlines...
//	1	found value; terminated with a newline (end of row)
//	0	found value; terminated with comma (more values in row)
// 	-1 	NULL fp
//	-2	NULL v
//	-3	had problem using malloc() to get memory for storing string
int ssv_read_value_from_csv(FILE *fp, struct ssv_value *v) {
	
	// make sure the file pointer is valid
	if (fp == NULL) {
		error("ssv_read_value_from_csv() was sent a NULL [fp]");
		return -1;
	}
	// make sure the value structure pointer is valid
	if(v == NULL) {
		error("ssv_read_value_from_csv() was sent a NULL [v]");
		return -2;
	}
	
	
	//--------------------------------------------------------------------------
	// read characters from text file
	//--------------------------------------------------------------------------
	
	// Set an arbitrary maximum length of the length of the input variable string.
	static char input[SSV_MAX_INPUT_LENGTH];
	
	char c;
	int charsFound = 0;
	char foundEnd = 0;
	char reportedLongString = 0;
	// input a string from the csv file. Stop inputting the string when you find
	// a comma, a newline, or an EOF
	do {
			
		// input a character
		c = fgetc(fp);
		
		// if the character terminates the value,
		if (c == ',' || c == '\n' || c == '\r' || c == EOF) {
			
			// record that you have found the end
			foundEnd = 1;
			// if the value string was short enough to be recorded completely,
			if (charsFound < SSV_MAX_INPUT_LENGTH) {
				// terminate the string after the last character was found from the value
				input[charsFound] = '\0';
			}
			// otherwise, the string was longer than the arbitrary limit I impose.
			else {
				//terminate the string at the last elemnt in the array, truncating
				// off the extra data that didn't fit into the [input] array.
				input[SSV_MAX_INPUT_LENGTH-1] = '\0';
				// record the number of chars you have found.
				charsFound = SSV_MAX_INPUT_LENGTH-1;
			}
			
		}
		// if the character is valid
		else {
			
			if (charsFound < SSV_MAX_INPUT_LENGTH) {
				// record the character in the input array
				input[charsFound] = c;
				// record the number of chars you have found
				charsFound++;
			}
			// if the input string had too many characters
			else if(!reportedLongString) {
				// report it
				error("ssv_read_value_from_csv() read a string that exceeded the maximum length! String is:");
				error(input);
				// don't report this again for this value
				reportedLongString = 1;
			}
			
		}
		
	} while (!foundEnd) ; // stop reading characters once you have found the end of the value
	
	
	
	// record the input string
	//ssvlog(input);
	
	
	//--------------------------------------------------------------------------
	// determine if the input is numerical or text
	//--------------------------------------------------------------------------
	
	// assume it is a number. the following code will test if it is a number and
	// set isNum to 0 if it is not
	char isNum = 1;
	// start finding the mantissa
	char findingMantissa = 1;
	// this keeps track of what to divide by when adding decimal values 
	double divInputDigit = 0;
	// keep track of what the mantissa is
	double mantissa = 0;
	// keep track of what the exponent is
	double exponent = 0;
	int i = 0;
	// 1 is positive sign of the mantissa, -1 is negative sign of the mantissa
	double mantissa_sign = 1;
	// 1 is positive sign of the exponent, -1 is negative sign of the exponent
	double exponent_sign = 1;
	// check if the number is negative
	// if the first character is a negative sign
	if (input[0] == '-') {
		mantissa_sign = -1;
		// ignore the first character
		i = 1;
	}
	// if the first character is a plus sign
	else if (input[0] == '+') {
		// ignore the first character
		i = 1;
	}
	
	while ( (i < charsFound) && isNum) {
		
		// if a digit was found in the string and you are finding the mantissa,
		if ( (input[i] >= '0' && input[i] <= '9') && findingMantissa) {
			// if the user is NOT inputting digits after the decimal point
			if (!divInputDigit) {
				// multiply the mantissa by 10 and add the value of the current digit
				mantissa = mantissa*10 + input[i] - '0';
			}
			// if the user IS inputting digits after the decimal point
			else {
				// add the fractional part of the input to the mantissa
				mantissa += (input[i] -'0')/divInputDigit;
				// make sure that next time, you divide the input digit by 10
				// times more than you just did, because each digit deeper into
				// the decimal places is worth 10 times less as the previous digit.
				divInputDigit *= 10;
			}
		}
		
		// if a digit was found in the string and you are finding the exponent,
		else if ( (input[i] >= '0' && input[i] <= '9') && !findingMantissa) {
			// multiply the exponent by 10 and add the input digit
			exponent = exponent*10 + input[i] - '0';
		}
		
		// if the user found a period, and a period has NOT been found before,
		// and the period was found in the mantissa,
		else if ( input[i] == '.' && findingMantissa && !divInputDigit) {
			divInputDigit = 10;
		}
		
		// if an 'e' has been found (and an e has not been found before)
		else if (input[i] == 'e' && findingMantissa) {
			// start finding the exponent.
			findingMantissa = 0;
			// check for sign information along with the exponent
			if (input[i+1] == '-') {
				exponent_sign = -1;
				i++;
			}
			// if there is a plus sign just before the exponent
			else if (input[i+1] == '+') {
				i++;
			}
		}
		
		else {
			// stop trying to interpret this as a number. This will exit the while loop
			isNum = 0;
		}
		
		// increment the index. look at the next character in the input array
		i++;
	}
	// if the number was found out to be a number,
	if (isNum) {
		// save the number and the exponent in double format
		v->num = mantissa*mantissa_sign * pow(10, exponent*exponent_sign);
	}
	// otherwise, if it was NOT a number, record it as 
	else {
		// set the number to NAN
		v->num = NAN;
	}
	//--------------------------------------------------------------------------
	// save the text entry ALWAYS. 
	//--------------------------------------------------------------------------
	
	// the reason I save both the text AND the numberical data (if there is any
	// numerical data in a value) is so that the format of however the numbers
	// were printed is not changed if this program was ever to write csv files
	// back to file from ssv_value structures
	
	// allocate memory for the string plus the terminating null character
	v->str = malloc(sizeof(char)*(charsFound+1));
	
	if (v->str == NULL) {
		// report and error and return an error code
		error("ssv_read_value_from_csv() could not allocate memory for string! String =");
		error(input);
		return -3;
	}
	// otherwise, assuming memory was allocated successfully,
	else {
		// copy the string from the [input] variable into the structure's [str] memory location
		strcpy(v->str,input);
	}
	
	// return a different value based on what terminated the value string (comma, newline, EOF, or other)
	if (c == ',') {
		return 0;
	}
	else if (c == '\n' || c == '\r') {
		return 1;
	}
	else if (c == EOF) {
		return 2;
	}
	else {
		// if this ever happens, that means I don't have good control over this program...
		error_d("unknown character stopped ssv_read_value_from_csv()! character (in decimal) = ",(int)c);
		return 3;
	}
}


/// this will read the data from a file into memory in the format of an ssv_file structure.
// [file_name] is the name of the file you wish to read
// [f] is a pointer to the existing ssv_file structure that you want to fill with this data
// returns
//	-1	couldn't open [file_name]
//	-2	bad [f] pointer
//	-3	bad header
//	-4	problems writing data to ssv_file
int ssv_file_read(char *file_name, struct ssv_file *f) {
	
	// try to open file
	FILE *fp = fopen(file_name,"r");
	if (fp == NULL) {
		error("ssv_file_read() could not open the [file_name]:");
		error(file_name);
		return -1;
	}
	
	if (f == NULL) {
		error("ssv_file_read() was sent NULL [f]!");
		return -2;
	}
	
	// record file_name.
	f->file_name = file_name;
	// init the block to defaults
	ssv_block_init(&(f->origin));
	// reset the columns
	f->columns = 0;
	
	//--------------------------------------------------------------------------
	// read the header
	//--------------------------------------------------------------------------
	
	// remember if you have found the number of columns yet
	char foundColumns = 0;
	// start on the origin block
	struct ssv_block *b = &(f->origin);
	// this is where temporary data is stored from the ssv_read_value_from_csv() function
	struct ssv_value vbuf; vbuf.num = SSV_NAN; vbuf.str = NULL;
	// this catches what ssv_read_value_from_csv returns
	int ret_val;
	
	do {
		// read a value from the csv and store it in the value buffer
		ret_val = ssv_read_value_from_csv(fp, &vbuf);
		
		// save the title of the column
		b->title = vbuf.str;
		
		
		// if the value was terminated by a comma
		if (ret_val == 0) {
			// create a new block to the right of the current one.
			b->blockRight = ssv_block_create();
			// switch to next block
			b = b->blockRight;
			// increment the number of columns the csv file has
			f->columns++;
		}
		// if the value was terminated by a newline,
		else {
			// increment the number of columns the csv file has
			f->columns++;
			// record that you have found all of the column names, and thus are done reading the header
			foundColumns = 1;
			b->blockRight = NULL;
		}
		
	} while (!foundColumns);
	
	
	//--------------------------------------------------------------------------
	// read the data into memory in blocks
	//--------------------------------------------------------------------------
	
	// start at the origin block
	b = &(f->origin);
	ssv_type c = 0;
	// reset the rows
	f->rows = 0;
	char endOfLine;
	char endOfFile = 0;
	char foundSomethingOnLine;
	// record the number of rows that were created.
	// each ssv_file structure has [SSV_BLOCK_VALS] rows by default.
	ssv_type rowsCreated = SSV_BLOCK_VALS;
	// until you reach the end of the file,
	while (!endOfFile) {
		
		// if you have stepped past a block-edge boundary, you will need to allocate another row.
		if ( (f->rows > 0) && (f->rows % SSV_BLOCK_VALS == 0) ) {
			// create a new row of blocks
			ssv_file_row_create(f, f->rows/SSV_BLOCK_VALS);
			rowsCreated += SSV_BLOCK_VALS;
		}
		
		// you start at the beginning of a line of text
		endOfLine = 0;
		// at the beginning of a line, you don't know if you have found anything substantial yet
		foundSomethingOnLine = 0;
		// for every column,
		for (c = 0; c < f->columns && !endOfLine; c++) {
			// read the value from .csv file
			ret_val = ssv_read_value_from_csv(fp,&vbuf);
			// save it in memory
			if( ssv_file_set_value(f,c,f->rows,&vbuf) ) {
				error ("ssv_file_read() could not set values in its ssv_file structure");
				return -4;
			}
			// if the read value returns with a newline, EOF, or something else weird, end the line
			if(ret_val == 1 || ret_val == 3) {
				endOfLine = 1;
			}
			else if (ret_val == 2){
				endOfLine = 1;
				endOfFile = 1;
			}
			// if you have not found anything on the line yet,
			if (!foundSomethingOnLine) {
				// and you just found something on the line,
				if(strlen(vbuf.str) > 0) {
					//record that you found something on the line
					foundSomethingOnLine = 1;
				}
			}
		}
		if (foundSomethingOnLine) {
			// this indicates how many lines have been read into memory.
			f->rows++;
		}
		
		// get to the next line in the csv file if you find a character that terminates the line
		while ( ! ( (ret_val == 1) || (ret_val == 2) || (ret_val == 3) ) ) {
			// just read out values until you get to the next line. ignore extra entries on 
			ssv_read_value_from_csv(fp,&vbuf);
		}
		
	}
	
	// figure out which columns are constant
	ssv_file_find_constants_max_min(f);
	
	// close the file you opened for reading at the beginning of this function
	fclose(fp);
	// success
	return 0;
}


/// this will save an entire ssv_file to file in csv format
// if a file with the same name exists, it WILL OVERWRITE IT.

// when saving the data, this will save whatever is in the file->block->value->str.
// This IGNORES the file->block->value->num value.
// the reason this is done is so that if you read a file, then write that file out
// of memory and back to file, the content of the csv will not be altered in any way.

// input [f] is an ssv_file structure
// input [file_name] is the name of the file (including path, extension, etc...)
// returns:
// 	0	successfull printing to file.
//	-1	NULL [f] ssv_file
//	-2	couldn't open the specified file for writing
int ssv_file_write(struct ssv_file *f, char *file_name){
	
	// make sure the file structure was not NULL
	if (f == NULL) {
		error("ssv_file_read() was sent NULL [f]!");
		return -1;
	}
	
	// open the file for writing. Overwrite if it already exists.
	FILE *fp = fopen(file_name, "w");
	
	if (fp == NULL) {
		error("ssv_file_write() couldn't open the specified file:");
		error(file_name);
		return -2;
	}
	
	//--------------------------------------------------------------------------
	// print the header
	//--------------------------------------------------------------------------
	
	// start with the name of column 1
	struct ssv_block *b = &(f->origin);
	char term;
	ssv_type r,c;
	// write the column header
	for (c = 0; c < f->columns; c++) {
		// if this is the last column
		if(c < f->columns-1)	term = ',';
		else					term = '\n';
		// print the header
		if(b != NULL) {
			fprintf(fp,"%s%c",b->title,term);
		}
		
		// advance to the next column
		b = b->blockRight;
	}
	
	//--------------------------------------------------------------------------
	// print the data
	//--------------------------------------------------------------------------
	// 
	struct ssv_value vbuf; vbuf.num = SSV_NAN; vbuf.str = NULL;
	for (r = 0; r < f->rows; r++) {
		for (c = 0; c < f->columns; c++) {
			// get the value from the ssv_file
			ssv_file_get_value(f, c, r, &vbuf);
			// if this is the last column
			if(c < f->columns-1)	term = ',';
			else					term = '\n';
			
			if (r == f->rows-1 && c == f->columns-1) {
				int i;
				int j;
				j = i*i;
				i = j*j;
			}
			// if the string is valid
			if (vbuf.str != NULL) {
				// write that value's str member to the csv file.
				fprintf(fp,"%s%c",vbuf.str,term);
			}
			// otherwise, if it is NULL,
			else {
				// print "nan"
				fprintf(fp,"nan%c",term);
			}
		}
	}
	
	// close file
	fclose(fp);
	// success
	return 0;
}


/// this will attempt to allocate space for a ssv_block
// returns a pointer to the ssv_block it created, or it exits the program.
// all or nothing
struct ssv_block *ssv_block_create(void) {
	// try to allocate memory
	struct ssv_block *b = malloc(sizeof(struct ssv_block));
	// check for failure
	if ( b == NULL) {
		error("ssv_create_block() could not allocate space for block");
		exit(-23);
	}
	// initialize the block
	ssv_block_init(b);
	// return the newly created block
	return b;
}


/** \brief erases an ssv block
 * \param b is a pointer to the block you wish to initialize.
 * This function initializes the block that you send it.
 * This includes setting both block pointers and the title to NULL.
 * This sets the col_is_const indicator to 0
 * this resets all of the values num and str members to SSV_NAN and NULL respectively.
 * return values:
 *	0	success
 *	-1	null [ssvb]
 */
int ssv_block_init(struct ssv_block *b) {
	if(b == NULL) {
		error("ssv_block_init() received NULL [ssvb] ssv_block");
		return -1;
	}
	// clear the block
	b->title = NULL;
	b->col_is_const = 0;
	int i;
	for (i = 0; i<SSV_BLOCK_VALS; i++) {
		b->vals[i].num = SSV_NAN;
		b->vals[i].str = NULL;
	}
	b->blockDown = NULL;
	b->blockRight = NULL;
	return 0;
}


/// this will set a value in a ssv_file structure
// column 0 is the first column
// row 0 is the first row
// returns:
//	0	succes
//	-1	NULL [f] file  structure
//	-2	NULL [v] value structure
//	-3	problem getting to the right column
//	-4 	problem getting to the right row
//	-5	invalid column index
//	-6	invalid row index
int ssv_file_set_value(struct ssv_file *f, ssv_type column, ssv_type row, struct ssv_value *v) {
	
	// if the value pointer is bad
	if (f == NULL) {
		// report and error and return an error code
		error("ssv_file_set_value() was sent a bad [f] value!");
		return -1;
	}
	
	// if the value pointer is bad
	if (v == NULL) {
		// report and error and return an error code
		error("ssv_file_set_value() was sent a bad [v] value!");
		return -2;
	}
	
	if (column > f->columns) {
		error_d("ssv_file_set_value() [column] out of bounds of the ssv_file structure! [f] has this many columns:", f->columns);
		error_d("and [column] was received as: ",column);
		return -5;
	}
	
	if (row > f->rows) {
		error_d("ssv_file_set_value() [row] out of bounds of the ssv_file structure! [f] has this many rows:", f->rows);
		error_d("and [row] was received as: ",row);
		return -6;
	}
	
	// start at the origin block
	struct ssv_block *b = &(f->origin);
	
	ssv_type c;
	// navigate to the right column
	for (c = 0; c < column; c++) {
		b = b->blockRight;
		if (b == NULL) {
			error("ssv_file_set_value() could not navigate columns!");
			return -3;
		}
	}
	ssv_type r = row;
	while (r >= SSV_BLOCK_VALS) {
		b = b->blockDown;
		if (b == NULL) {
			error("ssv_file_set_value() could not navigate rows!");
			return -4;
		}
		r -= SSV_BLOCK_VALS;
	}
	
	// set the value
	b->vals[r].num = v->num;
	b->vals[r].str = v->str;
	
	// success
	return 0;
}


/// this will set a value in a ssv_file structure
// column 0 is the first column
// row 0 is the first row
// returns:
//	0	succes
//	-1	NULL [f] file  structure
//	-2	NULL [v] value structure
//	-3	problem getting to the right column
//	-4 	problem getting to the right row
//	-5	invalid column index
//	-6	invalid row index
//	-7	NULL value
int ssv_file_get_value(struct ssv_file *f, ssv_type column, ssv_type row, struct ssv_value *v){
	
	// if the file pointer is bad
	if (f == NULL) {
		// report and error and return an error code
		error("ssv_file_get_value() was sent a bad [f] value!");
		return -1;
	}
	
	if (column >= f->columns) {
		error("ssv_file_set_value() column out of bounds of the ssv_file structure");
		return -5;
	}
	
	if (row >= f->rows) {
		error("ssv_file_set_value() row out of bounds of the ssv_file structure");
		return -6;
	}
	// if the value pointer is bad
	if (v == NULL) {
		// report and error and return an error code
		error("ssv_file_get_value() was sent a bad [f] value!");
		return -7;
	}
	
	// start at the origin block
	struct ssv_block *b = &(f->origin);
	
	ssv_type c;
	// navigate to the right column
	for (c = 0; c < column; c++) {
		b = b->blockRight;
		if (b == NULL) {
			error("ssv_file_get_value() could not navigate columns!");
			return -3;
		}
	}
	
	ssv_type r = row;
	while (r >= SSV_BLOCK_VALS) {
		b = b->blockDown;
		if (b == NULL) {
			error("ssv_file_set_value() could not navigate rows!");
			return -4;
		}
		r -= SSV_BLOCK_VALS;
	}
	
	// set the value
	v->num = b->vals[r].num;
	v->str = b->vals[r].str;
	
	// success
	return 0;
}



/// create a new row of blocks in a ssv_file
// returns 
//	0	succes
//	-1	bad [f] ssv_file
//	-2	couldn't navigate columns of the ssv_file structure
//	-3	couldn't navigate rows of the ssv_file structure
int ssv_file_row_create(struct ssv_file *f, ssv_type r) {
	// if the value pointer is bad
	if (f == NULL) {
		// report and error and return an error code
		error("ssv_file_row_create() was sent a bad [f] file structure!");
		return -1;
	}
	
	// keeps track of col and row
	ssv_type col; 
	ssv_type row;
	// keeps track of which column we are on
	struct ssv_block *bcol = &(f->origin);
	// keeps track of what row we are on when on a single column
	struct ssv_block *brow;
	
	// for every column
	for (col = 0; col < f->columns; col++) {
		// if this is not the first column,
		if (col != 0) {
			// move one block (column) right (advance one column to the right)
			bcol = bcol->blockRight;
		}
		// make sure you aren't stepping into the wastelands
		if (bcol == NULL) {
			error("ssv_file_row_create() couldn't navigate columns!");
			return -2;
		}
		
		// start at the top row of the column
		brow = bcol;
		for (row = 0; row < r; row++) {
			// if you are not 
			if (row != 0) {
				brow = brow->blockDown;
			}
			if (brow == NULL) {
			error("ssv_file_row_create() couldn't navigate rows!");
			return -3;
			}
		}
		// create a new block at the bottom of the list
		brow->blockDown = ssv_block_create();
		
	}
	
	// success
	return 0;
}


/// this calculates max and min for each column and figures out which columns have all the same data
// [f] is a pointer to the ssv_file
// returns:
//	[0]		succes
//	[-1] 	if the file was bad
//	[-2]	if it encountered difficulty navigating the rows
//	[-3]	if it encounteder difficulty navigating the columns
ssv_type ssv_file_find_constants_max_min(struct ssv_file *f) {
	
	ssv_type constants_found = 0;
	
	// if the ssv_file pointer is bad
	if (f == NULL) {
		// report and error and return an error code
		error("ssv_file_find_constants() was sent a bad [f] file structure!");
		return -1;
	}
	
	// this keeps track of if the current column is constant
	ssv_type constant;
	// start at the origin block
	struct ssv_block *col = &(f->origin);
	struct ssv_block *row = NULL;
	// keep track of what row and column you are on
	ssv_type r,c;
	// this keeps track of the current value's string
	char *str = NULL;
	// this keeps track of the current value's number
	double num;
	// this keeps track of the first string in a column
	char *str_first = NULL;
	// this keeps track of the max and min values for the current column
	double cmax, cmin;
	// navigate to the right column
	for (c = 0; c < f->columns; c++) {
		// if this is not the first block you encounter
		if(c != 0) {
			// move one block to the right
			col = col->blockRight;
		}
		
		// make sure the block you just moved to is not NULL
		if (col == NULL) {
			error("ssv_file_set_value() could not navigate columns!");
			error_d("r = ",r);
			error_d("c = ",c);
			return -2;
		}
		// for each column, start at the top of it
		row = col;
		// assume: current row is constant, and try to prove that wrong
		constant = 1;
		// get the first string
		str_first = col->vals[0].str;
		// begin by assuming the maximum is the first element,
		// then try to find something bigger  in this column
		cmax = col->vals[0].num;
		// begin by assuming the minimum is the first element,
		// then try to find something smaller in this column
		cmin = col->vals[0].num;
		// and work you way to the bottom, but stop looking as soon as you find 
		// just a single value that isn't the same as all the others
		for (r = 0; r < f->rows; r++) {
			// if this is NOT the first row you encounter,
			// and if you just stepped past a block boundary,
			if ( (r != 0) && (r%SSV_BLOCK_VALS == 0) ) {
				// advance down one block in the list
				row = row->blockDown;
			}
			// make sure the block you just moved to is not NULL
			if (row == NULL) {
				error("ssv_file_set_value() could not navigate rows:");
				error_d("r = ",r);
				error_d("c = ",c);
				return -3;
			}
			
			//------------------------------------------------------------------
			// check to see if the column is still constant
			//------------------------------------------------------------------
			
			// if you still think the column might be constant, keep trying to
			// disprove that assumption
			if (constant) {
				// save the string in this variable for brevity
				str = row->vals[r%SSV_BLOCK_VALS].str;
				if (str == str_first) {
					// we know that they point to the same location, so we don't
					// have to evaluate whether or not the actual string is the same
				}
				else if (str != NULL) {
					// if this entry differs from the first one,
					if (strcmp(str,str_first)) {
						// record that the row was not constant. This will break out of
						// the for(r) loop (but not the for(c) loop! we still need to
						// check the other columns :P
						constant = 0;
					}
				}
			}
			
			//------------------------------------------------------------------
			// find max & min
			//------------------------------------------------------------------
			num = row->vals[r%SSV_BLOCK_VALS].num;
			// if the current value is a number,
			if ( IS_NUM(num) ) {
				// it doesn't matter if cmax and cmin are NAN to begin with;
				// NAN will NEVER produce a valid comparison
				if (num > cmax) cmax = num;
				if (num < cmin) cmin = num;
			}
			
			// if they do not point to the same place, and the current one is NULL
			else {
				constant = 0;
			}
		}
		// record if the column is constant at the top of the column
		if(constant) {
			col->col_is_const = 1;
			constants_found++;
			ssvlog_s("Found constant column: ",col->title);
		}
		else {
			col->col_is_const = 0;
		}
		
		// record the max and min values of the column at the  top of the column
		col->cmax = cmax;
		col->cmin = cmin;
		// report max and min
		ssvlog_s("Column = ",col->title);
		ssvlog_f("Max = ",col->cmax);
		ssvlog_f("min = ",col->cmin);
		
	}
	
	return constants_found;
}


/// finds the top block in a column you specify
// returns a pointer to the top block in a column
struct ssv_block *ssv_file_get_column_top(struct ssv_file *f, ssv_type col){
	
	// if the ssv_file pointer is bad
	if (f == NULL) {
		// report and error and return an error code
		error("ssv_file_get_column() was sent a bad [f] file structure!");
		return NULL;
	}
	// if the column was out of bounds
	if ( col >= f->columns) {
		error_d("ssv_file_get_column() sent [col] greater than or equal to the number of columns in [f]! f->columbs =",f->columns);
		error_d("ssv_file_get_column() col = ",col);
		return NULL;
	}
	
	ssv_type c;
	// start at the origin
	struct ssv_block *b = &f->origin;;
	// navigate to the correct column to get the column's metadata
		for (c = 0; c < col; c++) {
			b = b->blockRight;
			if (b == NULL) {
				error_d("ssv_file_get_column() could not navigate columns! column =",c);
				return NULL;
			}
		}
	// return a pointer to the block at the top of the column the caller requested
	return b;
}
