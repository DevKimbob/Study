#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define TIMES 100000000

// int main() {
//     clock_t start, end;

//     printf("hello\n");
//     printf("%ld\n", CLOCKS_PER_SEC);
//     for (int i = 0; i < 3; i++) {
//         start = clock();
//         sleep(2);
//         end = clock();
//         printf("%ld\n", end - start);
//     }
// }

int add(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

int two(int a, int b) {
    add(a, b);
    sub(a, b);
    return 0;
}

int main() {
    int choice = 18;
    clock_t start, end;
    int k, i;

    int (*fp[20])(int, int);
    fp[19] = two;
    fp[0] = add;
    fp[1] = sub;

    for (k = 118; k < 121; k++) {
        start = clock();
        for (i = 0; i < TIMES; i++) {
            switch (k) {
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 23:
                case 24:
                case 25:
                case 26:
                case 27:
                case 28:
                case 29:
                case 30:
                case 31:
                case 33:
                case 34:
                case 35:
                case 36:
                case 37:
                case 38:
                case 39:
                case 40:
                case 41:
                case 43:
                case 44:
                case 45:
                case 46:
                case 47:
                case 48:
                case 49:
                case 50:
                case 51:
                case 53:
                case 54:
                case 55:
                case 56:
                case 57:
                case 58:
                case 59:
                case 118:
                    fp[0](1, 2);
                    fp[1](1, 2);
                    break;
                case 119:
                    two(1, 2);
                    break;
                case 120:
                    add(1, 2);
                    sub(1, 2);
                    break;
            }
        }
        end = clock();
        printf("switch case : %ld\n", end - start);
    }

    start = clock();
    for (i = 0; i < TIMES; i++) {
        fp[19](1, 2);
    }
    end = clock();
    printf("function pointer : %ld\n", end - start);

    start = clock();
    for (i = 0; i < TIMES; i++) {
        fp[0](1, 2);
        fp[1](1, 2);
    }
    end = clock();
    printf("function pointer : %ld\n", end - start);
}