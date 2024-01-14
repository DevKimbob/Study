#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    long version = sysconf(_SC_VERSION);
    printf("Posix version : %ld\n", version);
    if (version >= 199506L)
        printf("Can use Posix library\n");
    else
        printf("Does not support Posix1003.1c thread\n");
    return 0;
}