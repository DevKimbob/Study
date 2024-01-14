#include <stdio.h>
#include <string.h>

char s[] = "Man is immortal, because he has a soul";
char seps[] = " ,\t\n";
char* token;

int main() {
    printf("String : %s\n\n", s);
    token = strtok(s, seps);

    while (token != NULL) {
        printf("Token : %s\n", token);
        token = strtok(NULL, seps);
    }

    return 0;
}