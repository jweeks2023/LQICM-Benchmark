//From Thomas Ruby LQICM Pass Test Cases

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>

int main(){
    volatile int i, fact;
    srand(time(NULL));
    //int n=rand()%100000;
	volatile int n = 500000000;
    volatile int x=rand()%1000;
    volatile int j=0; 
    volatile int y=5;
    volatile int a=5;
	
	fact=1;
    i=1;
    while (i<=y) { 
        fact=fact*i; 
        i=i+1;
    }
	if(x>100){
		y=x+a;
    }
	if(x<=100){
		y=x+100;
    }
	a=0;
	
    while(j<n){
        //printf("blabla %d %d", i, fact);
        //printf("blabla %d", y);
        //printf("blabla %d", y);
        i=j;
        j=i+1;
    }
    return i;
}