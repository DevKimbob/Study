#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

int main() {
    char *cwd;
    DIR *dp;
    int n = 0;

    cwd = getcwd(NULL, BUFSIZ);

    if (chdir("bit") == -1) {
        perror("bit");
        exit(1);
    }

    dp = opendir(".");
    while (readdir(dp) != NULL) {
        if (++n > 2)
            break;
    }

    if (n <= 2) {
        chdir(cwd);
        if (rmdir("bit") == -1) {
            perror("bit");
            exit(1);
        }
    }
    else {
        printf("Error : not empty\n");
        exit(1);
    }

    closedir(dp);
}