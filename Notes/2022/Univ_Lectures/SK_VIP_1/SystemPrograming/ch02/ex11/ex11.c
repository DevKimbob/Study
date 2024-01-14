#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    int n;
    extern char *optarg;
    char *cwd;

    if ((n = getopt(argc, argv, "d:")) != -1) {
        if (mkdir(optarg, 0755) == -1) {
            perror(optarg);
            exit(1);
        }

        if (chdir(optarg) == -1) {
            perror(optarg);
            exit(1);
        }

        cwd = getcwd(NULL, BUFSIZ);
        printf("Cwd : %s\n", cwd);
    }
}