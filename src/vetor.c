#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"

// Prepara o vetor, alocando a memória inicial
void inicializar(VetorLivros *v, int capacidade_inicial) {
    // malloc reserva um bloco de memória para guardar os livros
    v->livros = (livro *)malloc(capacidade_inicial * sizeof(livro));
    
    // Se malloc der NULL, significa que o computador ficou sem memória
    if (v->livros == NULL) {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE); // Encerra o programa se der pau
    }
    
    v->tamanho = 0;           
    v->capacidade = capacidade_inicial; 
}

// Libera a memória pra nao dar pau
void liberar(VetorLivros *v) {
    free(v->livros);    // Devolve a memória para o sistema operacional
    v->livros = NULL;   // Remove o endereço para não tentar acessar memória liberada
    v->tamanho = 0;     // Reseta a contagem
    v->capacidade = 0;  // Reseta o limite
}

// Procura um livro pelo ID e fala onde ele está
int buscar_por_id(VetorLivros *v, int id) {
    // Percorre todos os livros que já foram cadastrados
    for (int i = 0; i < v->tamanho; i++) {
        // Se encontrar o ID que estamos procurando
        if (v->livros[i].id == id) {
            return i; // Retorna a posição do livro no vetor
        }
    }
    return -1; // Retorna -1 se percorreu tudo e não achou nada
}

// Adiciona um novo livro ao vetor e se precisar aumenta ele
int cadastrar_livro(VetorLivros *v, livro l) {
    // verifica se ja tem um id ingual
    if (buscar_por_id(v, l.id) != -1) {
        printf("Erro: Já existe um livro cadastrado com o ID %d.\n", l.id);
        return 0; // Retorna 0 avisando que não deu para cadastrar
    }

    // Se o vetor estiver cheio ele dobra a capacidade
    if (v->tamanho == v->capacidade) {
        int nova_capacidade = v->capacidade * 2; // Dobramos o espaço para eficiência
        
        // realloc tenta aumentar o bloco de memória atual
        livro *temp = (livro *)realloc(v->livros, nova_capacidade * sizeof(livro));
        
        if (temp == NULL) {
            perror("Erro ao realocar memória");
            return 0; // Falha na realocação
        }
        
        v->livros = temp;           // Atualiza o ponteiro para o novo bloco
        v->capacidade = nova_capacidade; // Atualiza o novo limite
    }

    // Adiciona o livro na posição livre
    v->livros[v->tamanho] = l;
    v->tamanho++; // Incrementa o tamanho para o próximo cadastro
    
    return 1; // Retorna 1 se não explodir
}
