#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    long lenth;

    if (argc != 2) {
        perror("arg");
        exit(1);
    } 

    //printf("%d\n", (int)strlen(argv[1]));
    if (strlen(argv[1]) > sysconf(_SC_LOGIN_NAME_MAX))
        printf("bigger\n");
    else
        printf("not bigger\n");
}