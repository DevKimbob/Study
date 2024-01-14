#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[]) {
    extern char *optarg;
    DIR *dp;
    struct dirent *d;
    char *file;
    char *tardir;
    int n;

    while ((n = getopt(argc, argv, "d:f:")) != -1) {
        switch (n) {
            case 'd':
                tardir = optarg;
                break;
            case 'f':
                file = optarg;
                break;
        }
    }

    dp = opendir(tardir);

    while (d = readdir(dp)) {
        if (strcmp(file, d->d_name) == 0) {
            printf("File exits\n");
            closedir(dp);
            exit(0);
        }
    }

    printf("No such file\n");
    closedir(dp);
    exit(1);
}