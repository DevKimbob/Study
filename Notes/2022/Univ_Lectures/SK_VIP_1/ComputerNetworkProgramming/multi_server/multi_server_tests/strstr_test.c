#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char buf[16] = "testsing";
    char *id1, *pwd1 = "ori";
    int buflen = strlen(buf);
    
    printf("%ld\n", strlen(buf));
    puts(buf);
    id1 = strtok(buf, "/ ");
    // if (strncmp(id1, buf, strlen(id1)) == 0) {
    //     puts(id1);
    //     printf("wrong\n");
    //     exit(1);
    // }
    // if (strstr(" ", buf) == NULL) {
    //     printf("wrong\n");
    //     exit(1);
    // }
    // if (id1 = strtok(buf, " /") == NULL) {
    //     printf("wrong\n");
    //     exit(1);
    // }

    puts(buf);
    puts(id1);
    if (buflen == strlen(buf)) {
        printf("wrong\n");
        exit(1);
    }
    pwd1 = strtok(NULL, "/ ");

    puts(id1);
    puts(pwd1);

    return 0;
}