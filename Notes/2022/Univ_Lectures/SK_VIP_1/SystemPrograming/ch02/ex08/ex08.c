#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *svd_dir;
    char *cwd;

    svd_dir = getcwd(NULL, 0);
    printf("%s\n", svd_dir);

    if (chdir("han") == -1) {
        perror("han");
        exit(1);
    }
    cwd = getcwd(NULL, 0);
    printf("%s\n", cwd);
    
    chdir(svd_dir);
    cwd = getcwd(NULL, 0);
    printf("%s\n", cwd);

    free(cwd);
    free(svd_dir);
}