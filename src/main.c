#include <stdio.h>
#include <string.h>
#include <errno.h>
#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN // evita headers pesados e conflitos de macros
    #include <windows.h>
#endif
#include <locale.h>
#include "util.h"
#include "vetor.h"
#include "livro.h"

int main(){
    #ifdef _WIN32
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);

        if (setlocale(LC_ALL, ".UTF-8") == NULL) {
            printf("Erro ao configurar UTF-8.\n");
        }
    #else
        if (setlocale(LC_ALL, "") == NULL) {
            printf("Erro ao configurar UTF-8.\n");
        }
    #endif      //tentativa de aplicação de UTF-8 para windows e linux

    FILE *title;
    int escolha;
    int ch, executando = 1;

    VetorLivros biblioteca;
    inicializar(&biblioteca, 10);       //inicialização do vetor de livros

    
    // 1. Login
    // 2. Inicialização do vetor (malloc)
    // 3. Carregamento automático do arquivo inicial
    
    do{
        limpar_tela();
        title = fopen("data/title.txt", "r");
        if (title == NULL){
            printf("Aviso: Não foi possível carregar title.txt (%s)\n", strerror(errno));
        } else{                             //abertura e checagem do arquivo de título
            while ((ch = fgetc(title)) != EOF ){
                    printf("%c", ch);
                }                           //printa o título do programa presente no title.txt
            fclose(title);
        }

        printf("\n╔══════════════════════════════════════════════════════════════════════╗\n");
        printf("║                       SISTEMA DE BIBLIOTECA (LMS)                    ║\n");
        printf("╠══════════════════════════════════════════════════════════════════════╣\n");
        printf("║  [1] Cadastrar livro              ║  [2] Listar todos os livros      ║\n");
        printf("║  [3] Buscar livros                ║  [4] Remover livro por ID        ║\n");
        printf("║  [5] Salvar em arquivo texto      ║  [6] Salvar em arquivo binário   ║\n");
        printf("║  [7] Carregar dados ao iniciar    ║  [8] Gerar relatórios            ║\n");
        printf("║  [9] Sair                         ║                                  ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════╝\n");
        printf("\nEscolha uma opção: \n");

        escolha = ler_inteiro();

        switch (escolha){
            case 1:
                // Cadastrar livro
                limpar_tela();
                int id_cadastro = 0, ano = 0;
                char titulo[100], autor[100], categoria[50];    //informações necessárias do struct dos livros

                printf("\n--- Cadastrar Livro ---\n");
                printf("ID: ");
                id_cadastro = ler_inteiro();

                printf("Título: ");
                ler_string(titulo, 100);

                printf("Autor: ");
                ler_string(autor, 100);

                printf("Ano: ");
                ano = ler_inteiro();

                printf("Categoria: ");
                ler_string(categoria, 50);

                livro novo = criar_livros(id_cadastro, titulo, autor, ano, categoria);       //montagem do struct do livro com as info adquiridas

                if (cadastrar_livro(&biblioteca, novo) == 1){
                    printf("\nLivro cadastrado com sucesso!\n");
                }
                
                pausar_tela();
                break;

            case 2:
                // Listar livros
                limpar_tela();
                int escolha_ordenar = 0;
                printf("1) Ordenar por título\n2) Ordenar por ano\n");
                escolha_ordenar = ler_inteiro();

                if (escolha_ordenar != 1 && escolha_ordenar != 2) {
                    printf("Opção inválida! Retornando ao menu.\n");
                    limpar_tela();
                    break;
                }

                if (biblioteca.tamanho == 0){
                    printf("Nenhum livro cadastrado.\n");       //checagem de biblioteca vazia
                } else{
                    ordenar_livros(&biblioteca, escolha_ordenar);       //ordenação usando a função e o tipo de ordenação escolhido
                    for (int i = 0; i < biblioteca.tamanho; i++){
                        imprimir_livro(biblioteca.livros[i]);           //impressão dos livros já ordenados
                        printf("\n------------------------\n");
                    }
                }

                pausar_tela();
                break;

            case 3:
                // Buscar livros
                limpar_tela();
                int escolha_buscar = 0;
                char termo[100];
                printf("1) Buscar por título (substring)\n2) Buscar por autor\n3) Buscar por categoria\n");
                escolha_buscar = ler_inteiro();         //escolha de em qual ordem mostrar os livros

                

                if(escolha_buscar == 1){
                    printf("Digite o título da obra: ");
                    ler_string(termo, 100);
                    buscar_por_titulo(&biblioteca, termo);

                } else if(escolha_buscar == 2){
                    printf("Digite o autor da obra: ");
                    ler_string(termo, 100);
                    buscar_por_autor(&biblioteca, termo);

                } else if(escolha_buscar == 3){
                    printf("Digite a categoria da obra: ");
                    ler_string(termo, 50);
                    buscar_por_categoria(&biblioteca, termo);
                    
                } else{
                    printf("Opção inválida! Retornando ao menu.\n");
                }

                pausar_tela();
                break;

            case 4:
                // Remover livro
                limpar_tela();
                int id_remover = 0;
                printf("Digite o ID do livro que será removido: ");
                id_remover = ler_inteiro();

                if(remover_livro(&biblioteca, id_remover) == 1){
                    printf("\nLivro removido com sucesso!\n");
                }

                pausar_tela();
                break;

            case 5:
                // Salvar em texto
                limpar_tela();

                pausar_tela();

                break;

            case 6:
                // Salvar em binario
                limpar_tela();

                pausar_tela();
                break;

            case 7:
                // Carregar dados
                limpar_tela();

                pausar_tela();
                break;

            case 8:
                // Relatorios
                limpar_tela();
                gerar_relatorios(&biblioteca);

                pausar_tela();
                break;

            case 9:
                limpar_tela();  
                printf("\nDeseja salvar antes de encerrar?\n1 - Sim\n2 - Não\n");
                escolha = ler_inteiro();

                if (escolha == 1){
                    printf("\n1 - Salvar dados em arquivo texto\n2 - Salvar dados em arquivo binário\n");
                    escolha = ler_inteiro();

                    if (escolha == 1) {
                        //função
                        printf("Salvando em arquivo de texto\n");
                        executando = 0;

                    } else if (escolha == 2) {
                        //função
                        printf("Salvando em arquivo binário\n");
                        executando = 0;
                    } else {
                        printf("Opção inválida! Retornando ao menu.\n");
                        pausar_tela();
                    }

                } else if(escolha == 2){
                    executando = 0;
                } else {
                    printf("Opção inválida! Retornando ao menu.\n");
                    pausar_tela();
                }
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
                pausar_tela();
                break;
        }
    } while (executando != 0);

    liberar(&biblioteca);
    printf("\nSistema encerrado.\n");
    
    return 0;
}
