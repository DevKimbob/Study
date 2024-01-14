#include <stdio.h>

int main() {
    int ch;
    int i = 0;
    while ((ch = getchar()) != EOF) {
        printf("%02d / printf : %c / putchar : ", i, ch);
        putchar(ch);
        printf("\n");
        i++;
    }
    return 0;
}