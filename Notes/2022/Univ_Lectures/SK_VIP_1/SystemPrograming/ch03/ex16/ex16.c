#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char *file;
    char dst[BUFSIZ];
    char buf_sym[BUFSIZ];
    char buf_orig[BUFSIZ];

    file = argv[1];
    strcpy(dst, file);
    strcat(dst, ".sym");

    symlink(file, dst);
    readlink(dst, buf_sym, BUFSIZ);
    realpath(dst, buf_orig);

    printf("%s\n", buf_sym);
    printf("%s\n", buf_orig);
}