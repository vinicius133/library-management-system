all: main_exec clean

main_exec: main.o util.o
	gcc main.o util.o -o main_exec

main.o: main.c
	gcc -c main.c

util.o: util.c
	gcc -c util.c

.PHONY: all clean
clean:
	rm -f *.o