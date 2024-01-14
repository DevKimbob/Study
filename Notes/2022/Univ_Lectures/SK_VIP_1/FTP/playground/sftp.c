#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <dirent.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#include "sftp.h"

char command[][8] = {
    "open",
    "cd",
    "lcd",
    "ls",
    "lls",
    "get",
    "put",
    "close",
    "quit",
    "hash"
};

extern void chdir_req();
extern void lchdir();
extern void ls_req();
extern void lls();
extern void get_req();
extern void put_file();
extern void getv_put();
extern void readcmd();
extern void wait_ack();

char buf[MAX_PAGE];
char cmdline[MAX_LINE];
char cmd[10];
char parameter[MAX_LINE];
int sockfd;

header phead;
struct iovec iov[2];
FILE *outfp;

int hash;

int main(int argc, char *argv[]) {
    int param_no;
    int connection_established = 0, completed = 0;
    char *hostname;

    // socket(), connect()
    if (argc > 1) {
        hostname = argv[1];
        if ((sockfd = tcp_open(hostname, "fax", 0)) > 0)
            connection_established = 1;
        else
            fprintf(stderr, "Fail to connect to %s\n", hostname);
    }


    for (;;) {
        bzero(cmdline, MAX_LINE);
        readcmd(cmdline, MAX_LINE);

        bzero(cmd, 10);
        bzero(parameter, MAX_LINE);
        param_no = sscanf(cmdline, "%s %s", cmd, parameter);

        if (strcmp(cmd, command[0]) == 0) {
            if (connection_established) {
                fprintf(stderr, "Already connect to server\n");
            }
            else {
                if (param_no > 1) {
                    hostname = parameter;
                    if ((sockfd = tcp_open(hostname, "fax", 4557)) > 0)
                        connection_established = 1;
                    else
                        fprintf(stderr, "Fail to connect to %s\n", hostname);
                }
                else
                    fprintf(stderr, "You should specify the server!\n");
            }
        }
        else if (strcmp(cmd, command[1]) == 0) {
            if (connection_established) 
                chdir_req(param_no - 1);
            else
                fprintf(stderr, "You should connect to server, first\n");
        }
        else if (strcmp(cmd, command[2]) == 0)
            lchdir(param_no - 1);
        else if (strcmp(cmd, command[3]) == 0) {
            if (connection_established) 
                ls_req(param_no - 1);
            else
                fprintf(stderr, "You should connect to server, first\n");
        }
        else if (strcmp(cmd, command[4]) == 0) {
            lls(param_no - 1);
        }
        else if (strcmp(cmd, command[5]) == 0) {
            if (connection_established) {
                if (param_no < 2)
                    fprintf(stderr, "You should specify the file name\n");
                else
                    get_req(parameter);
            }
            else
                fprintf(stderr, "You should connect to server, first\n");
        }
        else if (strcmp(cmd, command[6]) == 0) {
            if (connection_established) {
                if (param_no < 2)
                    fprintf(stderr, "You should specify the file name\n");
                else
                    put_file(parameter);
            }
            else
                fprintf(stderr, "You should connect to server, first\n");
        }
        else if (strcmp(cmd, command[7]) == 0) {
            if (connection_established) {
                phead.cmd = 'e';
                iov[0].iov_base = (char *)&phead;
                iov[0].iov_len = sizeof(header);
                iov[1].iov_base = NULL;
                iov[1].iov_len = htons(0);
                writev(sockfd, &iov[0], 2);
                close(sockfd);
                connection_established = 0;
            }
            else
                fprintf(stderr, "You should connect to server, first\n");
        }
        else if (strcmp(cmd, command[8]) == 0) {
            if (connection_established) {
                phead.cmd = 'e';
                iov[0].iov_base = (char *)&phead;
                iov[0].iov_len = sizeof(header);
                iov[1].iov_base = NULL;
                iov[1].iov_len = htons(0);
                writev(sockfd, &iov[0], 2);
                close(sockfd);
            }
            break;
        }
        else if (strcmp(cmd, command[9]) == 0) {
            if (hash) {
                hash = 0;
                fprintf(stderr, "Hash is off\n");
            }
            else {
                hash = 1;
                fprintf(stderr, "Hash is on\n");
            }
        }
        else {
            fprintf(stderr, "commands list: open, cd, lcd, ls, lls, get, put, close, quit\n");
        }
    }
}