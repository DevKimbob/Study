#include <stdio.h>
#include <time.h>

char *output[] = {"%x %X", "%Gy %mm %dd %Uw %h:%M", "%r"};

int main() {
    struct tm *tm;
    int n;
    time_t timep;
    char buf[257];

    time(&timep);
    tm = localtime(&timep);

    for (n = 0; n < 3; n++) {
        strftime(buf, sizeof(buf), output[n], tm);
        printf("%s = %s\n", output[n], buf);
    }
}