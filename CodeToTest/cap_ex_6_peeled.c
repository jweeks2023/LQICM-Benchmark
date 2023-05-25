//Made by Justice Howley

#include <stdio.h>

int main() {
    // Initialize random variables
    int a = 3;
    int b = 15;
    int c = 30;
    int d = 40;
    int e = 0;
    int f = 8;
    int i = 0;
    
    while (f < b){
        if (f == 5) printf("");
        for (int j = 0; j < a; j++){
            e = 5;
        }
        f++;
    }

    e = 2;

    while (i < 10000000){
        a = a + c;
        if (a < 100) c += 10;
        if (a > 100) c -= 2;

        i = i + 1;
    }

    return 0;
}