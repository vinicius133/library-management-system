#ifndef ARQUIVO_H
#define ARQUIVO_H
#include "vetor.h"

#define TXT "data/livros.txt"       //seta TXT como um alias para o caminho pro arquivo de texto
#define BIN "data/livros.data"         //seta BIN como um alias para o caminho pro arquivo binário

int salvar_texto(const VetorLivros *v);
int carregar_texto(VetorLivros *v);

#endif