#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;

    switch (pid = fork()) {
        case -1:
            exit(1);
            break;
        case 0:
            system("pwd");
            exit(0);
            break;
        default:
            system("ls");
            exit(0);
            break; 
    }
}