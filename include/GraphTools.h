//este arquivo contem o protótipo das funções, também conhecido como cabeçalho das funções
#ifndef GRAPHTOOLS_H //Se GRAPHTOOLS_H não estiver definido (o que significa que é a primeira vez que o arquivo de cabeçalho é incluído)
#define GRAPHTOOLS_h //define o símbolo GRAPHTOOLS_H, indicando que o arquivo de cabeçalho foi incluído.

#include <stdlib.h>
#include <math.h>


struct GRAFO * criaGrafo(int vertices);
struct NODO * criaNo(int valor, int distancia);
void adicionarAresta(struct GRAFO * grafo, int origem, int destino);
int distanciaEntreDoisPontos(int x0, int y0, int x1, int y1);


#endif