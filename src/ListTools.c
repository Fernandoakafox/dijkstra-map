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
/**************************************************************** 
 * pop                                                          *
 * objetivo: remover um nodo da pilha                           *
 * entrada : cabeça da pilha                                    *
 * saida   : inteiro do campo vertice do nodo removido da pilha *
 ****************************************************************/
int pop(struct Pilha **head){
    //se a pilha estiver vazia
    if((*head)->topo == NULL) return -1;
    struct NodoPilha *aux = (*head)->topo;
    
    int vertice = aux->vertice;
    
    if((*head)->topo->prox != NULL) (*head)->topo = (*head)->topo->prox;                                             
    else (*head)->topo = NULL;                
    
    free(aux); 
    return vertice;
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
        (*head)->topo = no;
    }else{
        no->prox = (*head)->topo;
        (*head)->topo = no;
    }
}