// 함수를 이용해 접근 권한 검색하기

#include <sys/errno.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int perm;

    if (access("linux.bak", F_OK) == -1 && errno == ENOENT)
        printf("linux.bak: File not exist\n");

    perm = access("linux.txt", R_OK);

    if (perm == 0)
        printf("linux.txt: Read permmission is permmited.\n");
    else if (perm == -1 && errno == EACCES)
        printf("linux.txt: Read permmission is not permmited.\n");
}