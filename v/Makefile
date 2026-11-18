main: main_obj rm_main

main_obj: util.o
	gcc main.c util.o -o main_exec

util.o:
	gcc -c util.c

rm_main:
	rm util.o