#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int rfd, wfd, n;
    char *file;
    char dir[BUFSIZ];
    char *buf[BUFSIZ];

    strcpy(dir, argv[1]);
    file = argv[2];

    mkdir(dir, 0755);
    strcat(dir, "/");
    strcat(dir, file);

    rfd = open(file, O_RDONLY);
    wfd = open(dir, O_CREAT | O_WRONLY | O_TRUNC, 0644);

    while ((n = read(rfd, buf, BUFSIZ)) > 0) {
        if (write(wfd, buf, n) != n)
            perror("write");
    }

    close(rfd);
    close(wfd);
    remove(file);
}