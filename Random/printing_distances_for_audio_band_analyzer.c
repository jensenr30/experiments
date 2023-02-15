#include <stdio.h>

int main(){
	FILE *output;
	output = fopen("output.txt","w");
	fprintf(output,"10 Lines:\n");
	int i;
	float j;
	j=1.5;
	for(i=0; i<10; i++){
 		fprintf(output,"%f\n",j);
 		j+=1.25;
	}
	
	fprintf(output,"\n16 Lines:\n");
	j=1.5;
	for(i=0; i<16; i++){
 		fprintf(output,"%f\n",j);
 		j+=1.25;
	}
	fclose(output);
	return 0;
}
