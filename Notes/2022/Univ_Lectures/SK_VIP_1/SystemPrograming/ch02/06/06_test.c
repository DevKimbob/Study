#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    char *cwd;

    cwd = getcwd(NULL, BUFSIZ);
    printf("Cwd : %s\n", cwd);
    printf("Ptr : %x\n", *cwd);

    chdir("bit");

    cwd = getcwd(NULL, BUFSIZ);
    printf("Cwd : %s\n", cwd);
    printf("Ptr : %x\n", *cwd);

    free(cwd);
}