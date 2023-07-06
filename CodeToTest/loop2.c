//From Thomas Ruby LQICM Pass Test Cases

#include <stdio.h>
#include <limits.h>

void use(int y){
    printf("y=%d\n",y);
}

int main(){
    volatile int i=INT_MIN,y=0;
    //srand(time(NULL));
    //int x=rand()%100;
    //int x2=rand()%100;
	volatile int x=10,x2=20;
    volatile int z;
    while(i<INT_MAX){
        z=y*y;
        //use(z);
        y=x+x;
        //use(y);
        x=x2;
        //use(x);
		i++;
    }
    return z;
}