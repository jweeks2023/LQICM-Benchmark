//From Thomas Ruby LQICM Pass Test Cases

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
    int i, fact;
    srand(time(NULL));
    int n=rand()%100000;
    int x=rand()%1000;
    int j=0; 
    int y=5;
    int a=5;
	
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