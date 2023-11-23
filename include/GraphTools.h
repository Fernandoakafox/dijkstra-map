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
    char **nomes; // Vetor de strings, para armazenar os nomes dos vertices
    struct PONTO *coordenadas; // Vetor de estruturas, para armazenar as coordenadas dos vertices
    struct NODO ** adjListas; // Para um array bidimensional dinâmico usamos **. Da mesma forma, usamos struct nodo** para armazenar um array para uma lista encadeada.
};

//estrutura para manipular dados de um arquivo csv
struct DataRecord {
    int vertice;        //coluna 1 do csv
    int x;              //coluna 2 do csv
    int y;              //coluna 3 do csv
    char referencia[3]; //coluna 4 do csv
    int adjacente1;     //coluna 5 do csv
    int adjacente2;     //coluna 6 do csv
    int adjacente3;     //coluna 7 do csv
    int adjacente4;     //coluna 8 do csv
};

struct GRAFO * criaGrafo(int vertices);
struct NODO * criaNo(int valor, int distancia);
void adicionarAresta(struct GRAFO * grafo, int origem, int destino);
int distanciaEntreDoisPontos(int x0, int y0, int x1, int y1);
struct Pilha* dijkstra(struct GRAFO *grafo, int partida, int destino);
void adicionarVertice(struct GRAFO * grafo, int vertice, char nome[3], int x, int y);
void  importaGrafo(struct GRAFO * grafo);
#endif // GRAPHTOOLS_H