#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

int main() {
    DIR *dp;
    struct dirent *d;

    dp = opendir(".");

    while ((d = readdir(dp)) != NULL) {
        if ((strcmp(d->d_name, ".")) && (strcmp(d->d_name, ".."))) {
            printf("%10s\n", d->d_name);
        }
    }
}