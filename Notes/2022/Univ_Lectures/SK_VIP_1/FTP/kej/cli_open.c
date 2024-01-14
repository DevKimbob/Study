#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string.h>
#include <unistd.h>

struct sockaddr_in tcp_srv_addr;
struct servent		tcp_serv_info;
struct hostent		tcp_host_info;

int tcp_open(char *host, char *service, int port)
// char *host;
// char *service;
// int port;
{
	int		fd, resvport;
	unsigned long	inaddr;
	struct servent	*sp;
	struct hostent	*hp;
	
	bzero((char*)&tcp_srv_addr, sizeof(tcp_srv_addr));
	tcp_srv_addr.sin_family = AF_INET;
	if(service != NULL) {
		if((sp = getservbyname(service, "tcp")) == NULL) {
			fprintf(stderr, "tcp_open:unknown service: %s/tcp", service);
			return(-1);
		}
		
		tcp_serv_info = *sp;
		
		if(port > 0)
			tcp_srv_addr.sin_port = htons(port);
		else
			tcp_srv_addr.sin_port = sp->s_port;
	}
	else {
		if(port <= 0) {
			fprintf(stderr, "tcp_open: must specify either service or port");
			return(-1);
		}
		tcp_srv_addr.sin_port = htons(port);
	}
	
	if((inaddr = inet_addr(host)) != INADDR_NONE) {
		bcopy((char *)&inaddr, (char *)&tcp_srv_addr.sin_addr, sizeof(inaddr));
		tcp_host_info.h_name = NULL;
	}
	else {
		if((hp = gethostbyname(host)) == NULL) {
			fprintf(stderr, "tcp_open: host name error: %s", host);
			return(-1);
		}
		tcp_host_info = *hp;
		bcopy(hp->h_addr, (char *)&tcp_srv_addr.sin_addr, hp->h_length);
	}
	if(port >= 0) {
		if((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
			fprintf(stderr, "tcp_open: can't create TCP socket");
			return(-1);
		}
	}
	
	if(connect(fd, (struct sockaddr *)&tcp_srv_addr, sizeof(tcp_srv_addr)) < 0) {
		fprintf(stderr, "tcp_open: can't connect tp server");
		
		close(fd);
		return(-1);
	}
	
	return(fd);
}
