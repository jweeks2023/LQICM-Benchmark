//From Thomas Ruby LQICM Pass Test Cases

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
    int i, fact;
    srand(time(NULL));
    //int n=rand()%10000;
	int n = 100000000;
    int a=rand()%100;
    int j=0; 
    int y=rand()%100;
	
	
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