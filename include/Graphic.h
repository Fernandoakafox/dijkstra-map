//este arquivo contem o protótipo das funções, também conhecido como cabeçalho das funções
#ifndef GRAPHIC_H //Se GRAPHIC_H não estiver definido (o que significa que é a primeira vez que o arquivo de cabeçalho é incluído)
#define GRAPHIC_H //define o símbolo GRAPHIC_H, indicando que o arquivo de cabeçalho foi incluído.
#include <stdio.h>
#include <stdlib.h>
#include "ListTools.h"
#include "GraphTools.h"

void plot_line (int x0, int y0, int x1, int y1, int espessura, int r, int g, int b);
void plot_pixel(FILE *file, int y, int x, int r, int g, int b, int pixel_data_offset);
void plot_route(struct Pilha **head, struct GRAFO *grafo);


#endif // GRAPHIC_H