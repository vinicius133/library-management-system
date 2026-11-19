all: main_exec clean

main_exec: main.o util.o vetor.o livro.o
	gcc main.o util.o vetor.o livro.o -o main_exec

main.o: main.c util.h vetor.h livro.h
	gcc -c main.c

util.o: util.c util.h
	gcc -c util.c

vetor.o: vetor.c vetor.h livro.h
	gcc -c vetor.c

livro.o: livro.c livro.h
	gcc -c livro.c

.PHONY: all clean
clean:
	rm -f *.o