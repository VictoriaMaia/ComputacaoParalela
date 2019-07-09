#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float* lerMatriz(char nome[], int *linhas, int *colunas);
void imprimirMatrizTela(float m[], int linha, int coluna);
void escreverMatrizArquivo(char *arq, float m[], int linha, int coluna);
float* multiplicaMatrizes(float m1[], int l1, int c1, float m2[], int l2, int c2);
void liberarMatriz(float matriz[]);
