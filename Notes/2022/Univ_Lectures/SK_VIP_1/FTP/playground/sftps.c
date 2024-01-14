#include <fcntl.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>
// #include <sys/dirent.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sftp.h"

extern void chdir_svc();
extern void ls_svc();
extern void get_svc();
extern void put_svc();
extern void send_ack();
extern void wait_ack();

struct iovec iov[2];
int verbose = 0;
header phead;
char buf[MAX_PAGE];

int main(int argc, char *argv[]) {
    struct sockaddr_in cli_addr, serv_addr;
    int sockfd, newsockfd;
    int clilen;
    int completed = 0;

    if ((argc > 1) && (argv[1][0] == 'v' || argv[1][0] == 'V'))
        verbose = 1;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "%s: socket error\n", argv[0]);
        exit(1);
    }

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(4557);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        fprintf(stderr, "%s: bind error\n", argv[0]);
        exit(2);
    }

    listen(sockfd, 5);
    for (;;) {
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd > 0) {
            completed = 0;

            if (verbose)
                fprintf(stderr, "connection is established\n");

            while (!completed) {
                bzero((char *)&phead, sizeof(header));
                bzero(buf, MAX_PAGE);

                iov[0].iov_base = (char *)&phead;
                iov[0].iov_len = sizeof(header);
                iov[1].iov_base = buf;
                iov[1].iov_len = MAX_PAGE;

                if ((readv(newsockfd, &iov[0], 2)) > 0) {
                    switch (phead.cmd) {
                        case 'c':
                            if (verbose)
                                fprintf(stderr, "cd request\n");
                            chdir_svc(newsockfd);
                            break;
                        case 'l':
                            if (verbose)
                                fprintf(stderr, "ls request\n");
                            ls_svc(newsockfd);
                            break;
                        case 'g':
                            if (verbose)
                                fprintf(stderr, "get request\n");
                            get_svc(newsockfd);
                            break;
                        case 'p':
                            if (verbose)
                                fprintf(stderr, "put request\n");
                            put_svc(newsockfd);
                            break;
                        otherwise:
                            completed = 1;
                    }
                } else
                    completed = 1;
            }
            close(newsockfd);
            if (verbose)
                fprintf(stderr, "socket is closed\n");
        }
    }
}