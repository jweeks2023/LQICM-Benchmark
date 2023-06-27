//VDG Example from Paper

#include <stdio.h>
#include <limits.h>

int main(){ 
	volatile int j, s;
	volatile int i = 0;
	volatile int x = 42;
	volatile int y = 5;
	volatile int a = 12;

    
	j = 0;
	s = 1;
	
	
	s = s * j;
	
	while(j<y){
		j = j + 1;
	}
	if(x>100) y = x + a;
	if (x<=100) y = x + 100;
	
	a = 1;

	while(i < 1000000000){
	
		j = i - 1;
		i = j + 2;
	}

	return 0;
}