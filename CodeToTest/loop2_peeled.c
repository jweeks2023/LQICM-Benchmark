//From Thomas Ruby LQICM Pass Test Cases

#include <stdio.h>

void use(int y){
    printf("y=%d\n",y);
}

int main(){
    int i=0,y=0;
    //srand(time(NULL));
    //int x=rand()%100;
    //int x2=rand()%100;
    int x=10,x2=20;
    int z;
    
    
    x=x2;
    use(x);
    y=x+x;
    use(y);
    z=y*y;
    use(z);
    
    for(; i<3;i++){
        
    }
    
    while(i<10000){
        i++;
    }
    return 42;
}