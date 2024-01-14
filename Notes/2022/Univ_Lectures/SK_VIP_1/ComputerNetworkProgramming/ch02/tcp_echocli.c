#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXLINE 127

int main(int argc, char *argv[]) {
    struct sockaddr_in servaddr;
    int s, nbyte;
    char buf[MAXLINE + 1];

    if (argc != 3) {
        printf("error : arg");
        exit(1);
    }

    if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket fail");
        exit(1);
    }

    bzero((char *)&servaddr, sizeof(servaddr));  // servaddr '\0'
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    servaddr.sin_port = htons(atoi(argv[2]));

    if (connect(s, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("connect fail");
        exit(1);
    }

    printf("Input : ");
    if (fgets(buf, sizeof(buf), stdin) == NULL)
        exit(1);
    nbyte = strlen(buf);

    if (write(s, buf, nbyte) < 0) {
        printf("error : write");
        exit(1);
    }

    printf("Receive : ");
    if ((nbyte = read(s, buf, MAXLINE)) < 0) {
        perror("read fail");
        exit(1);
    }

    buf[nbyte] = 0;
    printf("%s", buf);
    close(s);
    return 0;
}