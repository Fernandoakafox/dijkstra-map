#include "../include/GraphTools.h" // Biblioteca do desenvolvedor, para manipulação de grafos
#include "../include/Graphic.h"    // Biblioteca do desenvolvedor, para manipulação gráfica
#include "../include/ListTools.h"
#include <stdio.h>
#include <stdlib.h>

//ATENÇÃO -> O que esta comentado em main, esta comentado pois ao rodar da bug
// TODO descobrir o bug
int main (){
    struct GRAFO *grafo = criaGrafo(38); //temos vertice 0, logo se o nosso ultimo vertice é o 37, temos no total 38 vertices

    importaGrafo(grafo);

        
    //struct Pilha *dijkstraRoute = dijkstra(grafo, 5, 35);
    //printf("TOPO: %i\n", dijkstraRoute->topo->vertice); // O bug parece ser com a pilha
    
    //plot_route(&dijkstraRoute, grafo);
}