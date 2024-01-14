#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    char *fname;
    // char fntmp[BUFSIZ];
    char template[32];
    int fd;

    // fname = tmpnam(NULL);
    // printf("1. TMP File Name(tmpnam) : %s\n", fname);

    // tmpnam(fntmp);
    // printf("2. TMP File Name(tmpnam) : %s\n", fntmp);

    strcpy(template, "/tmp/hanbitXXXXXX");
    fname = mktemp(template);
    printf("3. TMP File Name(mktemp) : %s\n", fname);

    fd = open(fname, O_RDONLY);
    write(fd, "test", 10);
    close(fd);

    // 도대체 뭐가 달라서 문제가 생겼던거지?
    // 나중에 리캡할 때 다시 체크.
}