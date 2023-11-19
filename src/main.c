#include "../include/GraphTools.h" // Biblioteca do desenvolvedor, para manipulação de grafos
#include "../include/Graphic.h"    // Biblioteca do desenvolvedor, para manipulação gráfica
#include <stdio.h>
#include <stdlib.h>

int main (){
    struct GRAFO *grafo = criaGrafo(2);
    grafo->coordenadas[0].x = 871;
    grafo->coordenadas[0].y = 351;
    grafo->coordenadas[1].x = 871;
    grafo->coordenadas[1].y = 479;

    adicionarAresta(grafo, 0, 1);


    dijkstra(grafo, 0, 1);

    plot_line (grafo->coordenadas[0].x, grafo->coordenadas[0].y, grafo->coordenadas[1].x, grafo->coordenadas[1].y, 10, 255, 165, 0);
    printf("Distancia = %i\n", grafo->adjListas[1]->distancia);
}