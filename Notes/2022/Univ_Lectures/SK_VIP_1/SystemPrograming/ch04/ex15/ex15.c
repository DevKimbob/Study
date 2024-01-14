#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {
    int fd;
    int i;
    int n = 0;
    int buf[1] = {0};
    int info[4] = {0};

    fd = open("test.txt", O_RDONLY);
    //printf("fd : %d\n", fd);

    while (read(fd, buf, 1) > 0) {
        //printf("%d\n", buf[0]);

        if (buf[0] == 10) {
            printf("%d : %lf\n", info[0], (info[1] + info[2] + info[3]) / 3 * 1.0);
            for (i = 0; i < 4; i++)
                info[i] = 0;
            n = 0;
        }
        else if (buf[0] != 32) {
            info[n] = info[n] * 10 + (buf[0] - (int)'0');
            //printf("info[%d] : %d\n", n, info[n]);
        }
        else if ((buf[0] == 32) && (n < 4)) {
            n++;
        }
    }

    close(fd);
}