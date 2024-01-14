// unlink() 함수로 링크 끊기

#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    struct stat statbuf;

    stat("linux.txt", &statbuf);
    printf("1.linux.ln : Link Count : %d\n", (int)statbuf.st_nlink);

    unlink("linux.ln");

    stat("linux.txt", &statbuf);
    printf("2.linux.ln : Link Count : %d\n", (int)statbuf.st_nlink);

    unlink("linux.sym");
}