#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    extern char *optarg;
    int n;
    char *file;
    struct stat statbuf;

    if (n = getopt(argc, argv, "f:")) {
        switch (n) {
            case 'f':
                file = optarg;
                break;
        }
    } 

    stat(file, &statbuf);

    printf("File size : %d\n", (int)statbuf.st_size);
}