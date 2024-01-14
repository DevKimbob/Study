#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int from, to;
    int sum = 0;

    if (argc != 3) {
        printf("Error : number of arguments\n");
        exit(1);
    }

    from = atoi(argv[1]);
    to = atoi(argv[2]);

    for (; from <= to; from++)
        sum += from;

    printf("Sum = %d\n", sum);
}