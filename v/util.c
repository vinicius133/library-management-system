#include <stdio.h>
#include "util.h"

void limpar_buffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}