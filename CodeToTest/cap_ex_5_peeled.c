//Made by Justice Howley

int main() {
    // Initialize random variables
    int a = 0;
    int b = 15;
    int c = 30;
    int d = 40;
    int e = 0;
    int f = 8;

	
    e = 2;
	e = 5;
	e = 32;

    for (int i = 0; i <= 100000000; i++){
        a = a + c;
        if (a < 100) c += 10;
        if (a > 100) c -= 2;
    }

    return 0;
}