#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int n;
    extern char *optarg;

    while((n = getopt(argc, argv, "hpn:")) != -1){
        switch(n) {
            case 'h':
                printf("-h : help\n");
                printf("-p : \"Welcome Linux System Programming!\"\n");
                printf("-n <name> : \"Nice to meet <name>\"\n");
                break;
            case 'p':
                printf("Welcome Linux System Programming!\n");
                break;
            case 'n':
                printf("Nice to meet %s\n", optarg);
                break;
        }
    }
}