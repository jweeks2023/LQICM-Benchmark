#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#define ITERATIONS 		20					//number of times each file is benchmarked (default: 20)
#define OUTPUTTYPE 		2					//sets if results will be output in a table or plain numbers; 0 = plain, 1 = table, 2 = CSV format
#define OUTPUTTOGETHER	false					//specifies whether output will be in separate files or in one big file (default: true) (Only outputs in .csv if true)
#define COMPILER 		"clang-15"			//specifies what compiler version you're using (default: clang-15)
#define COMPILERPATH	"../../../usr/bin/"	//filepath of the compiler defined above (default: "../../../usr/bin/")
#define INPUTFOLDER 	"./CodeToTest/"		//filepath for folder containing files to test (default: " ./CodeToTest/")
#define OUTPUTFOLDER 	"./Outputs/"		//filepath for folder containing results of benchmark (default: "./Outputs/")
#define OPTLEVEL 		"ALL"				//the level of optimization the code being benchmarked is (default: 0)
#define MAXFILENAME		256					//the max number of characters in a filename (default: 256)
#define MAXFILEAMN		100					//the max number of files that can be processed by the benchmark (default: 100)

int MAXFILES = strcmp(OPTLEVEL, "ALL") == 0 ? MAXFILEAMN * 4 : MAXFILEAMN;	//specifies how many file runs can occur; based on OPTLEVEL

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
	char *timestamp = malloc(21);
	
	time(&rawtime);
	curTime = localtime(&rawtime);						//sets time to current time, then stores it
	strftime(timestamp, 20,"%Y-%m-%d %H%M%S", curTime);	//constructs timestamp in YYYY-MM-DD HHMMSS format (HH in 24hr form)
	return timestamp;
}

//Grabbing timestamp based on guide here: https://www.tutorialspoint.com/c_standard_library/c_function_strftime.htm
int OutputSingle(double dataArray[], char codeName[], double mean, double median, int ctr) {
	FILE *fileptr;
	char fileName[sizeof(OUTPUTFOLDER) + MAXFILENAME + 34];
	char *timestamp = GenerateTimestamp();
	
	for (int i = MAXFILENAME - 1; i >= 0; i--) {
        if (codeName[i] == '.') {
            codeName[i] = '\0';  // Replace period with null terminator
			break;
        }
    }
	
	if (OUTPUTTYPE == 2) {								//constructs filepath, with final format being "output YYYY-MM-DD HHMMSS.txt (or .csv)"
		snprintf(fileName, sizeof fileName, "%soutput%d %s %s.csv", OUTPUTFOLDER, ctr, codeName, timestamp);	
	}
	else {
		snprintf(fileName, sizeof fileName, "%soutput%d %s %s.txt", OUTPUTFOLDER, ctr, codeName, timestamp);
	}
	free(timestamp);
	
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

int OutputSummary(char fileNames[MAXFILES][MAXFILENAME], double means[MAXFILES], double medians[MAXFILES], int ctr) {
	FILE *fileptr;
	char fileName[sizeof(OUTPUTFOLDER) + 25];
	char *timestamp = GenerateTimestamp();

	if (OUTPUTTYPE == 2) {								//constructs filepath, with final format being "output YYYY-MM-DD HHMMSS.txt (or .csv)"
		snprintf(fileName, sizeof fileName, "%ssummary %s.csv", OUTPUTFOLDER, timestamp);	
	}
	else {
		snprintf(fileName, sizeof fileName, "%ssummary %s.txt", OUTPUTFOLDER, timestamp);
	}
	free(timestamp);
	
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
		for(int i = 0; i < ctr; i++) {
			if(fileNames[i][0] != '\0') {
				fprintf(fileptr, "%s,", fileNames[i]);
			}
		}
		fprintf(fileptr, "\nAvg Runtime (sec),");
		for(int i = 0; i < ctr; i++) {
			if(means[i] != 0) {
				fprintf(fileptr, "%f,", means[i]);
			}
		}
		fprintf(fileptr, "\nMedian Runtime (sec),");
		for(int i = 0; i < ctr; i++) {
			if(medians[i] != 0) {
				fprintf(fileptr, "%f,", medians[i]);
			}
		}
	}
	else {													//outputs results of benchmark in plain format
		fprintf(fileptr, "Filename\t\t");
		for(int i = 0; i < ctr; i++) {
			if(fileNames[i][0] != '\0') {
				fprintf(fileptr, "%s\t", fileNames[i]);
			}
		}
		fprintf(fileptr, "\nAvg Runtime (sec)\t");
		for(int i = 0; i < ctr; i++) {
			if(means[i] != 0) {
				fprintf(fileptr, "%f\t", means[i]);
			}
		}
		fprintf(fileptr, "\nMedian Runtime (sec)\t");
		for(int i = 0; i < ctr; i++) {
			if(medians[i] != 0) {
				fprintf(fileptr, "%f\t", medians[i]);
			}
		}
	}

	fclose(fileptr);
	return 1;
}

int OutputAll(char fileNames[MAXFILES][MAXFILENAME], double iterData[MAXFILES][ITERATIONS], double means[MAXFILES], double medians[MAXFILES], int ctr) {
	FILE *fileptr;
	char fileName[sizeof(OUTPUTFOLDER) + 35];
	char *timestamp = GenerateTimestamp();
	snprintf(fileName, sizeof fileName, "%soverall %s.csv", OUTPUTFOLDER, timestamp);
	free(timestamp);

	fileptr = fopen(fileName, "w");						//creates file
	if (fileptr == NULL) {
		printf("File output failed.");
		return 0;
	}

	fprintf(fileptr, "Filename,");
	for(int i = 0; i < ctr; i+=4) {
		if(fileNames[i][0] != '\0') {
			if(strcmp(OPTLEVEL, "ALL") == 0) {
				fprintf(fileptr, "%s,,,,", fileNames[i]);
			}
			else {
				fprintf(fileptr, "%s,", fileNames[i]);
			}
		}
	}
	
	fprintf(fileptr, "\nOpt Level,");
	for(int i = 0; i < ctr; i++) {
		if(fileNames[i][0] != '\0') {
			if(strcmp(OPTLEVEL, "ALL") == 0) {
				fprintf(fileptr, "O0,O1,O2,O3,");
				i += 3;
			}
			else {
				fprintf(fileptr, "O%d,", atoi(OPTLEVEL));
			}
		}
	}
	
	for(int i = 0; i < ITERATIONS; i++) {
		fprintf(fileptr, "\n%d,", i + 1);
		for(int j = 0; j < ctr; j++) {
			if(iterData[j][0] != 0) {
				fprintf(fileptr, "%f,", iterData[j][i]);
			}
		}
	}
	
	fprintf(fileptr, "\nAvg Runtime (sec),");
	for(int i = 0; i < ctr; i++) {
		if(means[i] != 0) {
			fprintf(fileptr, "%f,", means[i]);
		}
	}

	fprintf(fileptr, "\nMedian Runtime (sec),");
	for(int i = 0; i < ctr; i++) {
		if(medians[i] != 0) {
			fprintf(fileptr, "%f,", medians[i]);
		}
	}
	return 1;
}

int ValidCheck(char file[MAXFILENAME]) {				//Checks if file is valid program
	char cmd[MAXFILENAME + 19 + sizeof(COMPILERPATH) + sizeof(COMPILER) + sizeof(INPUTFOLDER)];
	snprintf(cmd, sizeof(cmd), "%s%s -Wall -Werror -c %s%s 2>&1", COMPILERPATH, COMPILER, INPUTFOLDER, file);
	FILE* output = popen(cmd, "r");						//First checks if it compiles
	if(!output) {										//If not, return -1
		return -1;
	}
	
	char buffer[256];									//Otherwise check output of compilation
	char* result = fgets(buffer, sizeof(buffer), output);
	pclose(output);
														//If it contains error or warning, return -1
	if(result && (strstr(buffer, "error") != NULL || strstr(buffer, "warning") != NULL)) {
		return -1;
	}
	
	return 0;											//All other (valid) programs return 0
}

//benchmark.c
int main(void) {
	struct timespec start, end;							//timespec objects used to mark start and end times
	struct dirent *entry;   							//Will grab info on things found in the directory
    DIR *dirObj;           								//The directory object
	dirObj = opendir(INPUTFOLDER);     					//Opens the directory
	char exe[sizeof(INPUTFOLDER) + 10];
	snprintf(exe, sizeof exe, "%stestExe", INPUTFOLDER);//string that contains the command to run the generated executable during the benchmark
	char rm[sizeof(INPUTFOLDER) + 12];
	snprintf(rm, sizeof rm, "rm %stestExe",INPUTFOLDER);//string that contains the command to remove the exe after benchmark is complete
	int ctr = 0;
	
	char fileNames[MAXFILES][MAXFILENAME];				//Array of all the file names
	double iterData[MAXFILES][ITERATIONS];				//Iteration data for files
	double fileMeans[MAXFILES];							//All the mean times
	double fileMedians[MAXFILES];						//All the median times
	
    if(dirObj == NULL){         						//If the directory is missing or been removed from the parent directory...
        printf("CodeToTest directory does not exist, or has been removed from the parent directory.");
        return EXIT_FAILURE;
    }

    while((entry=readdir(dirObj))){      				//Read the directory
        if(strstr(entry->d_name, ".C") || strstr(entry->d_name, ".c")){	//If the file is a C file...
			char file[MAXFILENAME];
			strncpy(file, entry->d_name, MAXFILENAME - 1);
			int res = ValidCheck(file);
			if(res == -1) {
				printf("File skipped due to errors/warnings\n");
			}
			else if(strcmp(OPTLEVEL, "ALL") == 0) {
				for(int i = 0; i < 4; i++) {
					strncpy(fileNames[ctr], entry->d_name, MAXFILENAME - 1);	//Save file name
					fileNames[ctr][MAXFILENAME - 1] = '\0';		//Append empty char to the end
					ctr++;
				}
			}
			else {
				strncpy(fileNames[ctr], entry->d_name, MAXFILENAME - 1);	//Save file name
				fileNames[ctr][MAXFILENAME - 1] = '\0';		//Append empty char to the end
				ctr++;
			}
        }
    }
	closedir(dirObj);   								//Close the directory
	qsort(fileNames, ctr, MAXFILENAME, compare);		//Sorts list of names
	
	
	for(int i = 0; i < ctr; i++) {
		double sum = 0;
		char opt[3];
		snprintf(opt, sizeof(opt), "O%d", strcmp(OPTLEVEL, "ALL") == 0 ? i % 4 : atoi(OPTLEVEL));
		
		char file[sizeof(COMPILERPATH) + sizeof(COMPILER) + (sizeof(INPUTFOLDER) * 2) + MAXFILENAME + 18];
		snprintf(file, sizeof file, "%s%s %s%s -%s -o %stestExe", COMPILERPATH, COMPILER, INPUTFOLDER, fileNames[i], opt, INPUTFOLDER); //Create the CMD command to compile
		system(file);    							//Create the executable for the C file
		
		printf("Running benchmark for %s with Opt Level %s...", fileNames[i], opt);
		fflush(stdout);
		
		for(int j = 0; j < ITERATIONS; j++) {
			printf("%d", j + 1);
			fflush(stdout);
			clock_gettime(CLOCK_REALTIME, &start);
			
			system(exe);							//actually runs the file we compiled
			
			clock_gettime(CLOCK_REALTIME, &end);
			iterData[i][j] = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;	//this calculates the runtime in seconds (with 6 decimals of precision)
			sum += iterData[i][j];
		}
		fileMeans[i] = sum / ITERATIONS;
		fileMedians[i] = Median(iterData[i]);
		printf("Done!\033[0;32m\u2713\033[0m\n");	//prints the green check :)
		if(OUTPUTTOGETHER != 1) {
			OutputSingle(iterData[i], fileNames[i], fileMeans[i], fileMedians[i], i + 1);	
		}
		
		system(rm);									//Delete the leftover executable
	}
	
	OutputAll(fileNames, iterData, fileMeans, fileMedians, ctr);
	printf("Building summary...");
	OutputSummary(fileNames, fileMeans, fileMedians, ctr);
	printf("Done!\033[0;32m\u2713\033[0m\n");
	printf("Check the \"Outputs\" folder for results.\n");
	
	return EXIT_SUCCESS;
}
