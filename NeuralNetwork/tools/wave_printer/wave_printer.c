/*
	wave_printer.c
	Ryan Jensen
	2014-07-26
	
	The purpose of this software is to input a wave file and output floating point values from -1.0 to 1.0.
	these floating point values will be printed to a file with the same name as the input wave file, but with a .txt extension.
	
	
	This software is provided in the hopes that it is useful, BUT WITHOUT ANY WARRANTY.
	Run this software at your own risk.
*/


#include <stdio.h>
#include <string.h>
#include <inttypes.h>


// the wave file is imported as the first argument after the name of the executable itself.
int main(int argc, char *argv[])
{
	int i;
	
	// if there is no input file, just quit.
	if(argc == 1)
	{
		printf("no file\n");
		return -1;
	}
	
	printf("file to print to file = \"%s\"\n", argv[1]);
	
	// attempt to open the wave file
	FILE *fp = fopen(argv[1], "rb");
	// if the file could not be opened, quit.
	if(fp == NULL)
	{
		printf("could not open \"%s\"\n", argv[1]);
		return -2;
	}
	
	
	// create the output path
	char outputPath[512];
	strcpy(outputPath, argv[1]);
	strcat(outputPath, ".dat");
	// open the output path
	FILE *outputFile = fopen(outputPath, "w");
	
	
	if(outputFile == NULL)
	{
		printf("could not open \"%s\"\n", outputPath);
		return -3;
	}
	
	int16_t buffer;
	
	// read out all the shit before the number of channels
	for(i=0; i<12; i++)
	{
		fread(&buffer, 2, 1, fp);
	}
	// save the last read of the wave file (the buffer) to the "channels" variable.
	int16_t channels = buffer;
	
	// clear out the rest of the header shit from the wav file in order to get to the actual audio data
	for(i=0; i<10; i++)
	{
		fread(&buffer, 2, 1, fp);
	}
	
	printf("channels detected: %d\n",channels);
	if(channels > 1)
	{
		printf("More than one channel detected. Using only the left channel.\n");
	}
	
	// read and write all of the audio data
	while(!feof(fp))
	{
		// read in the data from the first channel
		fread(&buffer, 2, 1, fp);
		// print data to file 
		//fprintf(outputFile, "%d\n", buffer);
		//fprintf(outputFile, "%f\n", buffer/((float)(1<<15)));
		fwrite(&buffer, 2, 1, outputFile);
		
		// skip any other channels. only read in the first channel.
		for(i=1; i<channels; i++)
		{
			fread(&buffer, 2, 1, fp);
		}
	}
	
	printf("Done!\n");
	// close files
	fclose(fp);
	fclose(outputFile);
	
	// successfully printed wav file
	return 0;
}
