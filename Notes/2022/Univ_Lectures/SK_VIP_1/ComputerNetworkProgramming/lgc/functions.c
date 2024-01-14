#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    inet_addr();
    inet_ntoa();

    socket();
    bind();
    listen();
    accept();
    connect();

    recv();
    send();
}