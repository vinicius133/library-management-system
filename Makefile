CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

OBJS = src/main.o src/util.o src/vetor.o src/livro.o
EXEC = lms

all: $(EXEC) clean

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

src/main.o: src/main.c include/util.h include/vetor.h include/livro.h
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

src/util.o: src/util.c include/util.h
	$(CC) $(CFLAGS) -c src/util.c -o src/util.o

src/vetor.o: src/vetor.c include/vetor.h include/livro.h
	$(CC) $(CFLAGS) -c src/vetor.c -o src/vetor.o

src/livro.o: src/livro.c include/livro.h
	$(CC) $(CFLAGS) -c src/livro.c -o src/livro.o

.PHONY: all clean
clean:
	rm -f src/*.o