#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main() {
    printf("before\n");
    kill(getpid(), SIGUSR1);
    printf("after\n");
}