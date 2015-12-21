CC = g++

all: clean main

main: main.o machine.o conveyor.o printer.o
	$(CC) -pthread main.o machine.o conveyor.o printer.o -o main -g

main.o:
	$(CC) -pthread -c main.cpp

machine.o:
	$(CC) -pthread src/machine.cpp -c -g

conveyor.o:
	$(CC) -pthread src/conveyor.cpp -c -g

printer.o:
	$(CC) -pthread src/printer.cpp -c -g
clean:
	rm -rf *.o main
