#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

#define ITERATIONS 20		//number of times the code is run
#define NEATDISPLAY true	//sets if results will be output in a table or plain numbers; true = table, false = plain

//Grabbing timestamp based on guide here: https://www.tutorialspoint.com/c_standard_library/c_function_strftime.htm
int OutputToFile(double dataArray[], int arraySize) {
	FILE *fileptr;
	time_t rawtime;
	struct tm *curTime;
	char timestamp[20];
	
	time(&rawtime);					//getting timestamp data and constructing timestamp
	curTime = localtime(&rawtime);
	strftime(timestamp,20,"%Y-%m-%d %H%M%S", curTime);
	
	char fileName[80] = "./Outputs/output ";
	strcat(strcat(fileName, timestamp), ".txt");	//generating filepath for output
	
	fileptr = fopen(fileName, "w");			//creating the file and opening it
	if (fileptr == NULL) {
		printf("File output failed.");
		return 0;
	}
	
	for(int i = 0; i < arraySize; i++) {		//storing contents of benchmark array into file
		fprintf(fileptr, "%f\n", dataArray[i]);
	}
	
	fclose(fileptr);
	return 1;
}

//benchmark.c
int main(void) {
	struct timespec start, end;			//timespec objects used to mark start and end times
	double iterData[ITERATIONS];		//array to store each iteration's runtime
	double sum = 0;						//rolling sum to calculate mean time
	
	printf("Running benchmark %d times...\n", ITERATIONS);
	
	for(int i = 0; i < ITERATIONS; i++) {
		clock_gettime(CLOCK_REALTIME, &start);
		
		demo(INT_MAX/4);				//change this method to whatever method you're using
		
		clock_gettime(CLOCK_REALTIME, &end);
		iterData[i] = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;	//this calculates the runtime in seconds (with 6 decimals of precision)
		sum += iterData[i];				//add to sum to calculate mean runtime
	}
	
	printf("Benchmark complete!\n\n");
	
	if(NEATDISPLAY) {					//displays results of benchmark in neat table
		printf("Iteration Runtimes:\n ID|Runtime (sec)\n---|-------------\n");
		for(int i = 0; i < ITERATIONS; i++) {
			printf("%3d|%f\n", i + 1, iterData[i]);
		}
	}
	else {								//displays results of benchmark in plain numbers
		for(int i = 0; i < ITERATIONS; i++) {
			printf("%f\n", iterData[i]);
		}
	}
	
	printf("Mean runtime: %f seconds\n", sum/ITERATIONS);
	
	printf("Exporting output to file...");
	OutputToFile(iterData, ITERATIONS);
	printf("Export complete.\n");
}
