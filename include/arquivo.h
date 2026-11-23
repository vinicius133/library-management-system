#ifndef ARQUIVO_H
#define ARQUIVO_H
#include "vetor.h"

#define TXT "data/livros.txt"
#define BIN "data/livros.data"

int salvar_texto(const char *nome_arquivo, const VetorLivros *v);

#endif