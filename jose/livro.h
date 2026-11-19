#ifndef LIVRO_H	

#define LIVRO_H

//struct base para as infos dos livros

typedef struct {

	int id ;
	char titulo[100];
	char autor[100];
	int ano ;
	char categoria[50];

} livro;

livro criar_livros(int id, const char *titulo, const char * autor, int ano, const char *categoria );//função para criar livros de acordo com o padrao do professor


#endif
