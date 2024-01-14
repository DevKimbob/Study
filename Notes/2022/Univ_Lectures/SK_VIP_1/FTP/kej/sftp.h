/*all:
	make sftp
	make sfrps
	make sfrpd
	
sftp: sftp.o sftp_sub.o cli_open.o
	cc -o sftps sftps.o sftpsv_sub.o
	
sftps: sftps.o sftpsv_sub.o
	cc -o sftps sftps.o sftpsv_sub.o
	
sftpd: sftpd.o sftpsv_sub.o
	cc -o sftpd sftpd.o sftpsv_sub.o
	
sftp.o: sftp.c
sftps.o: sftps.c
sftpd.o: sftpd.c
sftp_sub.o: sftp_sub.c
sftpsv_sub.o: sftpsv_sub.c
cli_open.o: cli_open.c*/

#ifndef _SFTP_H
#define _SFTP_H

#define MAX_LINE	80
#define MAX_PAGE	1024
#define SERV_TCP_PORT	2000

typedef struct _header {
	int	datalen;
	char	cmd;
}header;

#endif
