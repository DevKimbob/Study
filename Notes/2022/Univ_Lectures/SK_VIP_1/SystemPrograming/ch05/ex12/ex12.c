#include <stdio.h>
#include <grp.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[1]) {
    int n;
    char *name;
    struct group *gp;
    struct group *tmp;

    if (argc != 2) {
        printf("arg\n");
        exit(1);
    }

    gp = getgrnam(argv[1]);
    printf("primary group : %s\n", gp->gr_name);

    printf("secondary group : ");
    while ((tmp = getgrent()) != NULL) {
        n = 0;
        while (tmp->gr_mem[n] != NULL) {
            //printf("%s : %s\n", tmp->gr_name, tmp->gr_mem[n]);
            
            if (strcmp(tmp->gr_mem[n], argv[1]) == 0) {
                printf("%s ", tmp->gr_name);
                break;
            }
            n++;
        }
    }
    printf("\n");
}