// 디렉터리 생성하기

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    if (mkdir("han", 0755) == -1) {
        perror("han");
        exit(1);
    }
}