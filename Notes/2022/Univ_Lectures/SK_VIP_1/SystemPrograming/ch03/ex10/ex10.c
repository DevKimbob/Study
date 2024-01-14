#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    DIR *dp;
    struct stat statbuf;
    struct dirent *d;

    dp = opendir(".");

    while ((d = readdir(dp)) != NULL) {
        printf("%10s ", d->d_name);
        switch (d->d_type) {
            case DT_DIR:
                printf("Dir ");
                break;
            case DT_REG:
                printf("Reg ");
                break;
            case DT_LNK:
                printf("Sym ");
                break;
            default:
                printf("Something else ");
                break;
        }
        printf("%ld\n", d->d_ino);
    }
}