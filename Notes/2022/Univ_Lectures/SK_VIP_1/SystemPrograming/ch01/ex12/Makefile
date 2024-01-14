# Makefile

CC=gcc
CFLAGS=
OBJS=ex12_main.o ex12_subnum.o
LIBS=
all : sub.out

sub.out : $(OBJS)
	$(CC) $(CFLAGS) -o sub.out $(OBJS) $(LIBS)

03.main.o : ex12_main.c
	$(CC) $(CFLAGS) -c ex12_main.c

03.addnum.o : ex12_subnum.c
	$(CC) $(CFLAGS) -c ex12_subnum.c

clean:
	rm -f $(OBJS) sub.out *.o core
