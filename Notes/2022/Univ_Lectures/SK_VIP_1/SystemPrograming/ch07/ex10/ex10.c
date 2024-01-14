#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid, pid2;

    //printf("test\n");
    switch (pid = fork()) {
        case -1:
            exit(1);
            break;
        case 0:
            printf("1c PID : %d\n", getpid());
            switch (pid2 = fork()) {
                case -1:
                    exit(1);
                    break;
                case 0:
                    printf("  2c PID : %d\n", getpid());
                    break;
                default:
                    printf("  2p PID : %d\n", getpid());
                    break;
            }
            break;
        default:
            printf("1p PID : %d\n", getpid());
            printf("1p CPID : %d\n", pid);
            break;
    }
}