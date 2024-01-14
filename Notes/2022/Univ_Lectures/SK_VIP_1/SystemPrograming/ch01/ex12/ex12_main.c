#include <stdio.h>

extern int subnum(int a, int b);

int main() {
    int sub;

    sub = subnum(1, 5);
    printf("Subtraction : 1-5 = %d\n", sub);
}