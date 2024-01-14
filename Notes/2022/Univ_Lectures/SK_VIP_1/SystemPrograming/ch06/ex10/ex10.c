#include <stdio.h>
#include <sys/types.h>
#include <sys/times.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main() {
    clock_t ct, t1, t2;
    struct tms buf;

    ct = sysconf(_SC_CLK_TCK);

    t1 = times(&buf);
    sleep(5);
    t2 = times(&buf);

    printf("%.2lf\n", (double)(t2 - t1) / ct);
}