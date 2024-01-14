#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

int main() {
    struct sockaddr_in addr_in;
    struct sockaddr *addr;
    char *chptr;
    int *iptr;
    unsigned int i;

    bzero((char *)&addr_in, sizeof(addr_in));
    addr_in.sin_family = AF_INET;
    addr_in.sin_addr.s_addr = htonl(0x12345678);
    addr_in.sin_port = htons(0x1929);

    // chptr = (char *)&addr_in;
    // for(i = 0; i < 16; i++)
    //     printf("%c  ", *(chptr));
    // printf("\n");

    iptr = (int *)&addr_in;
    for(i = 0; i < 4; i++)
        printf("%u   ", *(iptr + i));
    printf("\n");
    
    bzero((char *)&addr, sizeof(addr));
    addr = (struct sockaddr *)&addr_in;
    printf("%d\n", addr->sa_family);
    printf("%lld\n", (unsigned long long)addr->sa_data);

    // chptr = (char *)addr;
    // for(i = 0; i < 16; i++)
    //     printf("%c  ", *(chptr + i));

    iptr = (int *)&addr_in;
    for(i = 0; i < 4; i++)
        printf("%u   ", *(iptr + i));
}