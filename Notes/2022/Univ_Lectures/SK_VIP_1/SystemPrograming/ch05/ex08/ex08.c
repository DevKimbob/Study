#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    unsigned int op = 0;
    int n;

    while ((n = getopt(argc, argv, "ahplx")) != -1) {
        switch (n) {
            case 'a':
                op = 15;
                break;
            case 'h':
                op |= 1;
                break;
            case 'p':
                op |= 2;
                break;
            case 'l':
                op |= 4;
                break;
            case 'x':
                op |= 8;
                break;
        }
    }

    if (op % 2) 
        printf("host : %ld\n", sysconf(_SC_HOST_NAME_MAX));
    op /= 2;
    if (op % 2)
        printf("process : %ld\n", sysconf(_SC_CHILD_MAX));
    op /= 2;
    if (op % 2)
        printf("login : %ld\n", sysconf(_SC_LOGIN_NAME_MAX));
    op /= 2;
    if (op % 2)
        printf("POSIX V : %ld\n", sysconf(_SC_VERSION));
}