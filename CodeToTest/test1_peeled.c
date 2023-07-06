//From Thomas Ruby LQICM Pass Test Cases

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>

int main(){
    volatile int i = 0;
    srand(time(NULL));
    //int n=rand()%10000;
	volatile int n = INT_MAX;
    volatile int a=rand()%100;
    volatile int j=INT_MIN; 
    volatile int y=rand()%100;
	
	
    y=a+1;
	//printf("blabla %d ", y);
    if(y==a+1)
		y=y+1;
	//printf("blabla %d ", y);
	
    while(j<n){
        j=j+1;
        y=j;
        //printf("blabla %d ", y);
    }
    return i;
}