#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

#define MAXLINE 511

char *EXIT_STRING = "exit";
int recv_and_print(int sd);
int input_and_send(int sd);
void sig_handler(int signo);

static int accp_sock;

int main(int argc, char *argv[]) {
    struct sockaddr_in cliaddr, servaddr;
    int listen_sock, addrlen = sizeof(cliaddr);
    pid_t pid;

    // if (argc != 2) {
    //     printf("%s <port>\n", argv[0]);
    //     exit(1);
    // }

    if ((listen_sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket fail");
        exit(1);
    }

    bzero((char *)&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // servaddr.sin_port = htons(atoi(argv[1]));
    servaddr.sin_port = htons(0);

    if(bind(listen_sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind fail");
        exit(1);
    }

    puts("Server waiting for Client...");
    listen(listen_sock, 1);

    if (getsockname(listen_sock, (struct sockaddr *)&servaddr, &addrlen) < 0) {
        perror("getsockname");
        exit(1);
    }
    printf("Use port : %d\n", ntohs(servaddr.sin_port));

    if ((accp_sock = accept(listen_sock, (struct sockaddr *)&cliaddr, &addrlen)) < 0) {
        perror("accept fail");
        exit(1);
    }

    puts("Client connected");
    if ((pid = fork()) > 0)
        input_and_send(accp_sock);
    else if (pid == 0)
        recv_and_print(accp_sock);
    
    close(listen_sock);
    close(accp_sock);
    return 0;
}

int input_and_send(int sd) {
    char buf[MAXLINE + 1];
    int nbyte;

    signal(SIGUSR1, sig_handler);

    while(fgets(buf, sizeof(buf), stdin) != NULL) {
        nbyte = strlen(buf);
        write(sd, buf, strlen(buf));
        
        if (strstr(buf, EXIT_STRING) != NULL) {
            puts("Good bye.");
            close(sd);
            exit(0);
        }
    }

    return 0;
}

int recv_and_print(int sd) {
    char buf[MAXLINE + 1];
    int nbyte;
    int ppid;

    while(1) {
        if ((nbyte = read(sd, buf, MAXLINE)) < 0 ) {
            perror("read fail");
            close(sd);
            exit(1);
        }
        buf[nbyte] = 0;
        
        if (strstr(buf, EXIT_STRING) != NULL) {
            ppid = getppid();
            if (ppid != 1)
                kill(ppid, SIGUSR1);

            break;
        }
        printf("%s", buf);
    }

    return 0;
}

void sig_handler(int signo) {
    puts("From client : Good bye.");
    sleep(1);
    write(accp_sock, EXIT_STRING, sizeof(EXIT_STRING));
    close(accp_sock);
    exit(0);
}