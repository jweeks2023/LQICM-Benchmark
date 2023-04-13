#include <time.h>
#include <stdio.h>
#include <limits.h>

#define BILLION  1000000000.0

int demo(int n) {

	int x, y;
	for (int i = 12; i < n - 1; i += 2) {
		x = 1 + 2;
		y = x + 1 + 2;
	}
	if (x > y) {
		return 0;
	} else {
		return 1;
	}
}

int main(void) {
	struct timespec start, end;
	int samples = 20;
	double iterData[samples];
	double sum = 0;
	printf("Running benchmark...\n");
	for(int i = 0; i < samples; i++) {
		clock_gettime(CLOCK_REALTIME, &start);
		demo(INT_MAX);
		clock_gettime(CLOCK_REALTIME, &end);
		iterData[i] = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / BILLION;
		sum += iterData[i];
	}
	printf("Benchmark complete!\n");
	printf("Iteration Runtimes:\n ID|Runtime (sec)\n---|-------------\n");
	for(int i = 0; i < samples; i++) {
		printf("%3d|%f\n", i + 1, iterData[i]);
	}
	printf("Mean Execution time after %d iterations: %f seconds\n", samples, sum/samples);
}
