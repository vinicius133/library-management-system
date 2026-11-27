ifeq ($(OS),Windows_NT)
	# checa se está rodando no Windows e usa o comando del
	RM = del /Q /F
	# Troca barras normais '/' por contrabarras '\' para evitar erro de sintaxe no Windows
	FIX_PATH = $(subst /,\,$1)
	# Define o nome do executável com extensão .exe
	EXEC = lms.exe
else
	# Em sistemas Unix (Linux/macOS), usa 'rm -f' e mantém os caminhos originais
	RM = rm -f
	FIX_PATH = $1
	EXEC = lms
endif

# Variáveis de compilação
# Define o compilador C
CC = gcc
# Ativa avisos rigorosos (-Wall -Wextra) e aponta a pasta de headers (-Iinclude)
CFLAGS = -Wall -Wextra -Iinclude

# Lista de todos os arquivos-objeto (.o) que compõem o sistema
OBJS = src/main.o src/util.o src/vetor.o src/livro.o src/arquivo.o

# Regra padrão executada ao rodar apenas 'make'
all: $(EXEC)

# Etapa de ligação (linking): junta todos os .o no executável final
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

# Regras de compilação individual de cada módulo (.c -> .o)
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

# Declara 'all' e 'clean' como alvos de ação (não são nomes de arquivos reais)
.PHONY: all clean

# Limpa os arquivos-objeto temporários e o executável gerado
clean:
	$(RM) $(call FIX_PATH,src/*.o) $(EXEC)