#include <stdio.h>
#include <sys/times.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    struct tms buf;
    clock_t ct, t1, t2;
    int n = 0;
    int i;
    int fd;

    ct = sysconf(_SC_CLK_TCK);
    t1 = times(&buf);
    printf("%.1lf %.1lf\n", (double)buf.tms_utime / ct, (double)buf.tms_stime / ct);

    for (i = 0; i < 100000; i++)
        n += (i + 1);

    for (i = 0; i < 3; i++) 
        sleep(1);

    for (i = 0; i < 1000000; i++) {
        fd = open("test.txt", O_RDONLY);
        close(fd);
    }

    t2 = times(&buf);    
    printf("%.1lf %.1lf\n", (double)buf.tms_utime / ct, (double)buf.tms_stime / ct);
    printf("%.1lf\n", (double)(t2 - t1) / ct);
    printf("%ld %ld\n", buf.tms_utime, buf.tms_stime);
}