#include "operacoesMatriz.h"

double* lerMatriz(char nome[], int *linhas, int *colunas){    
    FILE *arqMatriz;
    arqMatriz = fopen(nome, "r");
    
    if(arqMatriz == NULL){
        printf("Problema no arquivo\n");
        return 0;
    }
    
    char *pch;
    size_t tamBuffer = 100;
    char *buffer_linha = (char*) malloc(tamBuffer * sizeof(char));
    int qnt_linha, qnt_coluna;

    // LER NUMERO DE LINHAS
    getline(&buffer_linha, &tamBuffer, arqMatriz);
    qnt_linha = atoi(buffer_linha);
	*linhas = qnt_linha;

    // LER NUMERO DE COLUNAS
    getline(&buffer_linha, &tamBuffer, arqMatriz);
    qnt_coluna = atoi(buffer_linha);
	*colunas = qnt_coluna;

    double *matriz = (double*) malloc(qnt_linha*qnt_coluna*sizeof(double));
    
    // PREENCHENDO A MATRIZ    
    for(int linha=0; linha < qnt_linha; linha++){
        if(getline(&buffer_linha, &tamBuffer, arqMatriz) != -1){
            pch = strtok(buffer_linha, ":");
            for(int coluna=0; coluna < qnt_coluna; coluna++){
                if(pch != NULL){
                    matriz[linha*qnt_coluna + coluna] = atof(pch);
                    pch = strtok(NULL, ":");
                }                                
            }
        }
    }

    free(buffer_linha);
    fclose(arqMatriz);
	return matriz;
}

void imprimirMatrizTela(double m[], int linha, int coluna){
    for(int i = 0; i < linha; i++){
        for (int j = 0; j < coluna; j++ ){
            printf("[ %.2f ]", m[i*coluna + j]);
        }
        printf("\n");
    }
    printf("\n");
}


void multiplicaMatrizes(double mr[], double m1[], int l1, int c1, double m2[], int l2, int c2){	
    int i,j,k;

    # pragma omp parallel for schedule(static) private(i,j,k) shared(m1,m2,mr,l1,c1,c2)    
	for(i = 0; i < l1; i++){
		for(j = 0; j < c2; j++){
			mr[i*c2 + j] = 0;
			for(k = 0; k < c1; k++){
				mr[i*c2 + j] += m1[i*c1 + k] * m2[k*c2 + j];
			}
		}
	}	
}


void escreverMatrizArquivo(char *arq, double m[], int linha, int coluna){
	FILE *arqResposta;
    arqResposta = fopen(arq, "w");
    fprintf(arqResposta, "%d\n", linha);
    fprintf(arqResposta, "%d\n", coluna);
    int i, j;
    for(i=0; i < linha; i++){
		for(j = 0; j < coluna-1; j++){
			fprintf(arqResposta, "%.2f:", m[i*coluna + j]);
		}
        fprintf(arqResposta, "%.2f\n", m[i*coluna + j]);
    }
    
    fclose(arqResposta);
}

void liberarMatriz(double matriz[]){
	free(matriz);
}
