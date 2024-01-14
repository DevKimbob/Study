#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

void sig_child(int signo);

static pid_t pid;
extern int errno;

int main() {
    // pid_t pid;
    pid_t pid_wait;
    struct sigaction act;
    int i = 0;

    bzero((char *)&act, sizeof(act));
    act.sa_handler = sig_child;
    act.sa_flags = SA_RESTART;
    act.sa_flags |= SA_NOCLDWAIT;

    if ((pid = fork()) > 0) {
        sigaction(SIGCHLD, &act, (struct sigaction *)NULL);
        printf("Parent\n");
        // pid_wait = waitpid(-1, NULL, WNOHANG);
        printf("After waitpid\n"); 
        printf("pid_wait : %d\n", pid_wait);
        sleep(2);
        printf("pid_wait : %d\n", pid_wait);
        while (1) {
            sleep(1);
            printf("Inside sleep loop : %d\n", i++);
        }
    }
    else {
        printf("Child\n");
        sleep(5);
        printf("After sleep\n");
    }

    return 0;
}

void sig_child(int signo) {
    pid_t pidw;
    int errnow;
    printf("eno : %d\n", errno);
    while ((pidw = waitpid(-1, &errnow, WNOHANG)) == 0) {}

    printf("%d\n", errnow);
    printf("%d\n", WEXITSTATUS(errno));
    printf("%d exited\n", pidw);
    printf("eno : %d\n", errno);
}