#include <stdio.h>
#include <sys/utsname.h>
#include <unistd.h>

int main() {
    struct utsname un;
    char host[100];

    uname(&un);
    gethostname(host, 100);

    printf("uname : %s\n", un.machine);  // get host name from uname..?
    printf("gethostname : %s\n", host);
}