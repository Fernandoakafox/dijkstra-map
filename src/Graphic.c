#include "../include/Graphic.h"
#include "../include/ListTools.h"
#include "../include/GraphTools.h"
#include <stdio.h>
#include <stdlib.h>

#define IMG_WIDTH 1280
#define IMG_HEIGHT 758

// Graphic.h

#ifndef GRAPHIC_H
#define GRAPHIC_H

// Function declarations
int getColorRed();
int getColorGreen();
int getColorBlue();
void setColorRed(int newColor);
void setColorGreen(int newColor);
void setColorBlue(int newColor);

#endif // GRAPHIC_H



// .:| ========= Globais ========= |:.
int red = 255;
int green = 165;
int blue = 0;

int espessura = 10;



/***********************************************/
/* Funções                                     */
/***********************************************/

/************************************************  
 * plot_pixel                                   *
 * objetivo: mudar a cor de um pixel            *
 * entrada : arquivo bmp, coordenadas do pixel, cores em hexadecimal: r, g, b , posição do primeiro byte de pixels  *
 * saida   : alteração da cor de um pixel       *
 ************************************************/
void plot_pixel(FILE *file, int y, int x, int r, int g, int b, int pixel_data_offset) {
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // verifica se as coordenadas estão fora das bordas
    if (x < 0 || x >= IMG_WIDTH || y < 0 || y >= IMG_HEIGHT) {
        fprintf(stderr, "As coordenadas dos pixels estão fora da borda!\n");
        return;
    }

    int padding = (4 - (IMG_WIDTH * 3) % 4) % 4;
    int pos = (y * (IMG_WIDTH * 3 + padding) + x * 3);

    // Aponta o cursor para a posição do primeiro pixel + pos, ou seja, aponta para o byte onde a intensidade da cor blue será alterada
    fseek(file, pixel_data_offset + pos, SEEK_SET);
    fputc(b, file);
    // Aponta o cursor para a posição do primeiro pixel + pos + 1, ou seja, aponta para o byte onde a intensidade da cor green será alterada
    fseek(file, pixel_data_offset + pos + 1, SEEK_SET);
    fputc(g, file);
    // Aponta o cursor para a posição do primeiro pixel + pos + 2, ou seja, aponta para o primeiro byte onde a intensidade da cor red será alterada
    fseek(file, pixel_data_offset + pos + 2, SEEK_SET);
    fputc(r, file);
}

/************************************************  
 * plot_line                                    *
 * objetivo: mudar a cor de uma linha de pixels *
 * entrada : arquivo bmp, coordenadas do pixel, cores em hexadecimal: r, g, b , posição do primeiro byte de pixels  *
 * saida   : alteração da cor de uma linha de pixels       *
 ************************************************/

void plot_line (int x0, int y0, int x1, int y1, int espessura, int red, int green, int blue){
    y0 = IMG_HEIGHT - y0; //correção do y0
    y1 = IMG_HEIGHT - y1; //correção do y1
    FILE *file; // Ponteiro para o tipo FILE chamado file, que será usado para manipular o arquivo.
    file = fopen("../images/mapa_unisc.bmp", "rb+"); // Abre o arquivo BMP em modo de leitura e escrita binária
    if (file == NULL) {
        perror("Erro ao abrir arquivo, verifique se o executavel esta dentro do diretorio src\n");
        return;
    }

    unsigned char header[54]; //array de 54 bytes que será usado para armazenar o cabeçalho do arquivo BMP
    fread(header, sizeof(unsigned char), 54, file); // Lê 54 bytes do arquivo e armazena no array header. Esses 54 bytes representam o cabeçalho do arquivo BMP.

    // Obtém o deslocamento para os dados de pixel a partir do cabeçalho
    /*No formato de arquivo BMP, os primeiros 14 bytes do cabeçalho contêm informações gerais sobre o arquivo, e a partir do 15º byte começam a aparecer 
    informações mais detalhadas, incluindo o deslocamento para os dados de pixel. O deslocamento para os dados de pixel é um valor de 4 bytes que indica 
    a posição no arquivo BMP onde começam os dados que representam os pixels da imagem.*/
    int pixel_data_offset; // Será usada para armazenar o deslocamento para os dados de pixel no arquivo BMP
    pixel_data_offset = *(int *)&header[10]; //armazena a posição do primeiro byte de pixels

    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    for (int ty = -espessura / 2; ty <= espessura / 2; ++ty) {
        for (int tx = -espessura / 2; tx <= espessura / 2; ++tx) {
            int nx0 = x0 + tx, ny0 = y0 + ty;
            int nx1 = x1 + tx, ny1 = y1 + ty;

            while (1) {
                plot_pixel(file, ny0, nx0, red, green, blue, pixel_data_offset);
                if (nx0 == nx1 && ny0 == ny1)
                    break;
                e2 = 2 * err;
                if (e2 >= dy) {
                    err += dy;
                    nx0 += sx;
                }
                if (e2 <= dx) {
                    err += dx;
                    ny0 += sy;
                }
            }
        }
    }
    // Fecha o arquivo
    fclose(file);
}
//plot_route
//recebe pilha e grafo
//na primeira vez que manda as coordenadas para plot_line, manda o primeiro vertice e o segundo
//apartir da segunda vez, manda a ultima a sofrer pop e a nova
//recebe uma pilha de vertices
//enquanto tiver elementos na pilha
    //vertice = pop
    //grafo->coordenadas[vertice].x
    //grafo->coordenadas[vertice].y
    //vertice2 = pop
    //grafo->coordenadas[vertice2].x
    //grafo->coordenadas[vertice2].y

void plot_route(struct Pilha **head, struct GRAFO *grafo){
    int vertice1, vertice2;
    if((*head)->topo != NULL){
        printf("aqui\n");
        vertice1 = pop(head);
        vertice2 = pop(head);
        plot_line(grafo->coordenadas[vertice1].x , grafo->coordenadas[vertice1].y , grafo->coordenadas[vertice2].x , grafo->coordenadas[vertice2].y , 10 , red, green, blue);
    }
    while((*head)->topo != NULL){
        vertice1 = vertice2;
        vertice2 = pop(head);
        plot_line(grafo->coordenadas[vertice1].x , grafo->coordenadas[vertice1].y , grafo->coordenadas[vertice2].x , grafo->coordenadas[vertice2].y , 10 , red, green, blue);
    }
}




// ===== GETTERS ================================================ 

int getEspessura() {
    return espessura;
}

int getColorRed() {
    return red;
}

int getColorGreen() {
    return green;
}

int getColorBlue() {
    return blue;
}

// ===== SETTERS ================================================ 

void setEspessura(int novaEspessura) {
    espessura = novaEspessura;
}

void setColorRed(int newColor) {
    red = newColor;
}

void setColorGreen(int newColor) {
    green = newColor;
}

void setColorBlue(int newColor) {
    blue = newColor;
}


