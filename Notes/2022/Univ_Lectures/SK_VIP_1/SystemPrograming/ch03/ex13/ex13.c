#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int mode;
    char *file_name;

    sscanf(argv[1], "0%o", &mode);
    file_name = argv[2];

    printf("%o\n", mode);

    chmod(file_name, mode);
}