all:
	make linkedlist

linkedlist: llmain.o list.o
	cc -o linkedlist llmain.o list.o

llmain.o: llmain.c
linked_list.o: list.c

clean:
	rm -f *.o linkedlist