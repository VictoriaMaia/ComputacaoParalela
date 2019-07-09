#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double* lerMatriz(char nome[], int *linhas, int *colunas);
void imprimirMatrizTela(double m[], int linha, int coluna);
void escreverMatrizArquivo(char *arq, double m[], int linha, int coluna);
double* multiplicaMatrizes(double m1[], int l1, int c1, double m2[], int l2, int c2);
void liberarMatriz(double matriz[]);
