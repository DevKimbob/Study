#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>	/*for readv, writev*/
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "sftp.h"

extern char	buf[MAX_PAGE];
extern char	cmdline[MAX_LINE];
extern char	cmd[10];
extern char	parameter[MAX_LINE];
extern int	sockfd;
extern int	hash;
extern FILE	*outfp;

extern header	phead;
extern struct iovec iov[2];

int getv_put(int, FILE *);
void wait_ack();

/*****************************************************/

void chdir_req(int path_no)
// int path_no;
{
	char	*pathname;
	int	length;
	
	if(path_no > 0) {
		pathname = parameter;
		length = strlen(pathname);
		fprintf(stderr, "Attempt tp cd %s\n", pathname);
		iov[1].iov_base = pathname;
		iov[1].iov_len = length;
	}
	else {
		length = 0;
		fprintf(stderr, "Directory name is missing\n");
		iov[1].iov_base = NULL;
		iov[1].iov_len = 0;
	}
	
	phead.datalen = htons(length);
	phead.cmd = 'c';
	iov[0].iov_base = (char *)&phead;
	iov[0].iov_len = sizeof(header);
	writev(sockfd, &iov[0], 2);	/*send request*/
	
	getv_put(sockfd, stdout);	/*get response and put*/
}

/*****************************************************/

void lchdir(int path_no)
// int path_no;
{
	char	*pathname;
	int	length;
	
	if(path_no > 0) {
		pathname = parameter;
		length = strlen(pathname);
		fprintf(stderr, "local chdir %s\n", pathname);
		chdir(pathname);
	}
	else {
		fprintf(stderr, "Directory name is missing\n");
	}
}

/*****************************************************/

void ls_req(int path_no)
// int path_no;
{
	char	*pathname;
	int	length;
	
	if(path_no > 0) {
		pathname = parameter;
		length = strlen(pathname);
		iov[1].iov_base = pathname;
		iov[1].iov_len = length;
	}
	else {
		length = 0;
		iov[1].iov_base = NULL;
		iov[1].iov_len = 0;
	}
	
	phead.cmd = 'l';
	phead.datalen = htons(length);
	
	iov[0].iov_base = (char *)&phead;
	iov[0].iov_len = sizeof(header);
	
	writev(sockfd, &iov[0], 2);
	getv_put(sockfd, stdout);
}

/*****************************************************/

void lls(int path_no)
// int path_no;
{
	char	*pathname;
	int	length;
	
	bzero(cmdline, MAX_LINE);
	
	if(path_no > 0) {
		pathname = parameter;
		sprintf(cmdline, "ls -al %s", pathname);
	}
	else {
		strcpy(cmdline, "ls -al");
	}
	system(cmdline);
	fflush(stdout);
}

/*****************************************************/

void get_req(char *pathname)
// char *pathname;
{
	int	length;
	
	length = strlen(pathname);
	outfp = fopen(pathname, "w");
	
	phead.datalen = htons(length);
	phead.cmd = 'g';
	iov[0].iov_base = (char *)&phead;
	iov[0].iov_len = sizeof(header);
	iov[1].iov_base = pathname;
	iov[1].iov_len = length;
	writev(sockfd, &iov[0], 2);	/*send request*/
	
	getv_put(sockfd, outfp);
	fclose(outfp);
}

/*****************************************************/

void put_file(char *pathname)
// char *pathname;
{
	int	length;
	int 	fd;
	
	if((fd = open(pathname, O_RDONLY)) < 0) {
		fprintf(stderr, "fail to open %s\n", pathname);
		return;
	}
	
	length = strlen(pathname);
	phead.cmd = 'p';
	phead.datalen = htons(length);
	iov[0].iov_base = (char *)&phead;
	iov[0].iov_len = sizeof(header);
	iov[1].iov_base = pathname;
	iov[1].iov_len = length;
	writev(sockfd, &iov[0], 2);	/*send request*/
	
	wait_ack();
	
	while((length = read(fd, buf, MAX_PAGE)) > 0) {
		phead.cmd = 'd';
		phead.datalen = htons(length);
		iov[0].iov_base = (char *)&phead;
		iov[0].iov_len = sizeof(header);
		iov[1].iov_base = buf;
		iov[1].iov_len = MAX_PAGE;
		writev(sockfd, &iov[0], 2);
		if(hash)
			putc('#', stderr);
		
		wait_ack();
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

/*****************************************************/

int getv_put(int sockfd, FILE *fp)
// int sockfd;
// FILE *fp;
{
	int		completed = 0, length, i;
	
	while(!completed) {
		bzero(buf, MAX_PAGE);
		iov[0].iov_base = (char *)&phead;
		iov[0].iov_len = sizeof(header);
		iov[1].iov_base = buf;
		iov[1].iov_len = MAX_PAGE;
		readv(sockfd, &iov[0], 2);	/*Read response*/
		
		length = ntohs(phead.datalen);
		buf[strlen(buf)] = 0;
		if(length > 0) {
			switch (phead.cmd) {
				case 'e': /*error*/
					break;
				case 'f': /*end of file*/
					fwrite(buf, length, 1, fp);
					if(hash && (fp != stdout) && (fp != stderr))
						putc('#', stderr);
					completed = 1;
					break;
				case 'd': /*data*/
					fwrite(buf, length, 1, fp);
					if(hash && (fp != stdout) && (fp != stderr))
						putc('#', stderr);
					break;
			}
		}
		else /*data length == 0*/
			completed = 1;
			
		phead.cmd = 'a';	/*Acknowledgement*/
		phead.datalen = htons(0);
		iov[0].iov_base = (char *)&phead;
		iov[0].iov_len = sizeof(header);
		iov[1].iov_base = NULL;
		iov[1].iov_len = 0;
		writev(sockfd, &iov[0], 2);
	}
	if(hash && (fp != stdout) && (fp != stderr))
		putc('\n', stderr);
}

/*****************************************************/

int readcmd(char *ptr, int maxlen)
// char *ptr;
// int maxlen;
{
	int	n, rc;
	char	c;
	
	fprintf(stdout, "Commaned >> ");
	fflush(stdout);
	
	for(n = 1; n < maxlen; n++) {
		c = getchar();
		*ptr++ = c;
		if(c == '\n')
			break;
	}
	
	*ptr = 0; /*'\0'*/
	return(n);
}

/*****************************************************/

void wait_ack()
{
	bzero(buf, MAX_PAGE);
	
	iov[0].iov_base = (char *)&phead;
	iov[0].iov_len = sizeof(header);
	iov[1].iov_base = buf;
	iov[1].iov_len = MAX_PAGE;
	readv(sockfd, &iov[0], 2);
	
	if(phead.cmd == 'a')
		return;
	else	/*error*/
		;
}
