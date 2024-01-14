#include <stdio.h>
#include <time.h>

int main() {
    struct tm *tm;
    time_t timep;

    time(&timep);
    tm = localtime(&timep);

    printf("Time(sec) : %d\n", (int)timep);
    printf("Time(date) : %s", asctime(tm));
}