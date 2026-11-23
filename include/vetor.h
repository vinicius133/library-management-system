#ifndef VETOR_H
#define VETOR_H

#include "livro.h"

typedef struct { // struct para o vetor dinamico dos livros
    livro *livros; // passei livros como ponteiro porque não sei o tamanho total dele
    int tamanho;
    int capacidade;
} VetorLivros;

// funções para inicializar o vetor e liberar, tudo como ponteiro para a alegria do professor
void inicializar(VetorLivros *v, int capacidade_inicial);
void liberar(VetorLivros *v); // Devolve a memoria ao sistema para evitar vazamentos 

// funções para buscar por id, cadastrar e remover
int buscar_por_id(VetorLivros *v, int id);
int cadastrar_livro(VetorLivros *v, livro l); // usa o buscar_por_id para ver se ja existe o cadastro, se existir ele retorna erro
int remover_livro(VetorLivros *v, int id);

// funções de listagem e busca por texto
void listar_livros(VetorLivros *v);
void buscar_por_titulo(VetorLivros *v, const char *titulo);
void buscar_por_autor(VetorLivros *v, const char *autor);
void buscar_por_categoria(VetorLivros *v, const char *categoria);

// função de ordenação usando Merge Sort
// criterio: 1 = ordenar por titulo (A-Z) | 2 = ordenar por ano (mais antigo pro mais novo)
void ordenar_livros(VetorLivros *v, int criterio);

// função de relatórios gerais e por categoria
void gerar_relatorios(VetorLivros *v);

#endif
