#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    int n;
    char *file;
    extern char *optarg;
    struct stat statbuf;
    int file_type;
    
    if (n = getopt(argc, argv, "f:")) {
        switch (n) {
            case 'f':
                file = optarg;
                break;
        }
    }

    stat(file, &statbuf);
    
    file_type = statbuf.st_mode & S_IFMT;
    switch (file_type) {
        case S_IFREG:
            printf("File is Regular file\n");
            break;
        case S_IFDIR:
            printf("File is Directory\n");
            break;
        case S_IFLNK:
            printf("File is Symbalic Link\n");
            break;
    }
}