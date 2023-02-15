

#include <stdio.h>


int main(){
	
	// this is the target number of iterations
	unsigned long long N;
	// this is the maximum number of iterations I want the code to run through
	//keep track of the iterations
	unsigned long long maxN = (unsigned long long)-1;
	unsigned long long n;
	
	// start pi at one so it can be multiplied by the oncoming product series.
	long double pi = 1;
	
	
	n = 1; pi=1;
	for(N=1; N<=maxN; N*=2){
		for(; n<=N; n++){
			pi *= ((long double)(4*n*n))/((long double)((2*n-1)*(2*n+1)));
			//printf("pi = %f\n",pi*2.0f);
		}
		printf("%.1e iterations: \tpi = %.12Lf\n",(double)N,(double)pi*2.0f);
	}
	
	
	
	system("pause>nul");
	return 0;
}
