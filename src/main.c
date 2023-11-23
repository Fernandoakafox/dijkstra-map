#include "../include/GraphTools.h" // Biblioteca do desenvolvedor, para manipulação de grafos
#include "../include/Graphic.h"    // Biblioteca do desenvolvedor, para manipulação gráfica
#include "../include/ListTools.h"
#include <stdio.h>
#include <stdlib.h>


// .:| ========= Declaração das funções ========= |:.
void printDisplay();
void printMenu();

void setPontoPartida();
void setPontoChegada();
void limparPontos();
void tracarRota(struct GRAFO * grafo);


// .:| ========= Globais ========= |:.
int pontoPartida = -1;
int pontoChegada = -1;


// .:| ========= Constantes ========= |:.  
#define NUM_VERTICES 38



int main (){
    int opcao;
    struct GRAFO *grafo = criaGrafo(NUM_VERTICES); //temos vertice 0, logo se o nosso ultimo vertice é o 37, temos no total 38 vertices

    // inicializa o Grafo pelo arquivo csv
    importaGrafo(grafo);
        
    //struct Pilha *dijkstraRoute = dijkstra(grafo, 5, 17);
    //printf("TOPO: %i\n", dijkstraRoute->topo->vertice);
    
    //plot_route(&dijkstraRoute, grafo);
        

    while(1){
        printDisplay();
        printMenu();

        printf( "\n Opção: " );
        fflush( stdin );
        scanf("%i", &opcao);

        switch(opcao){

            case 0:
                exit(0);
                break;

            case 1:
                setPontoPartida();
                break;
            
            case 2:
                setPontoChegada();
                break;

            case 3:
                limparPontos();
                break;

            case 4: 
                tracarRota(grafo);
                break;


            default:
                printf("Escolha uma Opção Válida!");
                break;
        }

        printf( "\n" );
        system( "clear" );   // limpar tela
    }

}


void printDisplay() {
    printf("\n| === DISPLAY === |");
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

    printf("\n");
    printf("\n");
}


void printMenu() {
    printf("\n .:| ======================= MENU ======================= |:. ");
    printf("\n     [1] Escolher ponto de partida ");
    printf("\n     [2] Escolher ponto de chegada ");
    printf("\n     [3] Resetar pontos de Partida e Chegada ");
    printf("\n     [4] Traçar rota ");
    printf("\n     [0] Sair");
    printf("\n  :| ======================= ==== ======================= |: \n");
}




// [1] Escolher Ponto de Partida
void setPontoPartida () {
    int valorValido = 0;
    int entrada;

    while (!valorValido){
        printf("\n Digite o valor do ponto de Partida: ");
        scanf("%i", &entrada);
        // TODO adicionar validação de pontos existentes e válidos
        if (entrada >= 0 && entrada < NUM_VERTICES){
            valorValido = 1;
        } else {
            printf("\n Valor inválido!");
        }
    }

    pontoPartida = entrada;
    printf("\n Ponto de Partida selecionado!");
} 


// [2] Escolher Ponto de Chegada
void setPontoChegada () {
    int valorValido = 0;
    int entrada;

    while (!valorValido){
        printf("\n Digite o valor do ponto de Partida: ");
        scanf("%i", &entrada);
        
        if (entrada >= 0 && entrada < NUM_VERTICES){
            valorValido = 1;
        } else {
            printf("\n Valor inválido!");
        }
    }

    pontoChegada = entrada;
    printf("\n Ponto de Chegada selecionado!");
}


// [5] Limpar Pontos de Partida e Chegada
void limparPontos() {
    pontoChegada = -1;
    pontoPartida = -1;

    printf("Pontos de Partida e Chegada Resetados");
}


// [6] Traçar Rota
void tracarRota(struct GRAFO * grafo) {

    // validar se já foram escolhidos pontos de entrada e saída
    if (pontoChegada != -1 && pontoPartida != -1){
        dijkstra(grafo, pontoPartida, pontoChegada);
    } else {
        printf("\n Você deve escolher os pontos de partida e entrada entes de traçar a rota");
    }
}


