#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int n;
    char *option;
    char *file_loc;
    char *user;
    char *auth;
    char target;
    char target_str[2];
    struct stat statbuf;
    mode_t mode;
    mode_t mask = 0111000;

    option = argv[1];
    file_loc = argv[2];

    if (strchr(option, '+') != NULL) 
        target = '+';
    else if (strchr(option, '-') != NULL)
        target = '-';
    else if (strchr(option, '=') != NULL)
        target = '=';
    else {
        printf("error : option\n");
        exit(1);
    }
    // printf("%c\n", target);
    target_str[0] = target;
    // printf("%s\n", target_str);

    user = strtok(option, target_str);
    auth = strtok(NULL, target_str);
    // printf("%s  %s  %s  %s\n", option, file_loc, user, auth);

    if (strcmp(auth, "r") == 0)
        mode = 4; 
    else if (strcmp(auth, "w") == 0)
        mode = 2;
    else if (strcmp(auth, "x") == 0)
        mode = 1;
    else {
        printf("error : auth\n");
        exit(1);
    }
    // printf("%d\n", mode);

    if (strcmp(user, "a") == 0)
        mode *= 64 + 8 + 1;
    else if (strcmp(user, "u") == 0)
        mode *= 64;
    else if (strcmp(user, "g") == 0)
        mode *= 8;
    else if (strcmp(user, "o") == 0)
        mode *= 1;
    else {
        printf("error : user\n");
        exit(1);
    }
    // printf("%o\n", mode);

    stat(file_loc, &statbuf);
    printf("Original auth : %o\n", statbuf.st_mode);

    if (strcmp(target_str, "+") == 0)
        mode = statbuf.st_mode | mode;
    else if (strcmp(target_str, "-") == 0)
        mode = statbuf.st_mode & ~mode;
    else if (strcmp(target_str, "=") == 0)
        mode = (statbuf.st_mode & mask) | mode;
    else {
        printf("error : mode\n");
        exit(1);
    }
    // printf("%o\n", mode);

    chmod(file_loc, mode);
}