#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/wait.h>
#include <netdb.h>

#define MAXLINE 511

// vputs("verbose test");  is equivalent to
// if (verbose) puts("verbose test");
#define vputs(format) { \
    if (verbose) \
        puts(format); \
}

char *EXIT_STRING = "exit";
char *LOGOUT_STRING = "logout";
static pid_t pid;  // fork pid
static char login_id[32];  // login user's id
static int verbose = 0;  // verbose switch

int public_ip(char *buf, int size);
int login_serv(int sd);
int recv_and_print(int sd);
int select_op();
void sig_child(int signo);

int main(int argc, char *argv[]) {
    struct sockaddr_in servaddr, cliaddr;
    struct sigaction act, act_usr1;
    int listen_sock, accp_sock, addrlen = sizeof(cliaddr), status;
    char buf_addr[16];
    
    // argment check
    if ((argc != 1) && (argc != 2)) {
        printf("** Usage : %s [--verbose]\n", argv[0]);
        exit(1);
    }

    // --verbose option check
    if ((argc == 2) && (strcmp(argv[1], "--verbose") == 0)) {
        verbose = 1;
    }

    // signal handler for defunc handling
    bzero((char *)&act, sizeof(act));
    act.sa_handler = sig_child;
    act.sa_flags = SA_RESTART;
    act.sa_flags |= SA_NOCLDWAIT;

    // set signal handler
    vputs("-- setting signal handler : sigchild");
    if (sigaction(SIGCHLD, &act, (struct sigaction *)NULL)) {
        perror("sigaction");
        exit(1);
    }

    // set listen_sock
    vputs("-- setting listen socket for tcp/ip connection");
    if ((listen_sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket fail");
        exit(1);
    }

    // set server address struct
    vputs("-- setting server address structure");
    bzero((char *)&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(0);

    // bind server address structure to listen socket
    vputs("-- binding server address info to listen socket");
    if (bind(listen_sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind fail");
        exit(1);
    }

    // print ip, port of the server
    getsockname(listen_sock, (struct sockaddr *)&servaddr, &addrlen);
    public_ip(buf_addr, sizeof(buf_addr));
    //printf("** Server openned at %s:%d\n", buf_addr, ntohs(servaddr.sin_port));
	printf("** Server openned at port : %d\n", ntohs(servaddr.sin_port));

    // listen on listen socket
    puts("** Server waiting for Client...\n");
    vputs("-- listening on listen socket");
    listen(listen_sock, 5);
    for (;;) {
        // accept to accept socket
        if ((accp_sock = accept(listen_sock, (struct sockaddr *)&cliaddr, &addrlen)) < 0) {
            perror("accept fail");
            exit(1);
        }

        // print ip, port of the client
        vputs("-- accepted incomming connection request to accept socket");
        inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, buf_addr, sizeof(buf_addr));
        printf("** Client connected from %s:%d\n", buf_addr, ntohs(cliaddr.sin_port));

        // fork process
        if ((pid = fork()) > 0) {  // parent process
            printf("** Redirecting to child process (PID : %d)\n\n", pid);
            vputs("-- parent : closing accept socket");
            vputs("-- parent : adding pid to list");
            close(accp_sock);  // close accept socket and continue for(;;) loop
        }
        else if (pid == 0) {  // child process
            while (1) {
                // login mode
                vputs("-- login_serv function called");
                status = login_serv(accp_sock);
                vputs("-- write : sending return status of login_serv to client");
                write(accp_sock, &status, sizeof(int));  // return login function's status to client

                if (status == 1) {  // 1 : Match found, login success
                    // login success, receive mode
                    vputs("-- changing to receiving mode");
                    if (recv_and_print(accp_sock) == 1) {
                        continue;
                    }
                }
                else if (status == -1) {  // -1 : EXIT_STRING came as input
                    break;
                }
                else {}  // 0 : Wrong usage, 2 : Wrong password, 3: No id found => continue while(1) loop : redo login function
            }

            puts("** Client disconnected");
            printf("** Terminating process (PID : %d)\n", getpid());
            break;
        }
    }

    close(listen_sock);
    return 0;
}

int public_ip(char *buf, int size) {
    FILE *fp;

    // popen : run fork() internally
    // -child process : run "$ curl -s ifconfig.me" in shell and write result(ip) to pipe(fp)
    // $ curl -s ifconfig.me  # returns public ip address..?, -s : silent option
    vputs("-- receiving ip address");
    if ((fp = popen("curl -s ifconfig.me", "r")) == NULL) {
        perror("popen");
        exit(1);
    }

    // -parent process : read ip from fp and store to buf
    if (fgets(buf, size, fp) == NULL) {
        perror("fgets");
        exit(1);
    }
    pclose(fp);
}

int recv_and_print(int sd) {
    char buf[MAXLINE + 1];
    int nbyte;

    for (;;) {
        // read from client and store to buf
        if ((nbyte = read(sd, buf, MAXLINE)) < 0) {
            perror("read fail : recv");
            close(sd);
            exit(1);
        }
        buf[nbyte] = 0;  // add null

        // if buf == "logout" --ish
        if (strstr(buf, LOGOUT_STRING) != NULL) {
            vputs("-- user logged out, returning to login mode");
            printf("\n * Client logged out : %s\n", login_id);
            puts(" * Waiting for reconnection");
            return 1;
        }

        printf(" * Received from %s : %s", login_id, buf);
    }
    return 0;
}

int login_serv(int sd) {
	FILE *fp;
	int nbyte, buflen, i = 0;
	char buf[MAXLINE + 1];
	char *id1, *pwd1;
	char id2[32], pwd2[32];

    // read from client and store to buf
    vputs("-- read : waiting for client to enter id & password");
	if ((nbyte = read(sd, buf, MAXLINE)) < 0) {
		perror("read fail : login");
		close(sd);
		exit(1);
	}
	buf[nbyte] = 0;  // add null
    vputs("-- read complete");

    // if buf == "exit" --ish
	if (strstr(buf, EXIT_STRING) != NULL) {
        vputs("-- user exited from service, terminating prcess");
		printf("\n * Good bye\n");
        return -1;
    }

    // change "buf = id password" to
    // id1 = id, pwd1 = password
    buflen = strlen(buf);
    id1= strtok(buf, " /");  // slice by ' ' and '/'
	if (strlen(buf) == buflen) {  // if input had no ' ' or '/'
		printf(" * Wrong input : %s", buf);
        puts(" * (usage : <id> <password>)");
		return 0;
	}
	pwd1 = strtok(NULL, " /");

    // open accounts.txt
    vputs("-- fopen : open accounts.txt for database search");
	fp = fopen("./lib/accounts.txt", "r");
	// fp = fopen("../lib/accounts.txt", "r");  // option for executing from bin directory
	while (fscanf(fp, "%s %s", id2, pwd2) > 0) {
		if (strncmp(id1, id2, strlen(id2)) == 0) {  // if id1(input) == id2(from accounts.txt)
			if (strncmp(pwd1, pwd2, strlen(pwd2)) == 0) {  // if pwd1(input) == pwd2(from accounts.txt)
				printf(" * Match found\n");
                printf(" * Logged in as : %s\n\n", id1);
                strncpy(login_id, id1, strlen(id1));
				return 1;
			}
			else {  // if pwd1(input) != pwd2(from accounts.txt)
				printf(" * Wrong password for : %s\n", id1);
				return 2;
			}
		}
	}

	printf(" * No matches found for : %s\n", id1);  // if id1(input) != id2(from accounts.txt)
	fclose(fp);
	return 3;
}

void sig_child(int signo) {
    while (waitpid(-1, NULL, WNOHANG) == 0) {}
}
