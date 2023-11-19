#include "../include/GraphTools.h"
#include "../include/ListTools.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define INFINITO 9999




/***********************************************/
/* Funções                                     */
/***********************************************/

/************************************************  
 * criaGrafo                                    *
 * objetivo: cria o grafo                       *
 * entrada : número de vertices                 *
 * saida   : endereço de memoria para o grafo   *
 ************************************************/
struct GRAFO* criaGrafo(int vertices){
    struct GRAFO * grafo = (struct GRAFO * ) malloc(sizeof(struct GRAFO)); // Aloca memória para o grafo.
    if (grafo == NULL){
        printf("\n Não foi possível alocar memória!");
        return NULL; //indica falha na alocação
    }

    grafo->numVertices = vertices; // Inicializa o campo de número de vértices do grafo.
    
    grafo->visitado = (int *)malloc(vertices * sizeof(int)); // Cria a lista sequencial de visitados conforme o número de vértices.
    // Verifica a alocação de memória para grafo->visitado
    if (grafo->visitado == NULL) {
        printf("\nNão foi possível alocar memória para visitado!");
        free(grafo); // Libera a memória alocada para o grafo
        return NULL; // Indica falha na alocação
    }

    grafo->adjListas = (struct NODO **)malloc(vertices * sizeof(struct NODO *));// Cria a lista de adjacências conforme o número de vértices.
    // Verifica a alocação de memória para grafo->adjListas
    if (grafo->adjListas == NULL) {
        printf("\nNão foi possível alocar memória para adjListas!");
        free(grafo->visitado); // Libera a memória alocada para visitado
        free(grafo); // Libera a memória alocada para o grafo
        return NULL; // Indica falha na alocação
    }

    grafo->ant = (int *)malloc(vertices * sizeof(int)); // Cria a lista sequencial que armazena o vertice anterior
    // Verifica a alocação de memória para grafo->ant
    if (grafo->ant == NULL) {
        printf("\nNão foi possível alocar memória para ant!");
        free(grafo->adjListas); // Libera a memória alocada para adjListas
        free(grafo->visitado); // Libera a memória alocada para visitado
        free(grafo); // Libera a memória alocada para o grafo
        return NULL; // Indica falha na alocação
    }

    grafo->dist = (int *)malloc(vertices * sizeof(int)); // Cria a lista sequencial que armazena a distancia do vertice em relação ao ponto de partida
    // Verifica a alocação de memória para grafo->dist
    if (grafo->dist == NULL) {
        printf("\nNão foi possível alocar memória para dist!");
        free(grafo->ant); // Libera a memória alocada para ant
        free(grafo->adjListas); // Libera a memória alocada para adjListas
        free(grafo->visitado); // Libera a memória alocada para visitado
        free(grafo); // Libera a memória alocada para o grafo
        return NULL; // Indica falha na alocação
    }

    grafo->coordenadas = (struct PONTO *)malloc(vertices * sizeof(struct PONTO)); // Cria o vetor estruturado que armazena as coordenadas do vertice
    // Verifica a alocação de memória para grafo->coordenadas
    if (grafo->coordenadas == NULL) {
        printf("\nNão foi possível alocar memória para coordenadas!");
        free(grafo->dist); // Libera a memória alocada para dist
        free(grafo->ant); // Libera a memória alocada para ant
        free(grafo->adjListas); // Libera a memória alocada para adjListas
        free(grafo->visitado); // Libera a memória alocada para visitado
        free(grafo); // Libera a memória alocada para o grafo
        return NULL; // Indica falha na alocação
    }
        
    // Itera sobre os campos do grafo setando os valores predefinidos
    int i;
    for (i = 0; i < vertices; i++) {
        grafo->adjListas[i] = NULL;
        grafo->visitado[i] = 0;
        grafo->ant[i] = 0;
        grafo->dist[i] = INFINITO; //para o dijkstra funcionar setamos infinito, no futuro devemos fazer isso ao chamar o dijskra
    }
    
    // Retorna endereço para a estrutura grafo criada
    return grafo;
}

/*************************************************************
 * NECESARIO FAZER : verificação de memoria para cada malloc * 
 * criaNodo                                                  *
 * objetivo: cria novo nodo                                  *
 * entrada : valor do nodo                                   *
 * saida   : endereço do nodo criado                         *
 *************************************************************/
struct NODO * criaNo(int valor, int distancia) {
    struct NODO * no = (struct NODO * ) malloc(sizeof(struct NODO));
    no->vertice = valor;
    no->distancia = distancia;
    no->prox = NULL;
    return no;
}

/*****************************************************************************************
 * adicionarAresta                                                                       *
 * objetivo: adiciona aresta bidirecional entre vertice de origem e vertice de destino   *
 * entrada : grafo, origem, destino, distancia                                           *
 * saída   : grafo (por referência)                                                      *
 *****************************************************************************************/
void adicionarAresta(struct GRAFO * grafo, int origem, int destino) {
    int distancia = distanciaEntreDoisPontos(grafo->coordenadas[origem].x , grafo->coordenadas[origem].y , grafo->coordenadas[destino].x , grafo->coordenadas[destino].y);
    struct NODO *no;                      // Ponteiro para um nodo
    no = criaNo(destino, distancia);      // Cria o nodo do vértice destino.
    no->prox = grafo->adjListas[origem];  // Adiciona nó da origem para o destino.
    grafo->adjListas[origem] = no;        // Adiciona na lista de adjacências o vértice de destino.

    no = criaNo(origem, distancia);       // Cria o nodo do vértice origem.
    no->prox = grafo->adjListas[destino]; // Adiciona nó do destino para a origem.
    grafo->adjListas[destino] = no;       // Adiciona na lista de adjacências o vértice de origem.
}

/*****************************************************************************************
 * distanciaEntreDoisPontos                                                              *
 * objetivo: calcula a distancia entre dois pontos                                       *
 * entrada : pontos x e y do vertice de origem e pontos x e y do vertice de destino      *
 * saída   : distancia aproximada em pixels (talves seja interesante retornar float)     *
 *****************************************************************************************/
int distanciaEntreDoisPontos(int x0, int y0, int x1, int y1) {
    int distancia;
    distancia = sqrt((pow((x1 - x0), 2)) + pow((y1 - y0), 2)); //formula da distancia entre dois pontos
    return distancia;
}

/*************************************************************************************************************************
 * dijsktra                                                                                                              *
 * objetivo: Encontrar rota mais curta no grafo                                                                          *
 * entrada : grafo, vertice de partida, vertice de destino                                                               *
 * saída   : Retorna o endereço de uma pilha contendo o indice dos vertices da rota mais curta, partida no topo da pilha *
 *************************************************************************************************************************/
struct Pilha* dijkstra(struct GRAFO *grafo, int partida, int destino){
    // Redefini os campos do grafo que serão utilizados pelo dijsktra
    int i;
    for (i = 0; i < grafo->numVertices; i++) {
        grafo->visitado[i] = 0;
        grafo->ant[i] = 0;
        grafo->dist[i] = INFINITO;
    }

    grafo->dist[partida] = 0;     //ponto de partida tem distancia = 0
    grafo->visitado[partida] = 1; //visita ponto de partida
    grafo->ant[partida] = -1;     //ponto de partida não tem antecessor

    struct NODO *temp = grafo->adjListas[partida]; //ponteiro para o primeiro adjacente da lista de adjacencias do vertice de partida
    int verticeAtual = partida;                    //armazena o indice do vertice de iteração atual

    //enquanto o vertice de destino não foi visitado
    while(grafo->visitado[destino] != 1){
        int maisProximo = temp->vertice; //armazena o indice do vertice adjacente mais proximo, é iniciado com o primeiro vertice adjacente
        int distanciaMaisProximo = temp->distancia; //armazena a distancia do vertice adjacente mais proximo
        //o loop abaixo defini a distancia entre vertice de partida e seus adjacentes
        //enquanto temp apontar para um nodo existente na lista de adjacencias
        while(temp != NULL){
            //se o vertice ainda não foi visitado
            if(grafo->visitado[temp->vertice] == 0){
                if( (grafo->dist[verticeAtual] + temp->distancia) < grafo->dist[temp->vertice] ){ //se o distancia até chegar neste vertice adjacente for menor que o menor distancia anteriormente definido para chegar neste vertice adjacente
                    grafo->dist[temp->vertice] = grafo->dist[verticeAtual] + temp->distancia;  //atualiza o distancia para chegar neste vertice
                    grafo->ant[temp->vertice] = verticeAtual;
                }
                if (temp->distancia < distanciaMaisProximo){
                    maisProximo = temp->vertice;        //atualiza o maisProximo
                    distanciaMaisProximo = temp->distancia; //atualiza a distancia do mais proximo
                }
            }
            temp = temp->prox;
        }
        //visitar o nodo com distancia menor e que ainda não foi visitado, entre os nodos adjacentes
        grafo->visitado[maisProximo] = 1;
        verticeAtual = maisProximo; //atualiza o vertice atual
        temp = grafo->adjListas[maisProximo];
    }

    printf("A distancia mais proxima até o vertice de destino é: %i\n", grafo->dist[verticeAtual]);
    int aux = destino;
    struct Pilha *dijkstraRoute = NULL; //Cria um ponteiro para uma estrutura pilha 
    inicializaPilha(&dijkstraRoute);    //Esta pilha armazenara o indice dos vertices da rota mais rapida e sera utilizada para plotar os pixels
    // itera pelos vertices da rota mais curta, começando do destino até chegar na origem
    while(aux != - 1){
        printf("%i ", aux);
        push(&dijkstraRoute, aux); //empilha indice do vertice 
        aux = grafo->ant[aux];     //aux recebe o indice do vertice anterior ao vertice em questão
    }
    return dijkstraRoute;
}