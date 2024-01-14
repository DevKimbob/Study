#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main() {
    pid_t pid;
    int status;

    switch (pid = fork()) {
        case -1:
            exit(1);
            break;
        case 0:
            printf("child : ");
            execl("/usr/bin/who", "who", "-a", (char *)NULL);
            break;
        default:
            printf("parent : ");
            while (wait(&status) != pid)
                continue;
    }

}