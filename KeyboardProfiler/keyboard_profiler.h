

// This is returned when there are no input documents to run statistics on.
#define KEYPROF_NO_INPUT_FILES_PASSED 0xdeadbeef
#define KEYPROF_LOG_FILE_NAME "keyboard_log.txt"
#define KEYPROF_KEYS 36
int keyboard_profiler(int argc, char *argv[]);

#define KEYPROF_FILE_NOT_FOUND 404
#define KEYPROF_WORD_LENGTH_MAX 31
short keyprof_crunch_file(unsigned long long int *keyData, unsigned long long int *keyFrequency, unsigned long long int *keyStartingFrequency, unsigned long long int *wordLength, char *filePath, char includeSymbols, char keystrokeMode);

#define KEYPROF_OUTPUT_NAME_DEFAULT "key_statistics.txt"
short keyprof_save_stats(unsigned long long int *keyData, unsigned long long int *keyFrequency, unsigned long long int *keyStartingFrequency, unsigned long long int *wordLength, char *filePath);
short keyprof_load_stats(char *filePath, unsigned long long int *keyData);


/// these are all of the command line options that are available
// if this option is seen, the next argument will be taken as the output path to shove the data into.
#define KEYPROF_OPT_OUTPUT_PATH				"--output-file"
#define KEYPROF_OPT_OUTPUT_PATH_SHORT		"-f"
// this option will make the program erase the output file if it has any data already in it.
// the default action is to add the data to it each time.
#define KEYPROF_OPT_OVERWRITE				"--overwrite"
#define KEYPROF_OPT_OVERWRITE_SHORT			"-o"
// 
#define KEYPROF_OPT_INCLUDE_SYMBOLS			"--include-symbols"
#define KEYPROF_OPT_INCLUDE_SYMBOLS_SHORT	"-s"

#define KEYPROF_OPT_KEYSTROK_MODE			"--keystroke-mode"
#define KEYPROF_OPT_KEYSTROK_MODE_SHORT		"-k"

// this is a string of the valid character.
// it is set up so that the first half is the lowercase values of each key and the second half is the uppercase values of each key.
char *keyDataString;

/*
these are the following keys that will be logged and their respective locations in keyData arrays
these are the only keys that I am able to switch around, so these are the only ones I care about
There are 36 keys, and 36*2 possible characters (because each key has an upper and lower case value)
However, I don't really care about what value was pressed, I'm much more interested in the key.

00	a	A
01	b	B
02	c	C
03	d	D
04	e	E
05	f	F
06	g	G
07	h	H
08	i	I
09	j	J
10	k	K
11	l	L
12	m	M
13	n	N
14	o	O
15	p	P
16	q	Q
17	r	R
18	s	S
19	t	T
20	u	U
21	v	V
22	w	W
23	x	X
24	t	Y
25	z	Z
26	`	~
27	-	_
28	=	+
29	[	{
30	]	}
31	;	:
32	'	"
33	,	<
34	.	>
35	/	?

*/




