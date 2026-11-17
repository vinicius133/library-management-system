#include <stdio.h>
#include <string.h>

#include "livro.h" 
//Puxa a struct do livro

livro criar_livros(int id, const char *titulo, const char * autor, int ano, const char *categoria ) {//Função que vai criar livros, o noem ja diz ne
//- usei const char pra evitar alterações nos nomes e fiz como ponteiro, apontando para as variaveis que teoricamente vc vai criar
  
  livro novo_livro;

  novo_livro.id = id;
  novo_livro.ano = ano;

  strcpy(novo_livro.titulo, titulo);
  strcpy(novo_livro.autor, autor);
  strcpy(novo_livro.categoria, categoria);

  // Passando o valor das variaveis para ca, e usando da dadiva da string.
  
  return novo_livro;
}
