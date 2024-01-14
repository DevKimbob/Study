#include <stdio.h>
#include <stdlib.h>

int main() {
    char *val;

    val = getenv("SHELL");
    if (val == NULL)
        printf("SHELL not defined\n");
    else
        printf("SHELL = %s\n", val);
}