#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <windows.h>
#include "util.h"

int main(){
    SetConsoleOutputCP(CP_UTF8);
    FILE *title;
    char escolha, escolha_salvar;
    int ch, executando = 1;

    // VetorLivros biblioteca = criar_vetor(10);  ??

    title = fopen("title.txt", "r");
    if (title == NULL){
        printf("Aviso: Nao foi possivel carregar title.txt (%s)\n\n", strerror(errno));
    }                       //abertura e checagem de arquivo
    while ((ch = fgetc(title)) != EOF ){
            printf("%c", ch);
        }                   //printa o título do programa presente no title.txt
    fclose(title);


    do{
        printf("\n╔══════════════════════════════════════════════╗\n");
        printf("║           SISTEMA DE BIBLIOTECA              ║\n");
        printf("╠══════════════════════════════════════════════╣\n");
        printf("║  [1] Cadastrar livro                         ║\n");
        printf("║  [2] Listar todos os livros                  ║\n");
        printf("║  [3] Buscar livros                           ║\n");
        printf("║  [4] Remover livro por ID                    ║\n");
        printf("║  [5] Salvar em arquivo texto                 ║\n");
        printf("║  [6] Salvar em arquivo binario               ║\n");
        printf("║  [7] Carregar dados de arquivos ao iniciar   ║\n");
        printf("║  [8] Gerar relatorios                        ║\n");
        printf("║  [9] Sair                                    ║\n");
        printf("╠══════════════════════════════════════════════╣\n");
        printf("\nEscolha uma opcao: \n");

        scanf(" %c", &escolha);
        limpar_buffer();

        switch (escolha){
            case '1':
                // Cadastrar livro
                break;

            case '2':
                // Listar livros
                break;

            case '3':
                // Buscar livros
                break;

            case '4':
                // Remover livro
                break;

            case '5':
                // Salvar em texto
                break;

            case '6':
                // Salvar em binario
                break;

            case '7':
                // Carregar dados
                break;

            case '8':
                // Relatorios
                break;

            case '9':
                printf("\nDeseja salvar antes de encerrar?\n1 - Sim\n2 - Não\n");
                scanf(" %c", &escolha_salvar);
                if (escolha_salvar == '1'){
                    printf("\n1 - Salvar dados em arquivo texto\n2 - Salvar dados em arquivo binário\n");
                    scanf(" %c", &escolha);

                    if (escolha == '1') {
                        //função
                        printf("Salvando em arquivo de texto\n");
                        return 0;
                    } else if (escolha == '2') {
                        //função
                        printf("Salvando em arquivo binario\n");
                        return 0;
                    }
                } else if(escolha_salvar == '2'){
                    return 0;
                } else{
                    printf("Opcao invalida! Tente novamente.\n");
                }

            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    } while (escolha != '9');
    
    return 0;
}
