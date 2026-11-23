#include <stdio.h>
#include <stdlib.h>
#include <string.h> // para strstr e strcmp nas buscas, no merge sort e no relatório
#include <ctype.h>  // para tolower (deixar a busca sem frescura de maiuscula/minuscula)
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
        
        v->livros = temp;                // Atualiza o ponteiro para o novo bloco
        v->capacidade = nova_capacidade; // Atualiza o novo limite
    }

    // Adiciona o livro na posição livre
    v->livros[v->tamanho] = l;
    v->tamanho++; // Incrementa o tamanho para o próximo cadastro
    
    return 1; // Retorna 1 se não explodir
}

// Remove um livro do vetor pelo ID e reorganiza os elementos
int remover_livro(VetorLivros *v, int id) {
    int index = buscar_por_id(v, id); // Busca o índice do livro
    
    if (index == -1) {
        return 0; // Livro não encontrado
    }
    
    // Desloca todos os elementos à direita do índice removido para a esquerda pra não deixar buraco
    for (int i = index; i < v->tamanho - 1; i++) {
        v->livros[i] = v->livros[i + 1];
    }
    
    v->tamanho--; // Decrementa o tamanho do vetor
    return 1; // Sucesso
}



// Função auxiliar (só existe aqui dentro) pra comparar texto ignorando maiúscula/minúscula
static int contem_texto(const char *texto, const char *busca) {
    char texto_min[100];
    char busca_min[100];
    int i;

    // joga tudo pra minúsculo pra comparar de boa
    for (i = 0; texto[i] != '\0' && i < 99; i++) {
        texto_min[i] = tolower((unsigned char)texto[i]);
    }
    texto_min[i] = '\0';

    for (i = 0; busca[i] != '\0' && i < 99; i++) {
        busca_min[i] = tolower((unsigned char)busca[i]);
    }
    busca_min[i] = '\0';

    // strstr procura se 'busca_min' aparece em qualquer pedaço de 'texto_min'
    return strstr(texto_min, busca_min) != NULL;
}

// Lista todos os livros cadastrados no vetor
void listar_livros(VetorLivros *v) {
    if (v->tamanho == 0) {
        printf("\nNenhum livro cadastrado ainda.\n");
        return;
    }

    for (int i = 0; i < v->tamanho; i++) {
        imprimir_livro(v->livros[i]);
        printf("\n------------------------\n");
    }
}

// Busca livros por pedaço do título (substring)
void buscar_por_titulo(VetorLivros *v, const char *titulo) {
    int achou = 0;
    for (int i = 0; i < v->tamanho; i++) {
        if (contem_texto(v->livros[i].titulo, titulo)) {
            imprimir_livro(v->livros[i]);
            printf("\n------------------------\n");
            achou = 1;
        }
    }
    if (!achou) {
        printf("\nNenhum livro encontrado com o título \"%s\".\n", titulo);
    }
}

// Busca livros pelo nome do autor
void buscar_por_autor(VetorLivros *v, const char *autor) {
    int achou = 0;
    for (int i = 0; i < v->tamanho; i++) {
        if (contem_texto(v->livros[i].autor, autor)) {
            imprimir_livro(v->livros[i]);
            printf("\n------------------------\n");
            achou = 1;
        }
    }
    if (!achou) {
        printf("\nNenhum livro encontrado do autor \"%s\".\n", autor);
    }
}

// Busca livros pela categoria
void buscar_por_categoria(VetorLivros *v, const char *categoria) {
    int achou = 0;
    for (int i = 0; i < v->tamanho; i++) {
        if (contem_texto(v->livros[i].categoria, categoria)) {
            imprimir_livro(v->livros[i]);
            printf("\n------------------------\n");
            achou = 1;
        }
    }
    if (!achou) {
        printf("\nNenhum livro encontrado na categoria \"%s\".\n", categoria);
    }
}


// Junta as duas metades já ordenadas de volta no vetor principal
static void merge(livro *arr, int esq, int meio, int dir, int criterio) {
    int n1 = meio - esq + 1; // tamanho da metade esquerda
    int n2 = dir - meio;     // tamanho da metade direita

    // aloca dois vetores temporários na Heap pra não perder os dados na hora de sobrescrever
    livro *E = (livro *)malloc(n1 * sizeof(livro));
    livro *D = (livro *)malloc(n2 * sizeof(livro));

    if (E == NULL || D == NULL) {
        perror("Erro ao alocar memória no merge sort");
        free(E);
        free(D);
        return;
    }

    // copia os livros pros vetores temporários
    for (int i = 0; i < n1; i++) E[i] = arr[esq + i];
    for (int j = 0; j < n2; j++) D[j] = arr[meio + 1 + j];

    int i = 0, j = 0, k = esq;

    // vai comparando um da esquerda com um da direita e jogando o menor pro vetor original
    while (i < n1 && j < n2) {
        int esquerda_vem_primeiro = 0;

        if (criterio == 1) {
            // ordena por título (A-Z) usando strcmp
            if (strcmp(E[i].titulo, D[j].titulo) <= 0) {
                esquerda_vem_primeiro = 1;
            }
        } else {
            // ordena por ano (crescente)
            if (E[i].ano <= D[j].ano) {
                esquerda_vem_primeiro = 1;
            }
        }

        if (esquerda_vem_primeiro) {
            arr[k] = E[i];
            i++;
        } else {
            arr[k] = D[j];
            j++;
        }
        k++;
    }

    // se sobrou algum livro na esquerda ou na direita, só joga o resto no final
    while (i < n1) {
        arr[k] = E[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = D[j];
        j++;
        k++;
    }

    // libera os vetores temporários pra não vazar memória
    free(E);
    free(D);
}

// Esqueleto recursivo que fica quebrando o vetor no meio até sobrar 1 elemento
static void merge_sort_rec(livro *arr, int esq, int dir, int criterio) {
    if (esq < dir) {
        int meio = esq + (dir - esq) / 2; // acha o meio sem risco de estourar o int

        merge_sort_rec(arr, esq, meio, criterio);     // quebra a metade esquerda
        merge_sort_rec(arr, meio + 1, dir, criterio); // quebra a metade direita

        merge(arr, esq, meio, dir, criterio);         // junta tudo ordenado
    }
}

// Função pública que o main.c vai chamar pra ordenar
void ordenar_livros(VetorLivros *v, int criterio) {
    if (v->tamanho > 1) {
        merge_sort_rec(v->livros, 0, v->tamanho - 1, criterio);
    }
}

// RELATÓRIOS 
void gerar_relatorios(VetorLivros *v) {
    printf("\n========== RELATÓRIO DO ACERVO ==========\n");

    if (v->tamanho == 0) {
        printf("Nenhum livro cadastrado para gerar relatório.\n");
        printf("=========================================\n");
        return;
    }

    // 1. Quantidade total de livros
    printf("Total de livros cadastrados: %d\n", v->tamanho);

    // 2. Livro mais antigo e mais recente (varredura linear)
    int idx_antigo = 0;
    int idx_recente = 0;

    for (int i = 1; i < v->tamanho; i++) {
        if (v->livros[i].ano < v->livros[idx_antigo].ano) {
            idx_antigo = i;
        }
        if (v->livros[i].ano > v->livros[idx_recente].ano) {
            idx_recente = i;
        }
    }

    printf("Livro mais antigo: \"%s\" (%d)\n", v->livros[idx_antigo].titulo, v->livros[idx_antigo].ano);
    printf("Livro mais recente: \"%s\" (%d)\n", v->livros[idx_recente].titulo, v->livros[idx_recente].ano);

    // 3. Quantidade por categoria (contagem dinâmica sem repetir categoria)
    printf("\nQuantidade por categoria:\n");
    int *contado = (int *)calloc(v->tamanho, sizeof(int)); // marca quais posições já foram contadas
    if (contado == NULL) {
        perror("Erro de memória no relatório");
        return;
    }

    for (int i = 0; i < v->tamanho; i++) {
        if (contado[i] == 1) continue; // já contamos essa categoria antes

        int qtd = 1;
        for (int j = i + 1; j < v->tamanho; j++) {
            if (strcmp(v->livros[i].categoria, v->livros[j].categoria) == 0) {
                qtd++;
                contado[j] = 1; // marca como já contado pra não duplicar no print
            }
        }
        printf("  - %s: %d livro(s)\n", v->livros[i].categoria, qtd);
    }

    free(contado); // libera o vetor auxiliar pra não vazar memória
    printf("=========================================\n");
}
