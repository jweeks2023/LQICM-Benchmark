//Made by Justice Howley

#include <stdio.h>
#include <limits.h>
int main() {
    // Initialize random variables
    volatile int a = 3;
    volatile int b = 15;
    volatile int c = 30;
    volatile int d = 40;
    volatile int e = 0;
    volatile int f = 8;
    volatile int i = INT_MIN;

    while (i < INT_MAX){
        a = a + c;
        e = 2;
        if (a < 100) c += 10;
        if (a > 100) c -= 2;

        while (f < b){
            if (f == 5) printf("");
            for (int j = 0; j < a; j++){
                e = 5;
            }
            f++;
        }
        i = i + 1;
    }

    return 0;
}