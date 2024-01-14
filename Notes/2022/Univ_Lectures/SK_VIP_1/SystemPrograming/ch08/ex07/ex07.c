#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

void sig_handler(int signo) {
    printf("Sig handled\n");
    psignal(signo, "Signal");
}

int main() {
    void (*hand)(int);

    hand = signal(SIGILL, sig_handler);

    printf("before\n");
    kill(getpid(), SIGILL);
    printf("after\n");
}