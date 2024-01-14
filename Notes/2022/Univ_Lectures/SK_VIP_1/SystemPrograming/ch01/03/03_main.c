// meke 명령 사용하기(1)

#include <stdio.h>

extern int addnum(int a, int b);

int main() {
    int sum;

    sum = addnum(1, 5);
    printf("Sum 1-5 = %d\n", sum);
}