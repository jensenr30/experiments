#include "error.h"
#include <stdio.h>

void handle_error(int errFlag, char *errMsg){
	
	printf("Error %3d: ", errFlag);
	
	switch(errFlag){
	case e_failure_to_find_new_name:
		printf("Failure to make new name for new lifeform!\n");
		break;
	case e_malloc:
		printf("Failure to allocate more memory!\n");
	default:
		printf("Unknown Error!\n");
		break;
	}
	printf("errMsg = \"%s\"",errMsg);
}
