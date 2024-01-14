# make 명령 사용하기 (3)
# Makefile

CC=gcc
CFLAGS=
OBJS=03_main.o 03_addnum.o
LIBS=
all : add.out

add.out : $(OBJS)
	$(CC) $(CFLAGS) -o add.out $(OBJS) $(LIBS)

03.main.o : 03_main.c
	$(CC) $(CFLAGS) -c 03_main.c

03.addnum.o : 03_addnum.c
	$(CC) $(CFLAGS) -c 03_addnum.c

clean:
	rm -f $(OBJS) add.out *.o core
