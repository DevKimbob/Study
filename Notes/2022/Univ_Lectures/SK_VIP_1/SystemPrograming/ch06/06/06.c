#include <stdio.h>
#include <unistd.h>

extern char **environ;

int main() {
    char **env;

    env = environ;
    while (*env) {
        printf("%s\n", *env);
        env++;
    }
}