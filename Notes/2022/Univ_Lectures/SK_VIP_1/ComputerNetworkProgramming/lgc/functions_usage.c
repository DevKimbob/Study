#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    int listen_sock, accp_sock, connect_sock;
    int clilen;
    struct sockaddr_in serv, cli;
    char buf[100];

    serv.sin_family = AF_INET;
    serv.sin_addr = INADDR_ANY;
    serv.sin_port = htons(5000);

    // inet_addr();
    // inet_ntoa();

    listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    bind(listen_sock, (struct sockaddr *)&serv, sizeof(serv));
    listen(listen_sock, 5);

    connect(connect_sock, (struct sockaddr *)&servaddr, sizeof(servaddr));
    accp_sock = accept(listen_sock, (struct sockaddr *)&cli, &clilen);

    send(connect_sock, buf, sizeof(buf));
    recv(accp_sock, buf, sizeof(buf));
    
    write(connect_sock, buf, sizeof(buf));
    read(accp_sock, buf, sizeof(buf));

    close(connect_sock);
}