#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char check;
    long len;

    fp = fopen("test.txt", "r");
    fseek(fp, 0, SEEK_END);
    len = ftell(fp);
    rewind(fp);

    printf("Enter : ");
    scanf("%c", &check);
    
    while (ftell(fp) < len) {
        if (fgetc(fp) == check) {
            printf("Yes\n"); 
            exit(0);
        }
    }

    printf("No\n");
}