CC  = gcc
LIBS = -ljson-c

all:
	make greedy_array
	make greedy_pque
	make dynamic

greedy_array:
	$(CC) -o greedy_array greedy_array.c parse.c $(LIBS)

greedy_pque:
	$(CC) -o greedy_pque greedy_pque.c parse.c heap.c $(LIBS)

dynamic:
	$(CC) -o dynamic dynamic.c parse.c $(LIBS)

clean:
	rm -f *.o greedy_array greedy_pque dynamic core
