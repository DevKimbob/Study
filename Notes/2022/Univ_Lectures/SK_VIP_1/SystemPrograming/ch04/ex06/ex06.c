#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    char *file;
    int fd, n;
    char buf[BUFSIZ];

    file = argv[1];

    fd = open(file, O_RDONLY);

    while ((n = read(fd, buf, BUFSIZ)) > 0) {
        if (write(1, buf, n) != n)
            perror("write");
    }

    close(fd);
}