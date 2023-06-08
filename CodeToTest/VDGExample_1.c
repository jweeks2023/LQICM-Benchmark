//VDG Example from Paper

#include <stdio.h>

int main(){ 
	int j, s;
	int i = 0;
	int x = 42;
	int y = 5;
	int a = 12;

	while(i < 1000000){
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