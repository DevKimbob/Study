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

// vputs("verbose test");  is equivalent to
// if (verbose) puts("verbose test");
#define vputs(format) { \
    if (verbose) \
        puts(format); \
}

char *EXIT_STRING = "exit";
char *LOGOUT_STRING = "logout";
static int verbose = 0;  // verbose switch

int login_client(int sd);
int input_and_send(int sd);

int main(int argc, char *argv[]) {
    static struct sockaddr_in servaddr;
    static int s;
    int status;

    // argument check
    if ((argc != 3) && (argc != 4)) {
        printf("** Usage : %s <IP> <port> [--verbose]\n", argv[0]);
        exit(1);
    }

    // --verbose option check
    if ((argc == 4) && (strcmp(argv[3], "--verbose") == 0)) {
        verbose = 1;
    }

    // set connecting socket
    vputs("-- setting connecting socket for tcp/ip connection");
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        puts("Client: can't open stream socket");
        perror("socket fail");
        exit(1);
    }

    // set server address struct
    vputs("-- setting server address structure");
    bzero((char *)&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    servaddr.sin_port = htons(atoi(argv[2]));

    // connect to server
    vputs("-- sending connection request to the server");
    if (connect(s, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        puts("Client: can't connecto to server");
        perror("connect fail");
        exit(1);
    }
    puts("** Connectd to server\n");
    puts("** Type \"exit\" to disconnect");

    while (1) {
        // login mode
        switch (status = login_client(s)) {
            case 1:
                // login success, send mode
                printf(" * Login success\n\n");
                vputs("-- changing to sending mode");
                input_and_send(s);
                puts("** Type \"exit\" to disconnect");
                vputs("-- changing to login mode");
                break;  // break from switch-case and continue while(1) loop : redo login function
            case 2:
                puts(" * Wrong password\n");
                break;  // break from switch-case and continue while(1) loop : redo login function
            case 3:
                puts(" * No id match found\n");
                break;  // break from switch-case and continue while(1) loop : redo login function
            case 0:
                puts(" * Wrong format\n");
                break;  // break from switch-case and continue while(1) loop : redo login function
            case -1:
                close(s);
                return 0;
            default:
                printf("** Unknown error, exiting...\n");
                break;
        }
    }

    close(s);
    return 0;
}

int login_client(int sd) {
    char buf[MAXLINE + 1];
    int nbyte, result;

    puts(" * Usage : ID / Password");
    vputs("-- fgets : getting input from user");
    printf(" * Login >> ");
    // read from stdin and store in buf
    if (fgets(buf, sizeof(buf), stdin) != NULL) {
        vputs("-- write : sending input to server");
        write(sd, buf, strlen(buf));  // write to server from buf

        // if buf == "exit" --ish
        if (strstr(buf, EXIT_STRING) != NULL) {
            vputs("-- user entered exit");
            puts("\n** Disconnected from server");
            puts("** Good bye");
            close(sd);
            exit(0);
        }
    }

    // read from server(login_serv return) and store in result and return 
    vputs("-- read : receiving return status from sever");
    if ((nbyte = read(sd, &result, sizeof(int))) < 0) {
        perror("read fail");
        exit(1);
    }
    return result;
}

int input_and_send(int sd) {
    char buf[MAXLINE+1];
 
    vputs("-- fgets : getting input from user");
    printf(" * To server >> ");
    // read from stdin and store in buf
    while(fgets(buf, sizeof(buf), stdin) != NULL) {
        vputs("-- write : sending input to server");
        write(sd, buf, strlen(buf));  // write to server from buf
 
        // if buf == "logout" --ish
        if (strstr(buf, LOGOUT_STRING) != NULL ) {
            vputs("-- user entered logout");
            puts(" * Logged out, login to reconnect\n");
            return 1;
        }
        vputs("-- fgets : getting input from user");
        printf(" * To server >> ");
    }
    return 0;
}