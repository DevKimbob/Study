// zombie process, process sync
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid, pid2;
    int status;

    //printf("test\n");
    switch (pid = fork()) {
        case -1:
            exit(1);
            break;
        case 0:
            printf("1c PID : %d\n", getpid());
            printf("1c PPID : %d\n", getppid());
            switch (pid2 = fork()) {
                case -1:
                    exit(1);
                    break;
                case 0:
                    printf("  2c PID : %d\n", getpid());
                    printf("  2c PPID : %d\n", getppid());
                    break;
                default:
                    printf("  2p PID : %d\n", getpid());
                    printf("  2p PPID : %d\n", getppid());
                    while (wait(&status) != pid2) {
                        continue;
                    }
                    break;
            }
            break;
        default:
            printf("1p PID : %d\n", getpid());
            printf("1p CPID : %d\n", pid);
            while (wait(&status) != pid) {
                continue;
            }
            break;
    }
}