#include <stdio.h>
#include <sys/sysinfo.h>

int main() {
    struct sysinfo info;

    sysinfo(&info);

    printf("mem : %ld\n", info.totalram);
    printf("swap : %ld\n", info.totalswap);
}