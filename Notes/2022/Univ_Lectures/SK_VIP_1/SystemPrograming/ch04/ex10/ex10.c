#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int fd, n;
    char *buf[2];
    char *file;

    file = argv[1];

    fd = open(file, O_RDONLY);

    while ((n = read(fd, buf, 2)) > 0) {
        if (write(1, buf, 1) != 1)
            perror("write");
    }

    close(fd);
}