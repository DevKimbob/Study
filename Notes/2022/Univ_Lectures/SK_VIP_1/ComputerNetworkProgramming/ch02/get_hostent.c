#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    struct hostent *hp;
    struct in_addr in;
    int i;
    char buf[20];

    if (argc < 2) {
        printf("Usage : %s hostname\n", argv[0]);
        exit(1);
    }

    hp = gethostbyname(argv[1]);
    if (hp == NULL) {
        printf("gethostbyname fail\n");
        exit(1);
    }

    printf("hostname : %s\n", hp->h_name);
    printf("host address type no. : %d\n", hp->h_addrtype);
    printf("host address length : %dbytes\n", hp->h_length);

    for (i = 0; hp->h_addr_list[i]; i++) {
        memcpy(&in.s_addr, hp->h_addr_list[i], sizeof(in.s_addr));
        inet_ntop(AF_INET, &in, buf, sizeof(buf));
        printf("IP address(%dth) : %s\n", i + 1, buf);
    }

    for (i = 0; hp->h_aliases[i]; i++)
        printf("host aliases(%dth) : %s", i + 1, hp->h_aliases[i]);
    puts("");

    return 0;
}