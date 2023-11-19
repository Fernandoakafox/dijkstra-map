#include "../include/GraphTools.h" // Biblioteca do desenvolvedor, para manipulação de grafos
#include "../include/Graphic.h"    // Biblioteca do desenvolvedor, para manipulação gráfica
#include "../include/ListTools.h"
#include <stdio.h>
#include <stdlib.h>

//ATENÇÃO -> O que esta comentado em main, esta comentado pois ao rodar da bug, descobrir o bug
int main (){
    struct GRAFO *grafo = criaGrafo(4);
    grafo->coordenadas[0].x = 871;
    grafo->coordenadas[0].y = 351;
    grafo->coordenadas[1].x = 871;
    grafo->coordenadas[1].y = 479;
    grafo->coordenadas[2].x = 799;
    grafo->coordenadas[2].y = 479;
    grafo->coordenadas[3].x = 799;
    grafo->coordenadas[3].y = 536;


    adicionarAresta(grafo, 0, 1);
    adicionarAresta(grafo, 1, 2);
    adicionarAresta(grafo, 2, 3); 


    struct Pilha *dijkstraRoute = dijkstra(grafo, 0, 3);
    //printf("TOPO: %i\n", dijkstraRoute->topo->vertice); O bug parece ser com a pilha

    plot_route(&dijkstraRoute, grafo);
}