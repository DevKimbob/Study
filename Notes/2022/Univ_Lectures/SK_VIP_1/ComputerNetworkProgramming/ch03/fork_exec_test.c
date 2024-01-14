#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void child_start();

int main(int argc, char **argv) {
    pid_t pid;
    int child_status, child_return;

    puts("\tparent process start..........");
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)
        child_start();
    else if (pid > 0)
        printf("\n\t** parent : [PID = %d] Chlid PID = %d\n", getpid(), pid);
    
    return 0;
}

void child_start() {
    puts("\tchild process start...");
    printf("\t** child : [PID = %d] PPID = %d\n", getpid(), getppid());
    printf("\n\t** exec() calld : ls\n");
    execlp("ls", "ls", NULL);

    perror("exec at child");
    exit(1);
}