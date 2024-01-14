#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    int n;
    char *file_loc;
    extern char *optarg;
    struct stat statbuf;
    int mode;
    int div = 256;
    int i, j;

    if (n = getopt(argc, argv, "f:")) {
        switch (n) {
            case 'f':
                file_loc = optarg;
                break;
        }
    }
    
    stat(file_loc, &statbuf);

    printf("%s\n", file_loc);
    printf("%d\n", statbuf.st_uid);

    mode = statbuf.st_mode;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if ((mode/div) % 2) {
                switch (j) {
                    case 0:
                        printf("r");
                        break;
                    case 1:
                        printf("w");
                        break;
                    case 2:
                        printf("x");
                        break;
                }
            }
            else
                printf("-");
            div /= 2;
        }
    }

    printf("\n");
}