#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int inode[BUFSIZ];
    DIR *dp;
    struct dirent *d;
    struct stat s;

    dp = opendir(".");
    while ((d = readdir(dp)) != NULL) {
        lstat(d->d_name, &s);
        if ((s.st_nlink >= 2) && ((int)d->d_type == 8)) {
            printf("%s : %d\n", d->d_name, (int)s.st_ino);
            printf("%s\n", d->d_type);
        }
    }
}