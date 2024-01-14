#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int global_var = 0;

int main() {
    pid_t pid;
    int local_var = 0;

    if ((pid = fork()) < 0) {
        printf("error : fork\n");
        exit(1);
    } else if (pid == 0) {
        global_var++;
        local_var++;
        printf("Child PID : %d, PPID : %d\n", getpid(), getppid());
    } else {
        sleep(2);
        global_var += 5;
        local_var += 5;
        printf("Parent PID : %d, Child PID : %d\n", getpid(), pid);
    }

    printf("\tglobal var : %d\n", global_var);
    printf("\tlocal var : %d\n", local_var);
}