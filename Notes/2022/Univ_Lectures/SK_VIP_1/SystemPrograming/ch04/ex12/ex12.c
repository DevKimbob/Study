#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int n;
    char *file;
    FILE *fp;
    long length;
    char buf[2];

    file = argv[1];

    fp = fopen(file, "r");

    fseek(fp, 0, SEEK_END);
    length = ftell(fp);
    rewind(fp);
    
    while (ftell(fp) < length) {
        n = fread(buf, sizeof(char), 1, fp);
        buf[n] = '\0';
        fwrite(buf, sizeof(char), 1, stdout);
        fseek(fp, 1, SEEK_CUR);
    } 

    fclose(fp);
}