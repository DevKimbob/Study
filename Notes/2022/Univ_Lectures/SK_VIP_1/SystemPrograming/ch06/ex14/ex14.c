#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char env[BUFSIZ] = "SHELL=";
    strcat(env, argv[1]);
    printf("%s\n", env);
    putenv(env);
}