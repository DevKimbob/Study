#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <shadow.h>

int main(int argc, char *argv[]) {
    struct spwd *sp;
    time_t tp;

    sp = getspnam(argv[1]);
    printf("%ld days\n", sp->sp_lstchg);
}