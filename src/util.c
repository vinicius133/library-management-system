#include <stdio.h>
#include <string.h>
#include "util.h"

void limpar_buffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);        // descarta os caracteres restantes do buffer até encontrar uma quebra de linha ou o fim da entrada.
}

void limpar_espacos(char *str){
    if (str == 0) return; // proteção contra ponteiro null

    int i = 0; // índice de leitura
    int j = 0; // índice de escrita
    int espaco_anterior = 1;

    while (str[i] != '\0') {
        if (str[i] == ' ' || str[i] == '\t') {
            if (!espaco_anterior) {
                str[j++] = ' ';
                espaco_anterior = 1;
            }
        } else {
            str[j++] = str[i];
            espaco_anterior = 0;
        }
        i++;
    }

    if (j > 0 && str[j - 1] == ' ') {
        j--;
    }

    str[j] = '\0';
}


void ler_string(char *destino, int tamanho) {
    while (1) {
        if (fgets(destino, tamanho, stdin) != NULL) {
            if (strchr(destino, '\n') == NULL) {
                limpar_buffer();
            } else {
                destino[strcspn(destino, "\n")] = '\0';
            }

            limpar_espacos(destino); //já limpa os espaços automaticamente

            if (destino[0] != '\0') {
                return; //  sai do loop só se sobrou algum caractere válido
            }
        }
        printf("Entrada vazia não permitida! Digite novamente: ");
    }
}


int ler_inteiro() {
    int valor;
    while (1) {
        if (scanf("%d", &valor) == 1) {
            limpar_buffer();
            return valor;
        }
        limpar_buffer();
        printf("Entrada inválida! Digite apenas números inteiros: ");
    }
}