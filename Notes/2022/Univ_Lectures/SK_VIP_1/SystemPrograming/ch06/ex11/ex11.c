#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <sys/times.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    int i;
    int fd;
    struct tms buf;
    clock_t ct, t1, t2;

    ct = sysconf(_SC_CLK_TCK);
    t1 = times(&buf);

    for (i = 0; i < 100000; i++) {
        fd = open("test.txt", O_RDONLY);
        close(fd);
    }

    t2 = times(&buf);

    printf("%.2lf\n", (double)(t2 - t1) / ct);
}