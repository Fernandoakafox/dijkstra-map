#include <stdio.h>
#include <stdlib.h>
#include "../include/GraphTools.h" // Biblioteca do desenvolvedor, para manipulação de grafos
#include "../include/Graphic.h"    // Biblioteca do desenvolvedor, para manipulação gráfica
#include "../include/ListTools.h"

/*
    A -- C
    |    |
    |    D - E
    B --/  

    Rota mais curta A-E: A-C-D-E
*/

void erroRota() {
    printf("erro na rota"); 
    exit(EXIT_FAILURE);
}

void diskjraTeste1() {
    struct GRAFO* grafo = criaGrafo(5);
    adicionarVertice(grafo, 0, "A", 0, 0);
    adicionarVertice(grafo, 1, "B", 0, 2);
    adicionarVertice(grafo, 2, "C", 1, 0);
    adicionarVertice(grafo, 3, "D", 1, 1);
    adicionarVertice(grafo, 4, "E", 2, 1);
    
    adicionarAresta(grafo, 0, 1);
    adicionarAresta(grafo, 0, 2);
    adicionarAresta(grafo, 1, 3);
    adicionarAresta(grafo, 2, 3);
    adicionarAresta(grafo, 3, 4);

    struct Pilha* rota = dijkstra(grafo, 0, 4);
    int v = -1;          
    
    // Rota deve ser 0(A), 2(C), 3(D), 4(E)
    v = pop(&rota);
    if (v != 0) erroRota();
    v = pop(&rota);
    if (v != 2) erroRota();
    v = pop(&rota);
    if (v != 3) erroRota();
    v = pop(&rota);
    if (v != 4) erroRota();
    v = pop(&rota);
    if (v != -1) erroRota();
}


int main() {
    diskjraTeste1();
}
