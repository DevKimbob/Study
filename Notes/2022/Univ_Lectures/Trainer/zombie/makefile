all: main.o zombie.o
	g++ -o main main.o zombie.o
	rm -f *.o

main.o: main.cpp
zombie.o: zombie.cpp

clean:
	rm -f main *.o core