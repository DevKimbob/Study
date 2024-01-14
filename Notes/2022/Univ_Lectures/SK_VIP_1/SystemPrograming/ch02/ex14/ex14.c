#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[]) {
    extern char *optarg;
    DIR *dp;
    struct dirent *d;
    int n;
    char *file;

    if ((n = getopt(argc, argv, "f:")) != -1) {
        file = optarg;
    }
    dp = opendir(".");

    while (d = readdir(dp)) {
        if (strcmp(file, d->d_name) == 0) {
            printf("File(%s) is in the directory\n", file);
            exit(0);
        }
    }

    printf("No file matched\n");

    closedir(dp);
}