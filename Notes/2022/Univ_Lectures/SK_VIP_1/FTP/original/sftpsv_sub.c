#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
// #include <sys/dirent.h>
#include <dirent.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "sftp.h"

extern int verbose;
extern struct iovec iov[2];
extern header phead;
extern char buf[MAX_PAGE];

void wait_ack(int);
void send_ack(int);

void chdir_svc(int sockfd) {
    char *pathname;
    int length;

    if (ntohs(phead.datalen) > 0) {
        pathname = buf;
        chdir(pathname);
    }
    else
        chdir("");

    bzero(buf, MAX_PAGE);
    strcpy(buf, "cd is completed\n");
    length = strlen(buf);
    phead.cmd = 'f';
    phead.datalen = htons(length);
    iov[0].iov_base = (char *)&phead;
    iov[0].iov_len = sizeof(header);
    iov[1].iov_base = buf;
    iov[1].iov_len = length;
    writev(sockfd, &iov[0], 2);
}

void ls_svc(int sockfd) {
    int fd, length, pid;
    char cmdline[MAX_LINE], tmpf_name[MAX_LINE], *pathname;

    bzero(tmpf_name, MAX_LINE);
    pid = getpid();
    sprintf(tmpf_name, "/tmp/%d.dw", pid);

    bzero(cmdline, MAX_LINE);
    if (ntohs(phead.datalen) > 0) {
        pathname = buf;
        sprintf(cmdline, "ls -al %s > %s", buf, tmpf_name);
    }
    else    
        sprintf(cmdline, "ls -al > %s", tmpf_name);
    
    system(cmdline);

    fd = open(tmpf_name, O_RDONLY);
    while ((length = read(fd, buf, MAX_PAGE)) > 0) {
        phead.cmd = 'd';
        phead.datalen = htons(length);

        iov[0].iov_base = (char *)&phead;
        iov[0].iov_len = sizeof(header);
        iov[1].iov_base = buf;
        iov[1].iov_len = length;
        writev(sockfd, &iov[0], 2);

        wait_ack(sockfd);
    }

    close(fd);
    bzero(cmdline, MAX_LINE);
    sprintf(cmdline, "rm %s", tmpf_name);
    system(cmdline);

    phead.cmd = 'f';
    phead.datalen = htons(0);
    iov[0].iov_base = (char *)&phead;
    iov[0].iov_len = sizeof(header);
    iov[1].iov_base = NULL;
    iov[1].iov_len = 0;
    writev(sockfd, &iov[0], 2);
}

void get_svc(int sockfd) {
    int fd, length;
    char *pathname;

    if (ntohs(phead.datalen) > 0) {
        pathname = buf;
        if ((fd = open(pathname, O_RDONLY)) > 0) {
            while ((length = read(fd, buf, MAX_PAGE)) > 0) {
                phead.cmd = 'd';
                phead.datalen = htons(length);

                iov[0].iov_base = (char *)&phead;
                iov[0].iov_len = sizeof(header);
                iov[1].iov_base = buf;
                iov[1].iov_len = length;
                writev(sockfd, &iov[0], 2);
                wait_ack(sockfd);
                bzero(buf, MAX_PAGE);
            }
            close(fd);

            phead.cmd = 'f';
            phead.datalen = htons(0);
            iov[0].iov_base = (char *)&phead;
            iov[0].iov_len = sizeof(header);
            iov[1].iov_base = NULL;
            iov[1].iov_len = 0;
            writev(sockfd, &iov[0], 2);
        }
        else {
            sprintf(buf, "fail to open %s", pathname);
            length = strlen(buf);

            phead.cmd = 'f';
            phead.datalen = htons(0);
            iov[0].iov_base = (char *)&phead;
            iov[0].iov_len = sizeof(header);
            iov[1].iov_base = buf;
            iov[1].iov_len = length;
            writev(sockfd, &iov[0], 2);
        }
    }
    else {
        strcpy(buf, "file name missing!");
        length = strlen(buf);
        phead.cmd = 'f';
        phead.datalen = htons(0);
        iov[0].iov_base = (char *)&phead;
        iov[0].iov_len = sizeof(header);
        iov[1].iov_base = buf;
        iov[1].iov_len = length;
        writev(sockfd, &iov[0], 2);
    }
}

void put_svc(int sockfd) {
    FILE *outfp;
    int completed = 0, length;
    char *pathname;

    if (ntohs(phead.datalen) > 0) {
        pathname = buf;
        if ((outfp = fopen(pathname, "w")) != NULL) {
            send_ack(sockfd);

            bzero(buf, MAX_PAGE);
            iov[0].iov_base = (char *)&phead;
            iov[0].iov_len = sizeof(header);
            iov[1].iov_base = buf;
            iov[1].iov_len = MAX_PAGE;
            readv(sockfd, &iov[0], 2);

            while (phead.cmd == 'd') {
                fwrite(buf, ntohs(phead.datalen), 1, outfp);
                send_ack(sockfd);

                bzero(buf, MAX_PAGE);
                iov[0].iov_base = (char *)&phead;
                iov[0].iov_len = sizeof(header);
                iov[1].iov_base = buf;
                iov[1].iov_len = MAX_PAGE;
                readv(sockfd, &iov[0], 2);
            }

            if (phead.cmd == 'f') {
                fwrite(buf, ntohs(phead.datalen), 1, outfp);
            }
            else
                ;
        }
        fclose(outfp);
    }
}

void send_ack(int sockfd) {
    phead.cmd = 'a';
    phead.datalen = htons(0);

    iov[0].iov_base = (char *)&phead;
    iov[0].iov_len = sizeof(header);
    iov[1].iov_base = NULL;
    iov[1].iov_len = 0;
    writev(sockfd, &iov[0], 2);
}

void wait_ack(int sockfd) {
    bzero(buf, MAX_PAGE);

    iov[0].iov_base = (char *)&phead;
    iov[0].iov_len = sizeof(header);
    iov[1].iov_base = buf;
    iov[1].iov_len = MAX_PAGE;
    readv(sockfd, &iov[0], 2);

    if (phead.cmd == 'a') 
        return;
    else
        ;
}