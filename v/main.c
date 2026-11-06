#include <stdio.h>
#include <windows.h>

int main(){
    SetConsoleOutputCP(CP_UTF8);
    FILE *title;
    int escolha;

    title = fopen("title.txt", "r");
    if (title == NULL){
        printf("ERRO! Não foi possível abrir o arquivo, ele pode não existir ou estar sendo usado por outro programa!\n");
        return 1;
    }                       //abertura e checagem de arquivo

    do{
        fprintf("");

        switch (escolha){
        case 1:             //Cadastrar livro
            
            break;

        case 2:             //Listar todos os livros

            break;

        case 3:             //Buscar livros

            break;

        case 4:              //Remover livros por ID

            break;

        case 5:             //Salvar dados em arquivo texto

            break;

        case 6:             //Salvar dados em arquivo binário

            break;

        case 7:             //Carregar dados de arquivo ao iniciar

            break;

        case 8:             //Gerar relatórios

            break;

        case 9:             //Sair
            return 0;
        
        default:
            printf(u8"Opção inválida!\n");
            break;
        }
    } while (1 != 0);
    

    

    fclose(title);
    return 0;
}