#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid;

    switch (pid = vfork()) {
        case -1:
            exit(1);
            break;
        case 0:
            system("last");
            exit(0);
        default:
            system("date");
            exit(0);
    }
}