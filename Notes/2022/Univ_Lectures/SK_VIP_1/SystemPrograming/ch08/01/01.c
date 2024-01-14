#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int main() {
    printf("Before SIGCONT signal to parent\n");
    kill(getppid(), SIGCONT);

    printf("Before SIGQUIT Signal to me\n");
    kill(getpid(), SIGQUIT);
    
    printf("After SIGQUIT Signal\n");
}