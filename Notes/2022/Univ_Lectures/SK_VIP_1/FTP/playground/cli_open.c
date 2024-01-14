#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

struct sockaddr_in tcp_srv_addr;
/*  struct sockaddr_in {
    sa_family_t sin_family;
    in_port_t sin_port;
    struct in_addr sin_addr;
};  */
struct servent tcp_serv_info;
/*  struct servent {
    char *s_name;
    char **s_aliases;
    int s_port;
    char *s_proto;
};  */
struct hostent tcp_host_info;
/*  struct hostent {
    char *h_name;
    char **h_aliases;
    int h_addrtype;
    int h_length;
    char ** h_addr_list;
};  */

int tcp_open(char *host, char *service, int port) {
    // var def
    int fd, resvport;
    unsigned long inaddr;
    struct servent *sp;  // temp
    struct hostent *hp;  // temp

    // tcp_srv_addr : init and set family
    bzero((char *)&tcp_srv_addr, sizeof(tcp_srv_addr));
    tcp_srv_addr.sin_family = AF_INET;
    
    // tcp_srv_addr : set port
    if (service != NULL) {  // service is given
        if ((sp = getservbyname(service, "tcp")) == NULL) {
            fprintf(stderr, "tcp_open: unknown service: %s/tcp\n", service);
            return(-1);
        }

        tcp_serv_info = *sp;

        if (port > 0) { // port is given
            tcp_srv_addr.sin_port = htons(port);
            printf("port : %d\n", ntohs(tcp_srv_addr.sin_port));
            puts("1111");
        }
        else { // use the port from /etc/services
            // tcp_srv_addr.sin_port = sp->s_port;
            tcp_srv_addr.sin_port = htons(4557);
            printf("port : %d\n", ntohs(tcp_srv_addr.sin_port));
            printf("port : %d\n", ntohs(sp->s_port));
            puts("2222");
        }
    }
    else {  // no services is given
        if (port <= 0) {  // no port is given
            fprintf(stderr, "tcp_open: must specity either service or port\n");
            return(-1);
        }

        tcp_srv_addr.sin_port = htons(port);  // port is given
    }

    // tcp_srv_addr : set ip_addr
    if ((inaddr = inet_addr(host)) != INADDR_NONE) {  // host as ip (ex 123.1.2.3), inet_addr : IPv4 numbers-and-dots notation -> binary data network byte order
        bcopy((char *)&inaddr, (char *)&tcp_srv_addr.sin_addr, sizeof(inaddr));
        tcp_host_info.h_name = NULL;
    }
    else {  // host as name (ex google.com)
        if ((hp = gethostbyname(host)) == NULL) {
            fprintf(stderr, "tcp_open: host name error: %s\n", host);
            return(-1);
        }

        tcp_host_info = *hp;
        bcopy(hp->h_addr, (char *)&tcp_srv_addr.sin_addr, hp->h_length);
    }

    // open socket
    if (port >= 0) {
        if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            fprintf(stderr, "tcp_open: can't create TCP socket\n");
            return(-1);
        }
    }

    printf("port : %d\n", ntohs(tcp_srv_addr.sin_port));
    // connect
    if (connect(fd, (struct sockaddr *)&tcp_srv_addr, sizeof(tcp_srv_addr)) < 0) {
        fprintf(stderr, "tcp_open: can't connect to server\n");
        close(fd);
        return(-1);
    }

    return(fd);
}