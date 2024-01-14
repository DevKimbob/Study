#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
    int n;
    int op = 0;
    time_t timep;
    struct tm *tm;

    time(&timep);
    tm = gmtime(&timep);

    while ((n = getopt(argc, argv, "aymdwh")) != -1) {
        switch (n) {
            case 'a':
                op = 31;
                break;
            case 'y':
                op |= 1;
                break;
            case 'm':
                op |= 2;
                break;
            case 'd':
                op |= 4;
                break;
            case 'w':
                op |= 8;
                break;
            case 'h':
                op |= 16;
                break;
        }
    }

    if (op % 2)
        printf("%dy ", tm->tm_year + 1900);
    op /= 2;
    if (op % 2)
        printf("%dm ", tm->tm_mon);
    op /= 2;
    if (op % 2)
        printf("%dd ", tm->tm_mday);
    op /= 2;
    if (op % 2)
        printf("%d ", tm->tm_wday);
    op /= 2;
    if (op % 2)
        printf("%dh %dm %ds\n", tm->tm_hour, tm->tm_min, tm->tm_sec);
}