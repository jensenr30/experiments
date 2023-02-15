#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS     5


void *PrintHello(void *threadid)
{
	long tid;
	tid = (long)threadid;
	printf("Hello World! It's me, thread #%ld!\n", tid);
	pthread_exit(NULL);
	return 0;
}

int main (int argc, char *argv[])
{
	pthread_t threads;
	int rc;
	printf("In main: creating thread %d\n", 1);
	rc = pthread_create(&threads, NULL, PrintHello, (void *)1);
	if (rc){
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(-1);
	}

	/* Last thing that main() should do */
	pthread_exit(NULL);
	return 0;
}
