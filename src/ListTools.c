#include "../include/ListTools.h"
#include <stdio.h>


/************************************************* 
 * criaPilha                                     *
 * objetivo: inicializa pilha                    *
 * entrada : cabeça da pilha                     *
 * saida   :                                     *
 *************************************************/

void inicializaPilha(struct Pilha **head){
    *head = (struct Pilha*) malloc(sizeof(struct Pilha));
    (*head)->topo = NULL;
}

void pop(){}
/************************************************* 
 * push                                          *
 * objetivo: inclui nodo na pilha                *
 * entrada : cabeça da pilha e vertice           *
 * saida   :                                     *
 *************************************************/
void push(struct Pilha **head, int vertice){
    struct NodoPilha *no = (struct NodoPilha*) malloc(sizeof(struct NodoPilha));
    no->vertice = vertice;
    if((*head)->topo == NULL){
        no->prox = NULL;
    }else{
        no->prox = (*head)->topo;
        (*head)->topo = no;
    }
}