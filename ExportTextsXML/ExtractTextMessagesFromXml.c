
/* ExtractTestMessagesFromXml
 * Ryan Jensen
 * 2016-11-26
 * 
 * The purpose of this program is to parse an .xml file and export a .csv file.
 * I have this xml file that was generated using a program on my phone.
 * Program = "SMS Backup & Restore". It is an android app.
 * This file has an .xml format that is text and looks like this:
 * 
 * 
 */


//------------------------------------------------------------------------------
// headers
//------------------------------------------------------------------------------
#include <windows.h>
#include <stdio.h>
#include <inttypes.h>
#include <time.h>

//------------------------------------------------------------------------------
// function definitions
//------------------------------------------------------------------------------
#define END_PROGRAM(i) printf("Program Exit %d\nPress Enter to exit the program...",i);getchar();return i;

#ifdef _WIN32
void mkdir(char *dir)
{
	CreateDirectory(dir,NULL);
}
#endif


// this file will search until it finds your pattern in the text file
int ffind(FILE *fp, char *pattern)
{
	char c;
	char match = 0;
	unsigned int pati = 0;
	
	while(!match && !feof(fp))
	{
		c = fgetc(fp);
		// if this character matches the pattern,
		if(c == pattern[pati])
		{
			// start looking for the next character in the pattern
			pati++;
			// if you reached the end of your pattern,
			if(pattern[pati] == '\0' || pattern[pati] == '\n')
			{
				// you have found a match. This will exit the while loop.
				match = 1;
			}
		}
		// if this character does not match the pattern,
		else
		{
			// start looking from the beginning again.
			pati = 0;
		}
	}
	
	return feof(fp);
}


// this will return a pointer to a string read from a file. A string is either
// "this type of string" 
// or 
// 'this type of string'
// returns a 
int fgetstring(FILE *fp,char *buf, int bufsize)
{
	
	char gotstr = 0;
	int i;
	char termchar;
	
	buf[0] = fgetc(fp);		// get the first termination character
	buf[bufsize-1] = '\0';	// it is terminated no matter what.
	
	// quit if you don't find the beginning of a string.
	if( (buf[0] != '\'') && (buf[0] != '"') ) return 0;
	
	
	// remember which character is going to terminate this string
	termchar = buf[0];
	
	i = 0;
	// while you are still looking for a string to get,
	while(!feof(fp) && i < bufsize)
	{
		buf[i] = fgetc(fp);			// grab a char from the input file
		if(buf[i] == termchar)		// if it is the termination char,
		{
			break;						// quit looking for more chars
		}
		i++;						// place next char in next index of the array
	}
	
	buf[i] = '\0';					// always terminate strings. This will normally overwrite the termchar, unless the while loop terminates from feof or i+1 error. in which case the termchar was not found before other things limited the search.
	
	return 1;
	
}



// copied from stackexchange from user=Superlokkus
char* replace_char(char* str, char find, char replace){
    char *current_pos = strchr(str,find);
    while (current_pos){
        *current_pos = replace;
        current_pos = strchr(current_pos,find);
    }
    return str;
}


int main(int argc, char *argv[])
{
	#ifdef _WIN32
	printf("Program Compiled on Windows Platform.\n");
	#else
	printf("Program compiled on unknown platform.\n");
	#endif
	// the first argument is the program name itself.
	// if there is only one argument, the user did not call this program with any input file.
	if(argc < 2)
	{
		// so tell the user they are a dumbass.
		printf("You didn't give me The first argument you pass me must be a filename!\n");
		END_PROGRAM(-1);
	}
	
	printf("Trying to open file=\"%s\"\n",argv[1]);
	
	// try to open the file
	
	
	FILE *fp = fopen(argv[1],"r");
	
	if(fp == NULL)
	{
		printf("Coudn't open file.\n");
		END_PROGRAM(-2);
	}
	else
	{
		printf("File opened!\n");
	}
	
	uint32_t line = 0;
	char address[30];
	char date[10];
	char type[10];
	char body[5000];
	char contact_name[100];
	char file_name[200];
	FILE *out = NULL;
	char lasttype = '0';
	time_t lasttime;
	time_t datetime;
	
	mkdir("conversations");
	
	while(!feof(fp))
	{
		ffind(fp,"address=");
		fgetstring(fp,address,30);
		printf("______________________________________________\n");
		printf("address =      %s\n",address);
		
		ffind(fp,"date=");
		fgetstring(fp,date,10);
		printf("date =         %s\n",date);
		datetime = atoi(date);
		printf("datetime =     %d\n",datetime);
		printf("Date =         %s\n",ctime(&datetime));
		
		
		ffind(fp,"type=");
		fgetstring(fp,type,10);
		printf("type =         %s\n",type);
		
		ffind(fp,"body=");
		fgetstring(fp,body,5000);
		printf("body =         %s\n",body);
		replace_char(body,'%','p');
		
		ffind(fp,"contact_name=");
		fgetstring(fp,contact_name,100);
		printf("contact_name =         %s\n",contact_name);
		
		
		
		
		
		strcpy(file_name,"conversations\\");
		strcat(file_name,contact_name);
		strcat(file_name,".txt");
		out = fopen(file_name,"a");
		
		// if the message changed from being sent / received, print another newline.
		if(lasttype != type[0]) fprintf(out,"________________________________\n");
		
		if(lasttype != type[0] || datetime-lasttime > 120)
		fprintf(out,"%s",ctime(&datetime));
		// if you sent the message
		if(type[0] == '2')
		{
			fprintf(out,"                           Ryan:  ");
		}
		// if you received the message
		else
		{
			fprintf(out,"                         Them  :  ");
		}
		
		// print the message that was sent/received.
		fprintf(out,body);
		
		// print a terminating newline
		fprintf(out,"\n");
		
		// record what the last type was
		lasttime = datetime;
		lasttype = type[0];
		line++;
		//if(line >= 10) break;
		fclose(out);
	}
	
	if(feof(fp)) printf("\nReached the end of input file! Processing Complete!\n\n");
	fclose(fp);
	return 0;
 }
