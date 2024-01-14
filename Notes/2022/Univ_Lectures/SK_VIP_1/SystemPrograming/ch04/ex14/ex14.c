#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *rfp, *wfp;
    char buf[BUFSIZ];
    int n;
    
    rfp = fopen(argv[1], "r");
    wfp = fopen(argv[2], "w");

    while ((n = fread(buf, sizeof(char), BUFSIZ, rfp)) > 0) {
        fwrite(buf, sizeof(char), n, wfp);
    }

    fclose(rfp);
    fclose(wfp);
    remove(argv[1]);
}