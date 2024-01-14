#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    pid_t pid;

    switch (pid = fork()) {
        case -1:  // fork fail
            perror("fork");
            exit(1);
            break;
        case 0:  // child
            printf("Child Process PID : %d, PPID : %d\n", (int)getpid(), (int)getppid());
            break;
        default:  // parent
            printf("Parent Process PID : %d, PPID : %d, Child PID : %d\n", (int)getpid(), (int)getppid(), (int)pid);
            break;
    }

    printf("End of fork\n");
}