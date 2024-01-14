#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;

    printf("Start of main\n");

    if ((pid = fork()) == 0) {
        printf("Inside parent process\n");
        sleep(1);
    }
    else if (pid > 0) {
        printf("Inside child process\n");
        sleep(3);
    }
    else {
        printf("Error : fork");
        exit(1);
    }

    printf("End of main. pid : %d\n", pid);
    return 0;
}