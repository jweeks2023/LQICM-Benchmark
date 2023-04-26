#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#define ITERATIONS 20		//number of times the code is run
#define NEATDISPLAY true	//sets if results will be output in a table or plain numbers; true = table, false = plain

double Median(double dataArray[]) {
	for (int i = 0; i < ITERATIONS; ++i){			//simple sorting loop to order array
	   for (int j = i + 1; j < ITERATIONS; ++j){
		  if (dataArray[i] > dataArray[j]){
			 double a = dataArray[i];
			 dataArray[i] = dataArray[j];
			 dataArray[j] = a;
		  }
	   }
	}
	
	return ITERATIONS % 2 == 0 ? (dataArray[ITERATIONS/2] + dataArray[(ITERATIONS/2) + 1]) / 2 : dataArray[ITERATIONS/2];	//if number of entries in array is even, return the average the two center entries, otherwise return the center entry
}

//Grabbing timestamp based on guide here: https://www.tutorialspoint.com/c_standard_library/c_function_strftime.htm
int OutputToFile(double dataArray[], double sum) {
	FILE *fileptr;
	time_t rawtime;
	struct tm *curTime;
	char timestamp[20];
	
	time(&rawtime);
	curTime = localtime(&rawtime);						//sets time to current time, then stores it
	
	strftime(timestamp,20,"%Y-%m-%d %H%M%S", curTime);	//constructs timestamp in YYYY-MM-DD HHMMSS format (HH in 24hr form)
	char fileName[80] = "./Outputs/output ";
	strcat(strcat(fileName, timestamp), ".txt");		//constructs filepath, with final format being "output YYYY-MM-DD HHMMSS.txt"
	
	fileptr = fopen(fileName, "w");						//creates file
	if (fileptr == NULL) {
		printf("File output failed.");
		return 0;
	}
	
	if(NEATDISPLAY) {									//outputs results of benchmark in neat table
		fprintf(fileptr, "Iteration Runtimes:\n ID|Runtime (sec)\n---|-------------\n");
		for(int i = 0; i < ITERATIONS; i++) {
			fprintf(fileptr, "%3d|%f\n", i + 1, dataArray[i]);
		}
	}
	else {												//outputs results of benchmark in plain numbers
		for(int i = 0; i < ITERATIONS; i++) {
			fprintf(fileptr, "%f\n", dataArray[i]);
		}
	}
	fprintf(fileptr, "Mean runtime: %f\n", sum/ITERATIONS);
	fprintf(fileptr, "Median runtime: %f\n", Median(dataArray));
	fclose(fileptr);
	return 1;
}

//benchmark.c
int main(void) {
	struct timespec start, end;							//timespec objects used to mark start and end times
	struct dirent *entry;   							//Will grab info on things found in the directory
	DIR *dirObj;           								//The directory object
	char path[50] = "./CodeToTest/";  					//The path of the Benchmarking code
	dirObj = opendir(path);     						//Opens the directory
	

	if(dirObj == NULL){         						//If the directory is missing or been removed from the parent directory...
		printf("CodeToTest directory does not exist, or has been removed from the parent directory.");
        	return -1;
    	}

    	while((entry=readdir(dirObj))){      				//Read the directory
		double iterData[ITERATIONS];					//array to store each iteration's runtime
		double sum = 0;
		if(strstr(entry->d_name, ".c")){    			//If the file is a C file...
		    char file[100] = "clang-15 ./CodeToTest/";
		    strcat(strcat(file,entry->d_name)," -O0 -o ./CodeToTest/testExe"); //Create the CMD command to compile (note that we're compiling with no opt)
		    system(file);    							//Create the executable for the C file

		    printf("Running benchmark for %s...", entry->d_name);
				fflush(stdout);

				for(int i = 0; i < ITERATIONS; i++) {
					clock_gettime(CLOCK_REALTIME, &start);

					system("./CodeToTest/testExe");			//actually runs the file we compiled

					clock_gettime(CLOCK_REALTIME, &end);
					iterData[i] = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;	//this calculates the runtime in seconds (with 6 decimals of precision)
					sum += iterData[i];
				}

				printf("Done!\033[0;32m\u221A\033[0m\n");	//prints the green check :)
				OutputToFile(iterData, sum);
				system("rm ./CodeToTest/testExe");    		//Delete the leftover executable
        	}
    	}
    
    	closedir(dirObj);   								//Close the directory
	printf("Check the \"Outputs\" folder for results.\n");
	return 0;
}
