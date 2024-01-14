#include <stdio.h>

int main() {
    int ch;
    int i = 0;
    while ((ch = getch()) != EOF) {
        printf("%02d / printf : %c / putch : ", i, ch);
        putch(ch);
        printf("\n");
        i++;
    }
    return 0;
}
