#include <stdio.h>
#include <sys/types.h>
#include <shadow.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    struct spwd *sh;
    uid_t uid;

    if (argc != 2) {
        perror("arg");
        exit(1);
    } 

    uid = atoi(argv[1]);
    sh = getspent();

    printf("min : %ld\n", sh->sp_min);
    printf("max : %ld\n", sh->sp_max);
    printf("warn : %ld\n", sh->sp_warn);
    printf("inactive : %ld\n", sh->sp_inact);
}