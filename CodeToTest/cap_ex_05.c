//Made by Justice Howley

int main() {
    // Initialize random variables
    int a = 0;
    int b = 15;
    int c = 30;
    int d = 40;
    int e = 0;
    int f = 8;

    for (int i = 0; i <= 10000000; i++){
        a = a + c;
        e = 2;
        while (f < b){
            e = 5;
            f++;
        }
        if (a < 100) c += 10;
        if (a > 100) c -= 2;

        for (; c < 2*d; c++){
            e = 32;
        }
    }

    return 0;
}