// 시스템 호출의 오류 처리하기

#include <errno.h>
#include <stdio.h>
#include <unistd.h>

extern int errno;

int main() {
    if (access("test.txt", F_OK) == -1) {
        printf("errno = %d\n", errno);
    }
}