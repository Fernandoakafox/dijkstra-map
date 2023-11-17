#include <stdio.h>
#include <stdlib.h>

/***********************************************/
/* Definição do Registro e da Estrutura        */
/***********************************************/
struct NODO {
    int vertice;
    int distancia; //em metros
    int tipo;      //(1)ponto de interesse, (2)esquina para esquerda, (3)esquina para direita, (4)encruzilhada
    struct NODO * prox;
};

struct GRAFO {
    int *dist; //vetor para armazenar a distancia do vertice em relação ao ponto de partida
    int *ant;  //vetor para armazenar o vertice anterior
    int numVertices;
    int *visitado;
    struct NODO ** adjListas; // Para um array bidimensional dinâmico usamos **. Da mesma forma, usamos struct nodo** para armazenar um array para uma lista encadeada.
};
/***********************************************/
/* Definição das Funções                       */
/***********************************************/

int main (){

}