// 디렉터리명 변경하기

#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    if (rename("han", "bit") == -1) {
        perror("rename");
        exit(1);
    }
}