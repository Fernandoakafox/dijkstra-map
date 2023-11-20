#include "../include/GraphTools.h" // Biblioteca do desenvolvedor, para manipulação de grafos
#include "../include/Graphic.h"    // Biblioteca do desenvolvedor, para manipulação gráfica
#include "../include/ListTools.h"
#include <stdio.h>
#include <stdlib.h>

//ATENÇÃO -> O que esta comentado em main, esta comentado pois ao rodar da bug, descobrir o bug
int main (){
    struct GRAFO *grafo = criaGrafo(4);
    adicionarVertice(grafo, 0, "B1", 871, 351);
    adicionarVertice(grafo, 1, "0", 871, 479);
    adicionarVertice(grafo, 2, "0", 799, 479);  // 0 pode significar encruzilhada ou algo do tipo
    adicionarVertice(grafo, 3, "B2", 799, 536);

    adicionarAresta(grafo, 0, 1);
    adicionarAresta(grafo, 1, 2);
    adicionarAresta(grafo, 2, 3); 


    struct Pilha *dijkstraRoute = dijkstra(grafo, 0, 3);
    //printf("TOPO: %i\n", dijkstraRoute->topo->vertice); O bug parece ser com a pilha

    plot_route(&dijkstraRoute, grafo);
}