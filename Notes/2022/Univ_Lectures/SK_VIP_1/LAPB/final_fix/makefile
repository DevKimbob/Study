all:
	make lb_client
	make lb_server

lb_client: lb_cli.o
	cc -o lb_client lb_cli.o

lb_server: lb_ser.o
	cc -o lb_server lb_ser.o
	
lb_cli.o: lb_cli.c
lb_ser.o: lb_ser.c

clean:
	rm -f *.o lb_client lb_server
