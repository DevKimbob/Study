#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int rfd, wfd, n;
    char *buf[BUFSIZ];
    char *src, *dst;

    src = argv[1];
    dst = argv[2];

    rfd = open(src, O_RDONLY);
    wfd = open(dst, O_CREAT | O_WRONLY | O_TRUNC, 0644);

    while ((n = read(rfd, buf, BUFSIZ)) > 0) {
        if (write(wfd, buf, n) != n)
            perror("write");
    }

    close(rfd);
    close(wfd);
}