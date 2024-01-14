#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int main() {
    DIR *dp;
    struct dirent *d;

    dp = opendir(".");

    while ((d = readdir(dp)) != NULL) {
        if ((strcmp(d->d_name, ".") != 0) && (strcmp(d->d_name, "..") != 0))
            printf("%10s\n", d->d_name);
    } 

    closedir(dp);
}