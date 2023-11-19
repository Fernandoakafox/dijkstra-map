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

int pop(struct Pilha **head){
    //se a pilha estiver vazia
    if((*head)->topo == NULL){
        return -1;
    }
    struct NodoPilha *aux;
    int vertice;
    // se a pilha tiver 2 nodos
    if((*head)->topo->prox != NULL){
        aux = (*head)->topo;                 // aux aponta para o nodo no topo
        (*head)->topo = (*head)->topo->prox; // Diminui topo "pop"
        vertice = aux->vertice;
        free(aux);                           // Libera espaço de memoria
        return vertice;
    // senão a pilha tem somente 1 nodo
    }else{
        aux = (*head)->topo;                 // aux aponta para o nodo no topo
        (*head)->topo = NULL;                // topo aponta para NULL
        vertice = aux->vertice;              
        free(aux);                           // Libera espaço de memoria
        return vertice;
    }
}
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