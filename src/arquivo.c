#include <stdio.h>
#include "arquivo.h"

int salvar_texto(const VetorLivros *v){
    FILE *fp = fopen(TXT, "w");
    if (fp == NULL) {
        return 0;           //retorna 0 se não conseguir abrir o arquivo para escrever
    }

    for (int i = 0; i < v->tamanho; i++) {
        fprintf(fp, "%d;%s;%s;%d;%s\n", v->livros[i].id, v->livros[i].titulo, v->livros[i].autor, v->livros[i].ano, v->livros[i].categoria);
    }

    fclose(fp);
    return 1;               //retorna 1 se a função for executada com êxito
}