//este arquivo contem o protótipo das funções, também conhecido como cabeçalho das funções
#ifndef GRAPHTOOLS_H //Se GRAPHTOOLS_H não estiver definido (o que significa que é a primeira vez que o arquivo de cabeçalho é incluído)
#define GRAPHTOOLS_H //define o símbolo GRAPHTOOLS_H, indicando que o arquivo de cabeçalho foi incluído.

#include "ListTools.h"
#include <stdlib.h>
#include <math.h>

/***********************************************/
/* Definição do Registro e da Estrutura        */
/***********************************************/
struct NODO {
    int vertice;
    int distancia; // Em metros ou pixels
    struct NODO * prox;
};

struct PONTO{
    int x;
    int y;
};

struct GRAFO {
    int *dist; // Vetor para armazenar a distancia do vertice em relação ao ponto de partida
    int *ant;  // Vetor para armazenar o vertice anterior
    int numVertices;
    int *visitado;
    struct PONTO *coordenadas; // Vetor de estruturas, para armazenar as coordenadas dos vertices
    struct NODO ** adjListas; // Para um array bidimensional dinâmico usamos **. Da mesma forma, usamos struct nodo** para armazenar um array para uma lista encadeada.
};

struct GRAFO * criaGrafo(int vertices);
struct NODO * criaNo(int valor, int distancia);
void adicionarAresta(struct GRAFO * grafo, int origem, int destino);
int distanciaEntreDoisPontos(int x0, int y0, int x1, int y1);
struct Pilha* dijkstra(struct GRAFO *grafo, int partida, int destino);


#endif // GRAPHTOOLS_H