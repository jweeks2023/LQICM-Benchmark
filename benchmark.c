#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#define ITERATIONS 		20					//number of times each file is benchmarked (default: 20)
#define OUTPUTTYPE 		2					//sets if results will be output in a table or plain numbers; 0 = plain, 1 = table, 2 = CSV format
#define COMPILER 		"clang-15"			//specifies what compiler version you're using (default: clang-15)
#define COMPILERPATH	"../../../usr/bin/"	//filepath of the compiler defined above (default: "../../../usr/bin/")
#define INPUTFOLDER 	"./CodeToTest/"		//filepath for folder containing files to test (default: " ./CodeToTest/")
#define OUTPUTFOLDER 	"./Outputs/"		//filepath for folder containing results of benchmark (default: "./Outputs/")
#define OPTLEVEL 		"O0"				//the level of optimization the code being benchmarked is (default: O0)
#define MAXFILES		100					//the max number of files the benchmark will check for (default: 100)
#define MAXFILENAME		256					//the max number of characters in a filename

int compare(const void *a, const void *b) {	//Comparison method for quicksort function
    const char *fileA = (const char *)a;
    const char *fileB = (const char *)b;
    return strcmp(fileA, fileB);
}

//Method to find the median of an array
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

char* GenerateTimestamp() {							//generates the timestamp for output files
	time_t rawtime;
	struct tm *curTime;
	char *timestamp;
	
	time(&rawtime);
	curTime = localtime(&rawtime);						//sets time to current time, then stores it
	strftime(timestamp,20,"%Y-%m-%d %H%M%S", curTime);	//constructs timestamp in YYYY-MM-DD HHMMSS format (HH in 24hr form)
	return timestamp;
}

//Grabbing timestamp based on guide here: https://www.tutorialspoint.com/c_standard_library/c_function_strftime.htm
int OutputToFile(double dataArray[], char codeName[], double mean, double median, int ctr) {
	FILE *fileptr;
	char fileName[80];
	
	if (OUTPUTTYPE == 2) {								//constructs filepath, with final format being "output YYYY-MM-DD HHMMSS.txt (or .csv)"
		snprintf(fileName, sizeof fileName, "%soutput%d %s.csv", OUTPUTFOLDER, ctr, GenerateTimestamp());	
	}
	else {
		snprintf(fileName, sizeof fileName, "%soutput%d %s.txt", OUTPUTFOLDER, ctr, GenerateTimestamp());
	}
	
	fileptr = fopen(fileName, "w");						//creates file
	if (fileptr == NULL) {
		printf("File output failed.");
		return 0;
	}
	
	if(OUTPUTTYPE == 1) {									//outputs results of benchmark in neat table
		fprintf(fileptr, "Benchmark Results of %s\n", codeName);
		fprintf(fileptr, "Iteration Runtimes:\n ID|Runtime (sec)\n---|-------------\n");
		for(int i = 0; i < ITERATIONS; i++) {
			fprintf(fileptr, "%3d|%f\n", i + 1, dataArray[i]);
		}
		fprintf(fileptr, "Mean runtime: %f\n", mean);
		fprintf(fileptr, "Median runtime: %f\n", median);
	}
	else if(OUTPUTTYPE == 2) {								//outputs results of benchmark in CSV format
		fprintf(fileptr, "%s\n", codeName);
		fprintf(fileptr, "Iterations, Runtime\n");
		for(int i = 0; i < ITERATIONS; i++) {
			fprintf(fileptr, "%d,%f\n", i + 1, dataArray[i]);
		}
		fprintf(fileptr, "Mean:, %f\n", mean);
		fprintf(fileptr, "Median:, %f\n", median);
	}
	else {													//outputs results of benchmark in plain format
		fprintf(fileptr, "Benchmark Results of %s\n", codeName);
		for(int i = 0; i < ITERATIONS; i++) {
			fprintf(fileptr, "%f\n", dataArray[i]);
		}
		fprintf(fileptr, "Mean runtime: %f\n", mean);
		fprintf(fileptr, "Median runtime: %f\n", median);
	}
	
	fclose(fileptr);
	return 1;
}

int OutputAllData(char fileNames[MAXFILES][MAXFILENAME], double means[MAXFILES], double medians[MAXFILES]) {
	FILE *fileptr;
	char fileName[80];
	
	if (OUTPUTTYPE == 2) {								//constructs filepath, with final format being "output YYYY-MM-DD HHMMSS.txt (or .csv)"
		snprintf(fileName, sizeof fileName, "%ssummary %s.csv", OUTPUTFOLDER, GenerateTimestamp());	
	}
	else {
		snprintf(fileName, sizeof fileName, "%soutput %s.txt", OUTPUTFOLDER, GenerateTimestamp());
	}
	
	fileptr = fopen(fileName, "w");						//creates file
	if (fileptr == NULL) {
		printf("File output failed.");
		return 0;
	}
	
	fprintf(fileptr, "Benchmark Summary\n");
	if(OUTPUTTYPE == 1) {									//outputs results of benchmark in neat table
		fprintf(fileptr, "%15s|Avg Runtime (sec)|Median Runtime\n---------------|-----------------|-----------------\n", "Filename");
		for(int i = 0; i < ITERATIONS; i++) {
			if(fileNames[i][0] != '\0') {
				fprintf(fileptr, "%15s|%f%9s|%f\n", fileNames[i], means[i], "", medians[i]);
			}
		}
	}
	else if(OUTPUTTYPE == 2) {								//outputs results of benchmark in CSV format
		fprintf(fileptr, "Filename,");
		for(int i = 0; i < ITERATIONS; i++) {
			if(fileNames[i][0] != '\0') {
				fprintf(fileptr, "%s,", fileNames[i]);
			}
		}
		fprintf(fileptr, "\nAvg Runtime (sec),");
		for(int i = 0; i < ITERATIONS; i++) {
			if(means[i] != 0) {
				fprintf(fileptr, "%f,", means[i]);
			}
		}
		fprintf(fileptr, "\nMedian Runtime (sec),");
		for(int i = 0; i < ITERATIONS; i++) {
			if(medians[i] != 0) {
				fprintf(fileptr, "%f,", medians[i]);
			}
		}
	}
	else {													//outputs results of benchmark in plain format
		fprintf(fileptr, "Filename\t\t");
		for(int i = 0; i < ITERATIONS; i++) {
			if(fileNames[i][0] != '\0') {
				fprintf(fileptr, "%s\t", fileNames[i]);
			}
		}
		fprintf(fileptr, "\nAvg Runtime (sec)\t");
		for(int i = 0; i < ITERATIONS; i++) {
			if(means[i] != 0) {
				fprintf(fileptr, "%f\t", means[i]);
			}
		}
		fprintf(fileptr, "\nMedian Runtime (sec)\t");
		for(int i = 0; i < ITERATIONS; i++) {
			if(medians[i] != 0) {
				fprintf(fileptr, "%f\t", medians[i]);
			}
		}
	}

	fclose(fileptr);
	return 1;
}

//benchmark.c
int main(void) {
	struct timespec start, end;							//timespec objects used to mark start and end times
	struct dirent *entry;   							//Will grab info on things found in the directory
    DIR *dirObj;           								//The directory object
	dirObj = opendir(INPUTFOLDER);     					//Opens the directory
	char exe[50];
	snprintf(exe, sizeof exe, "%stestExe", INPUTFOLDER);//string that contains the command to run the generated executable during the benchmark
	char rm[50];
	snprintf(rm, sizeof rm, "rm %stestExe",INPUTFOLDER);//string that contains the command to remove the exe after benchmark is complete
	int ctr = 0;
	char fileNames[MAXFILES][MAXFILENAME];				//Array of all the file names
	double iterData[MAXFILES][ITERATIONS];				//Iteration data for files
	double fileMeans[MAXFILES];							//All the mean times
	double fileMedians[MAXFILES];						//All the median times

    if(dirObj == NULL){         						//If the directory is missing or been removed from the parent directory...
        printf("CodeToTest directory does not exist, or has been removed from the parent directory.");
        return -1;
    }

    while((entry=readdir(dirObj))){      				//Read the directory
        if(strstr(entry->d_name, ".C") || strstr(entry->d_name, ".c")){	//If the file is a C file...
			strncpy(fileNames[ctr], entry->d_name, MAXFILENAME - 1);	//Save file name
			fileNames[ctr][MAXFILENAME - 1] = '\0';		//Append empty char to the end
			ctr++;
        }
    }
	closedir(dirObj);   								//Close the directory
	qsort(fileNames, ctr, MAXFILENAME, compare);		//Sorts list of names
	
	for(int i = 0; i < ctr; i++) {
		double sum = 0;
		char file[100];
		snprintf(file, sizeof file, "%s%s %s%s -%s -o %stestExe", COMPILERPATH, COMPILER, INPUTFOLDER, fileNames[i], OPTLEVEL, INPUTFOLDER); //Create the CMD command to compile
		system(file);    							//Create the executable for the C file
		
		printf("Running benchmark for %s...", fileNames[i]);
		fflush(stdout);
		
		for(int j = 0; j < ITERATIONS; j++) {
			clock_gettime(CLOCK_REALTIME, &start);
			
			system(exe);							//actually runs the file we compiled
			
			clock_gettime(CLOCK_REALTIME, &end);
			iterData[i][j] = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;	//this calculates the runtime in seconds (with 6 decimals of precision)
			sum += iterData[i][j];
		}
		fileMeans[i] = sum / ITERATIONS;
		fileMedians[i] = Median(iterData[i]);
		printf("Done!\033[0;32m\u2713\033[0m\n");	//prints the green check :)
		OutputToFile(iterData[i], fileNames[i], fileMeans[i], fileMedians[i], i + 1);		
		system(rm);									//Delete the leftover executable
	}
	
	printf("Building summary...");
	sleep(1);
	OutputAllData(fileNames, fileMeans, fileMedians);
	printf("Done!\033[0;32m\u2713\033[0m\n");
	printf("Check the \"Outputs\" folder for results.\n");
	return 0;
}
