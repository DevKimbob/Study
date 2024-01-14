#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;
    char *argv[3];

    argv[0] = "vi";
    argv[1] = "/etc/hosts";
    argv[2] = NULL;

    switch (pid = fork()) {
        case -1:
            exit(1);
            break;
        case 0:
            execvp("/usr/bin/vi", argv);
            break;
        default:
            while (waitpid(pid, &status, WNOHANG) == 0) {
                printf("wait\n");
                sleep(1);
            }
    }
}