#include "../include/GraphTools.h" // Biblioteca do desenvolvedor, para manipulação de grafos
#include "../include/Graphic.h"    // Biblioteca do desenvolvedor, para manipulação gráfica
#include "../include/ListTools.h"
#include <stdio.h>
#include <stdlib.h>

// .:| ========= Declaração de funções de outros arquivos ========== |:.
// é necessário declara-las aqui pois ao usa-las dentro de outras funções na main
// não são consideradas declaradas
int getColorRed();
int getColorGreen();
int getColorBlue();

void setColorRed();
void setColorGreen();
void setColorBlue();


// .:| ========= Declaração das funções ========= |:.
void printDisplay(struct GRAFO *grafo);
void printMenu();

void setPontoPartida(int vertices);
void setPontoChegada(int vertices);
void limparPontos();
void alterarCorDaLinha();
void tracarRota(struct GRAFO * grafo, struct Pilha **dijkstraRoute);
void resetarImagem();

// .:| ========= Globais ========= |:.
int pontoPartida = -1;
int pontoChegada = -1;


int main (){
    int opcao;

    struct GRAFO *grafo;

    // inicializa o Grafo pelo arquivo csv
    importaGrafo(&grafo);
    imprimeGrafo(grafo);

    struct Pilha *dijkstraRoute;
   
    while(1){
        printDisplay(grafo);
        printMenu();

        printf( "\n Opção: " );
        fflush( stdin );
        scanf("%i", &opcao);

        switch(opcao){

            case 0:
                liberarMemoriaGrafo(grafo);
                exit(0);
                break;

            case 1:
                setPontoPartida(grafo->numVertices);
                break;
            
            case 2:
                setPontoChegada(grafo->numVertices);
                break;

            case 3:
                limparPontos();
                break;

            case 4: 
                alterarCorDaLinha();
                break;

            case 5:
                tracarRota(grafo, &dijkstraRoute);
                break;

            case 6:
                resetarImagem();
                break;

            default:
                printf("Escolha uma Opção Válida!");
                break;
        }

        printf( "\n" );
        system( "clear" );   // limpar tela
    }

}


void printDisplay(struct GRAFO *grafo) {
    printf("\n| === DISPLAY === |");

    // Pontos de Entrada e saída
    printf("\n Ponto de Partida: ");
    if (pontoPartida != -1){
         printf("%d", pontoPartida);
    } else {
        printf("Vazio!");
    }

    printf("\n Ponto de Chegada: ");
    if (pontoChegada != -1){
         printf("%d", pontoChegada);
    } else {
        printf("Vazio!");
    }

    printf("\n Distãncia entre os pontos: ");
    if (grafo->dist[pontoChegada] != 1000 && grafo->dist[pontoChegada] != 0){
        printf("%.2f metros", converterPixelEmMetros(grafo->dist[pontoChegada]));
    } else {
        printf("Aguardando traçar rota!");
    }

    printf("\n");

    // Cores da linha
    printf("\n Tonalidade Vermelha da Linha: %d", getColorRed());
    printf("\n Tonalidade Verde da Linha: %d", getColorGreen());
    printf("\n Tonalidade Azul da Linha: %d", getColorBlue());

    printf("\n");
    printf("\n");
}


void printMenu() {
    printf("\n .:| ======================= MENU ======================= |:. ");
    printf("\n     [1] Escolher ponto de partida ");
    printf("\n     [2] Escolher ponto de chegada ");
    printf("\n     [3] Resetar pontos de Partida e Chegada ");
    printf("\n     [4] Alterar a cor da Linha ");
    printf("\n     [5] Traçar rota ");
    printf("\n     [6] Resetar imagem ");
    printf("\n     [0] Sair");
    printf("\n  :| ======================= ==== ======================= |: \n");
}


void printfOpcoesCores() {
    printf("\n === Escolha a cor da linha ===");
    printf("\n [1] Padrão (recomentada)");
    printf("\n [2] Vermelho");
    printf("\n [3] Verde");
    printf("\n [4] Azul");
    printf("\n [5] Custom");
}

// [1] Escolher Ponto de Partida
void setPontoPartida (int vertices) {
    int valorValido = 0;
    int entrada;

    while (!valorValido){
        printf("\n Digite o valor do ponto de Partida: ");
        scanf("%i", &entrada);
        // TODO adicionar validação de pontos existentes e válidos
        if (entrada >= 0 && entrada < vertices){
            valorValido = 1;
        } else {
            printf("\n Valor inválido!");
        }
    }

    pontoPartida = entrada;
    printf("\n Ponto de Partida selecionado!");
} 


// [2] Escolher Ponto de Chegada
void setPontoChegada (int vertices) {
    int valorValido = 0;
    int entrada;

    while (!valorValido){
        printf("\n Digite o valor do ponto de chegada: ");
        scanf("%i", &entrada);
        
        if (entrada >= 0 && entrada < vertices){
            valorValido = 1;
        } else {
            printf("\n Valor inválido!");
        }
    }

    pontoChegada = entrada;
    printf("\n Ponto de Chegada selecionado!");
}


// [3] Limpar Pontos de Partida e Chegada
void limparPontos() {
    pontoChegada = -1;
    pontoPartida = -1;

    printf("Pontos de Partida e Chegada Resetados");
}

// [4] Alterar a cor da linha
void alterarCorDaLinha() {
    int opcao;
    int entradaInvalida = 1;

    while (entradaInvalida){

        printfOpcoesCores();
        printf( "\n Opção: " );
        fflush( stdin );
        scanf("%i", &opcao);

        switch (opcao){
        
            case 1: // PADRÃO
                setColorRed(255);
                setColorGreen(165);
                setColorBlue(0);
                entradaInvalida = 0;
                break;

            case 2: // VERMELHO
                setColorRed(255);
                setColorGreen(0);
                setColorBlue(0);
                entradaInvalida = 0;
                break;
            
            case 3: // VERDE
                setColorRed(0);
                setColorGreen(255);
                setColorBlue(0);
                entradaInvalida = 0;
                break;

            case 4: // AZUL
                setColorRed(0);   
                setColorGreen(0);
                setColorBlue(255);
                entradaInvalida = 0;
                break;

            case 5:
                printf("Indisponível");
                entradaInvalida = 0;
                break;


            default:
                printf("\n Opção Inválida!");
                break;
        }
    }
}

// [5] Traçar Rota
void tracarRota(struct GRAFO * grafo, struct Pilha **dijkstraRoute){

    // validar se já foram escolhidos pontos de entrada e saída
    if (pontoChegada != -1 && pontoPartida != -1){
        *dijkstraRoute = dijkstra(grafo, pontoPartida, pontoChegada);
        plot_route(&(*dijkstraRoute), grafo);

        desenharPino(grafo, pontoPartida);
    } else {
        printf("\n Você deve escolher os pontos de partida e entrada antes de traçar a rota");
        system("pause");
    }
}

// [6] Resetar Imagem
void resetarImagem() {
    FILE *fileMapa = fopen("../images/mapa_unisc.bmp", "wb");
    FILE *fileTemplate = fopen("../images/template.bmp", "rb");

    if (fileMapa == NULL || fileTemplate == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    // Define o tamanho do buffer
    const size_t bufferSize = 1024; // 1KB
    char buffer[bufferSize];

    // Leia do arquivo template e escreva no arquivo mapa_unisc em blocos
    while (!feof(fileTemplate)) {
        size_t bytesRead = fread(buffer, 1, bufferSize, fileTemplate);
        fwrite(buffer, 1, bytesRead, fileMapa);
    }

    // Feche ambos os arquivos
    fclose(fileMapa);
    fclose(fileTemplate);
}



