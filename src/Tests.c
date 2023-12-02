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
    adicionarVertice(grafo, 0, "A0", 0, 0);
    adicionarVertice(grafo, 1, "B0", 0, 2);
    adicionarVertice(grafo, 2, "C0", 1, 0);
    adicionarVertice(grafo, 3, "D0", 1, 1);
    adicionarVertice(grafo, 4, "E0", 2, 1);
    
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

void testeRotaOnibusPara18() {

    /** Função de teste para validar a resposta do programa
    Caso de teste:
    Realizar um percurso entre o Ponto de Ônibus e o o Bloco 18

    INPUTS :  grafo, pontoDePartida, pontoDeChegada
    OUTPUTS : o trajeto entre Vertices que significam o melhor trajeto

    Caso o teste não condiza com o caminho correto, irá printar no terminal 
    Teste Falhou
    
    **/

    struct GRAFO* grafo;
    int vetorAtual;

    importaGrafo(&grafo);
    struct Pilha* rota = dijkstra(grafo, 35, 1);

    // Rota 35 18 17 15 34 16 50 48 33 38 4 45 44 1 
    vetorAtual = pop(&rota);
    if (vetorAtual != 35) {
        printf("\n Teste  Falhou \n\n");
        return;
    }

    vetorAtual = pop(&rota);
    if (vetorAtual != 18) {
        printf("\n Teste  Falhou \n\n");
        return;
    }


    vetorAtual = pop(&rota);
    if (vetorAtual != 17) {
        printf("\n Teste  Falhou \n\n");
        return;
    }


    vetorAtual = pop(&rota);
    if (vetorAtual != 15) {
        printf("\n Teste  Falhou \n\n");
        return;
    }

    vetorAtual = pop(&rota);
    if (vetorAtual != 34) {
        printf("\n Teste  Falhou \n\n");
        return;
    }

    vetorAtual = pop(&rota);
    if (vetorAtual != 16) {
        printf("\n Teste  Falhou \n\n");
        return;
    }

    vetorAtual = pop(&rota);
    if (vetorAtual != 50) {
        printf("\n Teste  Falhou \n\n");
        return;
    }

    vetorAtual = pop(&rota);
    if (vetorAtual != 48) {
        printf("\n Teste  Falhou \n\n");
        return;
    }
    
    vetorAtual = pop(&rota);
    if (vetorAtual != 23) {
        printf("\n Teste  Falhou \n\n");
        return;
    }

    vetorAtual = pop(&rota);
    if (vetorAtual != 38) {
        printf("\n Teste  Falhou \n\n");
        return;
    }
    vetorAtual = pop(&rota);
    if (vetorAtual != 4) {
        printf("\n Teste  Falhou \n\n");
        return;
    }

    vetorAtual = pop(&rota);
    if (vetorAtual != 45) {
        printf("\n Teste  Falhou \n\n");
        return;
    }

    vetorAtual = pop(&rota);
    if (vetorAtual != 44) {
        printf("\n Teste  Falhou \n\n");
        return;
    }

    vetorAtual = pop(&rota);
    if (vetorAtual != 1) {
        printf("\n Teste  Falhou \n\n");
        return;
    }
    printf("\n\n O teste passou\n ");
}


int main() {
    printf("\n Primeiro teste:\n");
    diskjraTeste1();

    printf("\n\n Segundo teste:\n");
    testeRotaOnibusPara18();
}
