#include <stdio.h>
#include <unistd.h>

int main() {
    printf("PID : %d\n", (int)getpid());
    printf("PGID : %d\n", (int)getpgrp());
    printf("SID : %d\n", (int)getsid(0));
}