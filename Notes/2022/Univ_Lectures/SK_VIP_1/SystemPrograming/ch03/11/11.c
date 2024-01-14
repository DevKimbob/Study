// readlink() 함수로 심벌릭 링크의 내용 읽기

#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    char buf[BUFSIZ];
    int n;

    n = readlink("linux.sym", buf, BUFSIZ);
    if (n == -1) {
        perror("readlink");
        exit(1);
    }

    buf[n] = '\0';
    printf("linux.sym : READLINK = %s\n", buf);
}