#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int n;
    char *file;
    FILE *fp;
    long length;
    char c;

    file = argv[1];

    fp = fopen(file, "r");

    fseek(fp, 0, SEEK_END);
    length = ftell(fp);
    rewind(fp);
    
    while (ftell(fp) < length) {
        c = getc(fp);
        putc(c, stdout);
        fseek(fp, 1, SEEK_CUR);
    } 

    fclose(fp);
}