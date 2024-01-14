#include <stdio.h>
#include <sys/sysinfo.h>

int main() {
    struct sysinfo info;

    sysinfo(&info);

    printf("Total Ram : %ld\n", info.totalram);
    printf("Free Ram : %ld\n", info.freeram);
    printf("Num of Processes : %d\n", info.procs);
}