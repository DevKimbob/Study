#include <stdio.h>
#include <sys/utsname.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int option = 0;
    int n;

    while ((n = getopt(argc, argv, "akrnhs")) != -1) {
        switch (n) {
            case 'a':
                option |= 31;
                break;
            case 'k':
                option |= 1;
                break;
            case 'r':
                option |= 2;
                break;
            case 'n':
                option |= 4;
                break;
            case 'h':
                option |= 8;
                break;
            case 's':
                option |= 16;
                break;
            default:
                perror("arg");
                exit(1);
        }
    }

    if (option % 2) {
        printf("");
    }
}