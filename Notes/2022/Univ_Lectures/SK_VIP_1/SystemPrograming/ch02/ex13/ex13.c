#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

int main() {
    int n = 1;
    DIR *dp;
    struct dirent *d;
    long loc;

    dp = opendir(".");

    while (d = readdir(dp)) {
        printf("%10s\n", d->d_name);
        if (++n == 3) {
            loc = telldir(dp);
        }
    }

    seekdir(dp, loc);
    d = readdir(dp);
    printf("** 3rd file/directory **\n");
    printf("%10s\n", d->d_name);

    closedir(dp);
}