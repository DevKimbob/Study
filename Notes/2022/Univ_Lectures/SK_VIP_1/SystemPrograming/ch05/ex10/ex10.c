#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    struct passwd *pw;
    uid_t uid;

    if (argc != 2) {
        perror("arg");
        exit(1);
    }

    uid = atoi(argv[1]);

    pw = getpwuid(uid);
    printf("%s\n", pw->pw_dir);
}