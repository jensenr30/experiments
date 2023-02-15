#include <stdio.h>
// this is where the statistics related files will be stored
char *statsDir;
// this is the file type that the statistics file will have
char *statsExt;
// this is a file that is used to collect and record statistics
FILE *stats;



void init_stats();
