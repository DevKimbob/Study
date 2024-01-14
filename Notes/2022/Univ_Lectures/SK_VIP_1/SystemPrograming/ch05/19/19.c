#include <stdio.h>
#include <time.h>

int main() {
    time_t timep;

    time(&timep);

    printf("Time(sec) : %d\n", (int)timep);
    printf("Time(date) : %s", ctime(&timep));
}