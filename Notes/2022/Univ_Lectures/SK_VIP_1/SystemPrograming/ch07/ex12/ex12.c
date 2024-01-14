#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void printdir() {
    system("ls");
}

int main() {
    int status;
    pid_t pid;

    switch (pid = fork()) {
        case -1:
            exit(1);
            break;
        case 0:
            printf("Child : ");
            atexit(printdir);
            exit(0);
            break;
        default:
            printf("Parent : ");
            while (wait(&status) != pid) {
                continue;
            }
            break;
    }
}