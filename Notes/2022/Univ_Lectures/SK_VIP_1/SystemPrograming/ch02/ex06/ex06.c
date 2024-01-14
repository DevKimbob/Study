#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    if (rmdir("dir1") == -1) {
        perror("dir1");
        exit(1);
    }

    if (rename("dir2", "hanbit") == -1) {
        perror("dir2");
        exit(1);
    }
}