//A simple program to demonstrate how the benchmark works.

#include <stdio.h>
#include <limits.h>

int main() {	//method being tested, swap or add methods to this file to test different code examples

	int x, y;
	for (int i = 12; i < INT_MAX/4 - 1; i += 2) {
		x = 1 + 2;
		y = x + 1 + 2;
	}
	if (x > y) {
		return 0;
	} else {
		return 1;
	}
}
