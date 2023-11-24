#include "../include/GraphTools.h"
#include "../include/ListTools.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define INFINITO 9999
#define MAX_LINE_LENGTH 1000 //tamanho maximo das linhas do arquivo csv
#define MAX_COLUMNS 8 //numero maximo de colunas do arquivo csv


void limparGrafo(struct GRAFO *grafo);


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
    struct GRAFO * grafo = (struct GRAFO * ) malloc(sizeof(struct GRAFO));
    if (!grafo) {
        printf("\n Falha na alocação de memória!");
        return NULL;
    }

    grafo->numVertices = vertices;
    grafo->visitado = (int *)malloc(vertices * sizeof(int));
    grafo->adjListas = (struct NODO **)malloc(vertices * sizeof(struct NODO *));
    grafo->ant = (int *)malloc(vertices * sizeof(int));
    grafo->dist = (int *)malloc(vertices * sizeof(int));
    grafo->coordenadas = (struct PONTO *)malloc(vertices * sizeof(struct PONTO));
    grafo->nomes = (char **)malloc(vertices * sizeof(char *)); //array de ponteiros para caracteres/strings

    if (!(grafo->visitado && grafo->adjListas && grafo->ant && grafo->dist && grafo->coordenadas)) {
        limparGrafo(grafo); // Função para liberar a memória alocada
        printf("\n Falha na alocação de memória!");
        return NULL;
    }

    for (int i = 0; i < vertices; i++) {
        grafo->adjListas[i] = NULL;
        grafo->visitado[i] = 0;
        grafo->ant[i] = 0;
        grafo->dist[i] = INFINITO;
    }

    return grafo;
}

void limparGrafo(struct GRAFO *grafo) {
    if (grafo) {
        free(grafo->visitado);
        free(grafo->adjListas);
        free(grafo->ant);
        free(grafo->dist);
        free(grafo->coordenadas);
        free(grafo->nomes);
        free(grafo);
    }
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

void adicionarVertice(struct GRAFO * grafo, int vertice, char nome[3], int x, int y) {
    grafo->nomes[vertice] = nome;
    grafo->coordenadas[vertice].x = x;
    grafo->coordenadas[vertice].y = y;
}

/*****************************************************************************************
 * adicionarAresta                                                                       *
 * objetivo: adiciona o vertice de destino na lista de adjacencias do vertice de origem  *
 * entrada : grafo, origem, destino, distancia                                           *
 * saída   : lista de adjacencias atualizada                                             *
 *****************************************************************************************/
void adicionarAresta(struct GRAFO * grafo, int origem, int destino) {
    int distancia = distanciaEntreDoisPontos(grafo->coordenadas[origem].x , grafo->coordenadas[origem].y , grafo->coordenadas[destino].x , grafo->coordenadas[destino].y);
    struct NODO *no;                      // Ponteiro para um nodo
    no = criaNo(destino, distancia);      // Cria o nodo do vértice destino.
    no->prox = grafo->adjListas[origem];  // Adiciona nó da origem para o destino.
    grafo->adjListas[origem] = no;        // Adiciona na lista de adjacências o vértice de destino.
}

/*****************************************************************************************
 * distanciaEntreDoisPontos                                                              *
 * objetivo: calcula a distancia entre dois pontos                                       *
 * entrada : pontos x e y do vertice de origem e pontos x e y do vertice de destino      *
 * saída   : distancia aproximada em pixels (talves seja interesante retornar float)     *
 *****************************************************************************************/
int distanciaEntreDoisPontos(int x0, int y0, int x1, int y1) {
    int distancia;
    distancia = sqrt(pow((x1 - x0), 2) + pow((y1 - y0), 2)); //formula da distancia entre dois pontos
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

/**********************************************************************************************
 * importaGrafo                                                                               *
 * objetivo: importar vertices, coordenadas dos vertices, e seus adjacentes de um arquivo csv.*
 * entrada :                                                                                  *
 * saída   : vertices, coordenadas dos vertices e lista de adjacencias criadas/atualizadas    *
 **********************************************************************************************/
void importaGrafo(struct GRAFO *grafo){
    const char *filename = "../input_data/grafoData.csv";
    //ponteiro para o arquivo no modo read (leitura)
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo csv");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    struct DataRecord record; //estrutura record para armazenar valores das colunas

    // Ignorar a linha de cabeçalho se houver uma
    if (fgets(line, MAX_LINE_LENGTH, file) == NULL) {
        perror("Erro ao ler a linha de cabeçalho do arquivo csv");
        exit(EXIT_FAILURE);
    }

    // Lê uma linha do arquivo 'file' e armazena os caracteres lidos na variavel 'line', enquanto houver linhas. MAX_LINE_LENGTH define o tamanho maximo da linha
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        //armazena os valores das colunas 1, 2, 3 e 4
        sscanf(line, "%i,%i,%i,%[^,]", &record.vertice, &record.x, &record.y, record.referencia);
        adicionarVertice(grafo, record.vertice, record.referencia, record.x, record.y); //adiciona o vertice da coluna iterada e seus dados
    }

    // Reposiciona o ponteiro do arquivo para o início
    fseek(file, 0, SEEK_SET);

    // Ignorar a linha de cabeçalho se houver uma
    if (fgets(line, MAX_LINE_LENGTH, file) == NULL) {
        perror("Erro ao ler a linha de cabeçalho do arquivo csv");
        exit(EXIT_FAILURE);
    }

    // Lê uma linha do arquivo 'file' e armazena os caracteres lidos na variavel 'line', enquanto houver linhas. MAX_LINE_LENGTH define o tamanho maximo da linha
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        //armazena os valores das colunas 5, 6, 7 e 8
        sscanf(line, "%i,%*i,%*i,%*[^,],%i,%i,%i,%i", &record.vertice, &record.adjacente1, &record.adjacente2, &record.adjacente3, &record.adjacente4);
        if(record.adjacente1 != -1)
            adicionarAresta(grafo, record.vertice, record.adjacente1);
        if(record.adjacente2 != -1)
            adicionarAresta(grafo, record.vertice, record.adjacente2);
        if(record.adjacente3 != -1)
            adicionarAresta(grafo, record.vertice, record.adjacente3);
        if(record.adjacente4 != -1)
            adicionarAresta(grafo, record.vertice, record.adjacente4);
    }

    fclose(file);
}
/************************************************ 
 * mostra    Grafo                              *
 * objetivo: imprimir o grafo                   *
 * entrada : grafo                              *
 * saída   : nenhuma                            *
 ************************************************/
void imprimeGrafo(struct GRAFO *grafo){
    int i;
    for( i = 0; i < grafo->numVertices; i++){
        struct NODO *temp = grafo->adjListas[i]; // Cria um ponteiro temporário para caminhar pelo grafo.
        printf( "\n Lista de adjacencias do vertice %d\n ", i );
        while(temp){
            printf("%d -> ", temp->vertice);
            printf("(%i)", temp->distancia);
            temp = temp->prox;
        }
        printf("\n" );
    }
}