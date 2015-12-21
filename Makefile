CC = g++

all: clean main

main: main.o machine.o conveyor.o printer.o
	$(CC) -pthread -std=c++0x main.o machine.o conveyor.o printer.o -o main -g

main.o:
	$(CC) -pthread -std=c++0x -c main.cpp

machine.o:
	$(CC) -pthread -std=c++0x src/machine.cpp -c -g

conveyor.o:
	$(CC) -pthread -std=c++0x src/conveyor.cpp -c -g

printer.o:
	$(CC) -pthread -std=c++0x src/printer.cpp -c -g
clean:
	rm -rf *.o main
