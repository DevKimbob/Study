#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[], char **envp) {
    char **env;
    char *buf;

    env = envp;
    while (*env) {
        if ((buf = strstr(*env, argv[1])) == *env) {
            printf("%s\n", *env);
            return 0;
        }
        env++;
    }

    printf("no env\n");
    return -1;
}