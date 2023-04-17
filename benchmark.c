#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define ITERATIONS 20		//number of times the code is run
#define NEATDISPLAY true	//sets if results will be output in a table or plain numbers; true = table, false = plain

int main(void) {
	struct timespec start, end;		//timespec objects used to mark start and end times
	double iterData[ITERATIONS];		//array to store each iteration's runtime
	double sum = 0;				//rolling sum to calculate mean time
	
	printf("Running benchmark %d times...\n", ITERATIONS);
	
	for(int i = 0; i < ITERATIONS; i++) {
		clock_gettime(CLOCK_REALTIME, &start);
		//cap_ex_5Opt();			//change this method to whatever method you're using
		clock_gettime(CLOCK_REALTIME, &end);
		iterData[i] = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000;	//this calculates the runtime in seconds (with 6 decimals of precision)
		sum += iterData[i];		//add to sum to calculate mean runtime
	}
	
	printf("Benchmark complete!\n\n");
	
	if(NEATDISPLAY) {			//displays results of benchmark in neat table
		printf("Iteration Runtimes:\n ID|Runtime (sec)\n---|-------------\n");
		for(int i = 0; i < ITERATIONS; i++) {
			printf("%3d|%f\n", i + 1, iterData[i]);
		}
	}
	else {					//displays results of benchmark in plain numbers
		for(int i = 0; i < ITERATIONS; i++) {
			printf("%f\n", iterData[i]);
		}
	}
	
	printf("Mean runtime: %f seconds\n", sum/ITERATIONS);
}
