#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    struct hostent *myhost;
    struct in_addr in;

    if (argc < 2) {
        printf("usage error\n");
        exit(1);
    }

    inet_pton(AF_INET, argv[1], &in.s_addr);
    myhost = gethostbyaddr((char *)&(in.s_addr), sizeof(in.s_addr), AF_INET);

    if (myhost == NULL) {
        printf("error : gethostbyaddr()\n");
        exit(1);
    }
    printf("host name : %s\n", myhost->h_name);

    return 0;
}