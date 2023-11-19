//este arquivo contem o protótipo das funções, também conhecido como cabeçalho das funções
#ifndef LISTTOOLS_H //Se LISTTOOLS_H não estiver definido (o que significa que é a primeira vez que o arquivo de cabeçalho é incluído)
#define LISTTOOLS_H //define o símbolo LISTTOOLS_H, indicando que o arquivo de cabeçalho foi incluído.
#include <stdio.h>
#include <stdlib.h>

struct NodoPilha{
    int vertice;
    struct NodoPilha *prox;
};

struct Pilha{
    struct NodoPilha *topo;
};


void inicializaPilha(struct Pilha **head);
int pop(struct Pilha **head);
void push(struct Pilha **head, int vertice);


#endif