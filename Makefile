#checa se tá rodando no windows
ifeq ($(OS),Windows_NT)
	EXEC = bibliotecalms.exe
# função de apagar utilizando powershell para maior versatilidade
	CLEAN = powershell -NoProfile -Command "Remove-Item -Force -ErrorAction SilentlyContinue src/main.o, src/util.o, src/vetor.o, src/livro.o, src/arquivo.o, bibliotecalms.exe"
# em caso de linux, macOS, etc
else
	EXEC = bibliotecalms
	CLEAN_CMD = rm -f $(OBJS) $(EXEC)
endif

# define o compilador gcc
CC = gcc
# ativa avisos rigorosos e aponta a pasta de headers
CFLAGS = -Wall -Wextra -Iinclude

# lista dos arquivos objeto
OBJS = src/main.o src/util.o src/vetor.o src/livro.o src/arquivo.o

all: $(EXEC)

#  junta todos os .o no executável final
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

# compilação individual de cada arquivo objeto
src/main.o: src/main.c include/util.h include/vetor.h include/livro.h include/arquivo.h
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

src/util.o: src/util.c include/util.h
	$(CC) $(CFLAGS) -c src/util.c -o src/util.o

src/vetor.o: src/vetor.c include/vetor.h include/livro.h
	$(CC) $(CFLAGS) -c src/vetor.c -o src/vetor.o

src/livro.o: src/livro.c include/livro.h
	$(CC) $(CFLAGS) -c src/livro.c -o src/livro.o

src/arquivo.o: src/arquivo.c include/arquivo.h include/vetor.h include/livro.h
	$(CC) $(CFLAGS) -c src/arquivo.c -o src/arquivo.o

# declara all e clean como alvos de ação
.PHONY: all clean

#  limpa os arquivos objeto temporários e o executável. o hífen evita que dê erro caso a pasta esteja limpa
clean:
	-$(CLEAN)