#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main (int argc, char *argv[]) {
    int n;
    extern char *optarg;
    char *file_loc;
    struct stat statbuf;

    if (n = getopt(argc, argv, "f:")) {
        switch (n) {
            case 'f':
                file_loc = optarg;
                break;
        }
    } 

    stat(file_loc, &statbuf);

    printf("File name : %s\n", file_loc);
    printf("Inode : %o\n", statbuf.st_ino);
    printf("File type : ");
    switch (statbuf.st_mode & S_IFMT) {
        case S_IFDIR:
            printf("dir\n");
            break;
        case S_IFREG:
            printf("reg file\n");
            break;
        case S_IFLNK:
            printf("sym link\n");
            break;    
    }
    printf("Auth : %o\n", (unsigned int)statbuf.st_mode);
    printf("UID : %d\n", statbuf.st_uid);
}