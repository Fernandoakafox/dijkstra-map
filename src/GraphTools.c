#include "../include/GraphTools.h"
#include "../include/ListTools.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_DISTANCE 999            //A maior distancia entre vertices, em pixels
#define INFINITO MAX_DISTANCE + 1   //INFINITO sempre sera o valor de MAX_DISTANCE + 1
#define MAX_LINE_LENGTH 1000        //tamanho maximo das linhas do arquivo csv
#define MAX_COLUMNS 8               //numero maximo de colunas do arquivo csv





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
        liberarMemoriaGrafo(grafo); // Função para liberar a memória alocada
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

void liberarMemoriaGrafo(struct GRAFO *grafo) {
    if (grafo) {
        free(grafo->visitado);
        //libera memoria da lista de adjacencias
        int i;
        for (i = 0; i < grafo->numVertices; i++) {
            struct NODO *temp = grafo->adjListas[i];
            while(temp != NULL){
                struct NODO *aux = temp;
                temp = temp->prox;
                free(aux);
            }
            grafo->adjListas[i] = NULL;
        }
        // Libera memoria do array de ponteiros adjListas
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
        grafo->dist[i] = MAX_DISTANCE; //setamos a distancia de todos elementos com a distancia maxima
    }

    grafo->dist[partida] = 0;     //ponto de partida é setado com distancia = 0
    grafo->ant[partida] = -1;     //ponto de partida não tem antecessor

    int verticeAtual; //armazena o indice do vertice de iteração atual
    int maisProximo;

    //enquanto o vertice de destino não foi visitado
    while(grafo->visitado[destino] != 1){

        int distanciaMaisProximo = INFINITO; //deve ser setada como maior que a distancia inicialmente setada para os elementos do vetor dist[]
        //Loop percorre lista de visitado e de distancia, em busca do elemento com menor valor. Em outras palavras, busca o vertice, ainda não visitado e mais proximo ao ponto de partida
        for(i = 0; i < grafo->numVertices; i++){
            if(grafo->dist[i] < distanciaMaisProximo && grafo->visitado[i] == 0){
                distanciaMaisProximo = grafo->dist[i]; //armazena a distancia do vertice adjacente mais proximo
                maisProximo = i; //armazena o indice do vertice adjacente mais proximo
            }
        }
        verticeAtual = maisProximo;        //Vertice de iteração atual é o vertice, ainda não visitado, com a menor distancia até o ponto de partida
        grafo->visitado[verticeAtual] = 1; //Visita o vertice atual

        struct NODO *temp = grafo->adjListas[verticeAtual];//ponteiro para o primeiro adjacente da lista de adjacencias do vertice de partida
        //o loop abaixo defini a distancia entre vertice de partida e seus adjacentes
        while(temp != NULL){
            //se o vertice ainda não foi visitado
            if(grafo->visitado[temp->vertice] == 0){
                if((grafo->dist[verticeAtual] + temp->distancia) < grafo->dist[temp->vertice] ){ //se o tempo até chegar neste vertice adjacente for menor que o menor tempo anteriormente definido para chegar neste vertice adjacente
                    grafo->dist[temp->vertice] = grafo->dist[verticeAtual] + temp->distancia;  //atualiza o tempo para chegar neste vertice
                    grafo->ant[temp->vertice] = verticeAtual;
                }
            }
            temp = temp->prox;
        }
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
 * entrada : endereço do ponteiro para o grafo                                                *
 * saída   : vertices, coordenadas dos vertices e lista de adjacencias criadas/atualizadas    *
 **********************************************************************************************/
void importaGrafo(struct GRAFO **grafo){
    const char *filename = "../input_data/grafoData.csv";
    //ponteiro para o arquivo no modo read (leitura)
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo csv");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];

    // Ignorar a linha de cabeçalho se houver uma
    ignorarCabecalhoCSV(file, line);

    int vertices = 0;
    // Itera sobre o arquivo csv, armazenando o numero de linhas como numero de vertices, visto que cada linha representa um vertice
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL){
        vertices++;
    }
    
    //cria espaço de memoria para o grafo conforme numero de vertices 
    *grafo = criaGrafo(vertices);

    // Reposiciona o ponteiro de posição de leitura para o início do arquivo
    fseek(file, 0, SEEK_SET);

    struct DataRecord record; //estrutura record para armazenar valores das colunas

    // Ignorar a linha de cabeçalho se houver uma
    ignorarCabecalhoCSV(file, line);

    // Lê uma linha do arquivo 'file' e armazena os caracteres lidos na variavel 'line', enquanto houver linhas. MAX_LINE_LENGTH define o tamanho maximo da linha
    //fgets reposiciona automaticamente a posição do ponteiro de leitura para o inicio da proxima linha
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        //armazena os valores das colunas 1, 2, 3 e 4
        sscanf(line, "%i,%i,%i,%[^,]", &record.vertice, &record.x, &record.y, record.referencia);
        adicionarVertice(*grafo, record.vertice, record.referencia, record.x, record.y); //adiciona o vertice da coluna iterada e seus dados
    }

    // Reposiciona o ponteiro de posição de leitura para o início do arquivo
    fseek(file, 0, SEEK_SET);

    // Ignorar a linha de cabeçalho se houver uma
    ignorarCabecalhoCSV(file, line);

    // Lê uma linha do arquivo 'file' e armazena os caracteres lidos na variavel 'line', enquanto houver linhas. MAX_LINE_LENGTH define o tamanho maximo da linha
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        //armazena os valores das colunas 5, 6, 7 e 8
        sscanf(line, "%i,%*i,%*i,%*[^,],%i,%i,%i,%i", &record.vertice, &record.adjacente1, &record.adjacente2, &record.adjacente3, &record.adjacente4);
        if(record.adjacente1 != -1)
            adicionarAresta(*grafo, record.vertice, record.adjacente1);
        if(record.adjacente2 != -1)
            adicionarAresta(*grafo, record.vertice, record.adjacente2);
        if(record.adjacente3 != -1)
            adicionarAresta(*grafo, record.vertice, record.adjacente3);
        if(record.adjacente4 != -1)
            adicionarAresta(*grafo, record.vertice, record.adjacente4);
    }

    fclose(file);
}

/*********************************************************************
 * objetivo: Ignorar a linha de cabeçalho se houver uma              *
 * entrada : ponteiro para o arquivo file e vetor de caracteres line *
 * saída   : nenhuma                                                 *
 *********************************************************************/
void ignorarCabecalhoCSV(FILE *file, char line[]){
    if (fgets(line, MAX_LINE_LENGTH, file) == NULL) {
        perror("Erro ao ler a linha de cabeçalho do arquivo csv");
        exit(EXIT_FAILURE);
    }
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
/******************************************************************* 
 * objetivo: converter distancia em pixel para distancia em metros *
 * entrada : distancia em pixels                                   *
 * saída   : distancia em metros                                   *
 *******************************************************************/
float converterPixelEmMetros(int distanciaEmPixels){
    float distanciaEmMetros = distanciaEmPixels * 0.57063829787234042553191489361702;
    return distanciaEmMetros;
}