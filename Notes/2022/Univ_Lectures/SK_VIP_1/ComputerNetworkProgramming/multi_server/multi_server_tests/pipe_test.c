#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    int fd[2];
    pid_t pid;
    char buf[100], buf2[100], buf3[100];
    int len;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    switch (pid = fork()) {
        case -1:
            perror("fork");
            exit(1);
            break;
        case 0:
            close(fd[1]);
            // for (int i = 0; i < 3; i++) {
            //     printf("c sleep %d\n", i);
            //     sleep(1);
            // }
            len = read(fd[0], buf, sizeof(buf));
            printf("len %d\n", len);
            // buf[strlen(buf)] = 0;
            len = read(fd[0], buf2, sizeof(buf));
            printf("len %d\n", len);
            // buf[strlen(buf2)] = 0;
            len = read(fd[0], buf3, sizeof(buf));
            printf("len %d\n", len);
            // buf[strlen(buf3)] = 0;
            buf[10] = 0;
            puts(buf);
            puts(buf2);
            puts(buf3);
            // if (fd[0] != 0) {
            //     close(fd[0]);
            // }
            printf("pid %d\n", getppid());
            break;
        default:
            close(fd[0]);
            write(fd[1], "test", sizeof("test"));
            write(fd[1], "test", sizeof("test"));
            write(fd[1], "test", sizeof("test"));
            printf("after p write\n");
            sleep(5);
            // if (fd[1] != 1) {
            //     close(fd[1]);
            // }
            break;
    }
}