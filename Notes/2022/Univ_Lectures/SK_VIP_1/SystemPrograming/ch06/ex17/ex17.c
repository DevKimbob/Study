#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *env, *val;

    setenv(argv[1], argv[2], 0);

    val = getenv(argv[1]);
    printf("%s = %s\n", argv[1], val);
}