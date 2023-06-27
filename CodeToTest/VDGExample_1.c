//VDG Example from Paper

#include <stdio.h>
#include <limits.h>

int main(){ 
	volatile int j, s;
	volatile int i = 0;
	volatile int x = 42;
	volatile int y = 5;
	volatile int a = 12;

	while(i < 1000000000){
		j = 0;
		s = 1;
		while(j<y){
			s = s * j;
			j = j + 1;
		}
		if(x>100) y = x + a;
		if (x<=100) y = x + 100;
	
		j = i - 1;
		a = 1;
		i = j + 2;
	}

	return 0;
}