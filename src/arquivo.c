#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"
#include "livro.h"
#include "vetor.h"

int salvar_texto(const VetorLivros *v){         //usa const 
    FILE *fp = fopen(TXT, "w");     //abre o arquivo de texto usando o alias setado no .h em modo de escrita
    if (fp == NULL) {
        return 0;           //retorna 0 se não conseguir abrir o arquivo para escrever
    }

    for (int i = 0; i < v->tamanho; i++) {          //percorre todos os livros da biblioteca
        fprintf(fp, "%d;%s;%s;%d;%s\n", v->livros[i].id, v->livros[i].titulo, v->livros[i].autor, v->livros[i].ano, v->livros[i].categoria);        //grava na forma ID;Titulo;Autor;Ano;Categoria no arquivo
    }

    fclose(fp);
    return 1;               //retorna 1 se a função for executada com êxito
}


int carregar_texto(VetorLivros *v){ 
    FILE *fp = fopen(TXT, "r");             ////abre o arquivo de texto usando o alias setado no .h em modo de leitura
    if (fp == NULL) {
        return 0;           //retorna 0 se não conseguir abrir o arquivo para ler
    }
    char linha[512];            //buffer temporário pra cabera linha do arquivo q contém todos os dados de um livro

    while (fgets(linha, sizeof(linha), fp) != NULL) {       //lê uma linha inteira do arquivo até chegar no EOF
        linha[strcspn(linha, "\r\n")] = '\0';           //remove o \n e o \r se o arquivo tiver sido salvo no windows

        if (linha[0] == '\0') {
            continue;                                     //ignora linhas vazias e continua lendo o resto
        }            
        
        char *token_id        = strtok(linha, ";");
        char *token_titulo    = strtok(NULL, ";");
        char *token_autor     = strtok(NULL, ";");          //usa o strtok pra separar a linha em tokens divididos pelo ; e recebe o enderço de cada um colocando nos ponteiros
        char *token_ano       = strtok(NULL, ";");          //o null sere pra dizer ao strtok começar de onde ele parou anteriormente
        char *token_categoria = strtok(NULL, ";");

        if (token_id != NULL && token_titulo != NULL && token_autor != NULL && token_ano != NULL && token_categoria != NULL) {      //garante q os 5 campos existam

            int id  = atoi(token_id);
            int ano = atoi(token_ano);      //conversão de texto para inteiro usando atoi pq tudo puxado de um txt é texto

            livro novo = criar_livros(id, token_titulo, token_autor, ano, token_categoria);         //cria um novo livro com as informações adquiridas
            cadastrar_livro(v, novo);

        }
    }

    fclose(fp);
    return 1;           //retorna 1 se a função for executada com êxito
}