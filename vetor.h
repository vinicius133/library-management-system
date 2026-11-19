#ifndef VETOR_H
#define VETOR_H

#include "livro.h"

typedef struct { //struct para o vetor dinamico dos livros
    livro *livros; //passei livros como ponteiro porque não sei o tamanho total dele
    int tamanho;
    int capacidade;
} VetorLivros;

// funções que para inicializar o vetor e liberar, tudo como ponteiro para a alegria do profeesor
void inicializar(VetorLivros *v, int capacidade_inicial);
void liberar(VetorLivros *v); //Devolve a memoria ao sistema para evitar vazamentos 

//funções para buscar por id e cadastrar
int buscar_por_id(VetorLivros *v, int id);
int cadastrar_livro(VetorLivros *v, livro l); //usa o buscar_por_id para ver se ja existe o cadastro, se existir ele retorna erro

#endif
