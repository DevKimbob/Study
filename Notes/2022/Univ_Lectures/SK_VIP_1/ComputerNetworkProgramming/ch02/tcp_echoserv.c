#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAXLINE 127

int main(int argc, char *argv[]) {
    struct sockaddr_in servaddr, servaddr2, cliaddr, cliaddr2;
    int listen_sock, accp_sock, addrlen = sizeof(cliaddr), nbyte;
    char buf[MAXLINE + 1];
    char buf_cliaddr[20];

    if (argc != 2) {
        printf("error : arg");
        exit(1);
    }

    if ((listen_sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket fail");
        exit(0);
    }

    bzero((char *)&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));

    if (bind(listen_sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind fail");
        exit(1);
    }

    printf("  bef lst server port : %d\n", ntohs(servaddr.sin_port));
    getsockname(listen_sock, (struct sockaddr *)&servaddr2, &addrlen);
    printf("  bef lst server port : %d\n", ntohs(servaddr2.sin_port));
    listen(listen_sock, 5);
    while (1) {
        puts("Server waiting for connection request...");
        printf("  aft lst server port : %d\n", ntohs(servaddr.sin_port));
        getsockname(listen_sock, (struct sockaddr *)&servaddr2, &addrlen);
        printf("  aft lst server port : %d\n", ntohs(servaddr2.sin_port));

        accp_sock = accept(listen_sock, (struct sockaddr *)&cliaddr, &addrlen);
        if (accp_sock < 0) {
            perror("accept fail");
            exit(1);
        }

        puts("Client connected...");
        inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, buf_cliaddr, sizeof(buf_cliaddr));
        printf("  client addr : %s\n", buf_cliaddr);
        printf("  client port : %d\n", ntohs(cliaddr.sin_port));

        getpeername(accp_sock, (struct sockaddr *)&cliaddr2, &addrlen);
        printf("  client port : %d\n", ntohs(cliaddr2.sin_port));

        nbyte = read(accp_sock, buf, MAXLINE);
        write(accp_sock, buf, nbyte);
        close(accp_sock);
    }
    close(listen_sock);
    return 0;
}