// strerror() 함수로 오류 메시지 출력하기

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern int errno;

int main() {
    char *err;

    if (access("test.txt", R_OK) == -1) {
        err = strerror(errno);
        printf("Error : %s(test.txt)\n", err);
        exit(1);
    }
}