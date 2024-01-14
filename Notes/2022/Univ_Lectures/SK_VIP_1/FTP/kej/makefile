all:
	make sftp
	make sftps
	make sftpd
	
sftp: sftp.o sftp_sub.o cli_open.o
	cc -o sftp sftp.o sftp_sub.o cli_open.o
	
sftps: sftps.o sftpsv_sub.o
	cc -o sftps sftps.o sftpsv_sub.o
	
sftpd: sftpd.o sftpsv_sub.o
	cc -o sftpd sftpd.o sftpsv_sub.o
	
sftp.o: sftp.c
sftps.o: sftps.c
sftpd.o: sftpd.c
sftp_sub.o: sftp_sub.c
sftpsv_sub.o: sftpsv_sub.c
cli_open.o: cli_open.c

clean:
	rm *.o sftp sftps sftpd