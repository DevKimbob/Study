#include <stdio.h>
#include <sys/sysinfo.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    pid_t ppid, pgid, sid;

    pid = atoi(argv[1]);

    if (pid == 0) {
        printf("PPID : %d\n", getppid());
        printf("PGID : %d\n", getpgid(getpid()));
        printf("SID : %d\n", getsid(getpid()));
    }
    else {
        printf("PGID : %d\n", getpgid(pid));
        printf("SID : %d\n", getsid(pid));
    }
}