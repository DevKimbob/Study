#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *env;

    setenv("TESTENV", "ubuntu", 0);
    env = getenv("TESTENV");
    printf("TESTENV = %s\n", env);

    unsetenv("TESTENV");
    if ((env = getenv("TESTENV")) == NULL) {
        perror("env");
        exit(1);
    }
    printf("TESTENV = %s\n", env);
}