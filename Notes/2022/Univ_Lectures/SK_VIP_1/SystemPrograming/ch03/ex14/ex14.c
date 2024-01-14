#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    char *file, *src, *dst;

    src = argv[0];
    file = argv[1];
    dst = argv[2];

    dst = strcat(dst, "/");
    dst = strcat(dst, file);
    rename(file, dst);
}