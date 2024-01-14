#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>

int main() {
    struct servent *servent;

    servent = getservbyname("echo", "udp");
    if (servent == NULL) {
        printf("cannot get service info\n\n");
        exit(0);
    }

    printf("UDP echo portnumber(network) : %d\n", servent->s_port);
    printf("UDP echo portnumber(host) : %d\n", ntohs(servent->s_port));

    return 0;
}