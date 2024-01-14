#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern int errno;

int main() {
    char *err;

    if (access("test.txt", F_OK) == -1) {
        // printf("errno = %d\n", errno);

        // ref : 04.c using perror
        perror("text.txt");
        printf("\n");

        // ref : 05.c using strerror
        err = strerror(errno);
        printf("Error : %s(test.txt)\n", err);

        exit(1);
    }
}