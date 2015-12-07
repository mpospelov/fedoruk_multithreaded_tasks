CC = g++

all: clean main

main: main.o machine.o conveyor.o printer.o
	$(CC) main.o machine.o conveyor.o printer.o -o main -g

main.o:
	$(CC) -c main.cpp

machine.o:
	$(CC) src/machine.cpp -c -g

conveyor.o:
	$(CC) src/conveyor.cpp -c -g

printer.o:
	$(CC) src/printer.cpp -c -g
clean:
	rm -rf *.o main
