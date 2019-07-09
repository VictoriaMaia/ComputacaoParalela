#include <stdio.h>
#include <stdlib.h>
#include <string.h>


float* leMatriz(char nome[], int *linhas, int *colunas){
	//printf("Arquivo matriz: %s \nArquivo vetor: %s\nArquivo resultado: %s\n", argv[1], argv[2], argv[3]);
    
    FILE *arqMatriz;
    arqMatriz = fopen(nome, "r");
    
    if(arqMatriz == NULL){
        printf("Problema na criação do arquivo\n");
        return 0;
    }
    
    char *pch;
    size_t tamBuffer = 100;
    char *buffer_linha = (char*) malloc(tamBuffer * sizeof(char));

    // ######################################################################
    // ############################### MATRIZ ###############################
    // ######################################################################
    printf("\n###################################\n");
    printf("############# MATRIZ ##############\n");
    printf("###################################\n\n");
    int qnt_linha, qnt_colunaM;

    // LER NUMERO DE LINHAS
    getline(&buffer_linha, &tamBuffer, arqMatriz);
    // printf("%s", buffer_linha);
    qnt_linha = atoi(buffer_linha);
	*linhas = qnt_linha;

    // LER NUMERO DE COLUNAS
    getline(&buffer_linha, &tamBuffer, arqMatriz);
    qnt_colunaM = atoi(buffer_linha);
	*colunas = qnt_colunaM;

    printf("Num de linhas : %d\nNum de colunas : %d\n", qnt_linha, qnt_colunaM);

    float *matriz = (float*) malloc(qnt_linha*qnt_colunaM*sizeof(float));
    
    // PREENCHENDO A MATRIZ    
    for(int linha=0; linha < qnt_linha; linha++){
        if(getline(&buffer_linha, &tamBuffer, arqMatriz) != -1){
            // printf("Linha : %d\nLi: %s\n", linha,buffer_linha);
            pch = strtok(buffer_linha, ":");
            for(int coluna=0; coluna < qnt_colunaM; coluna++){
                if(pch != NULL){
                    matriz[linha*qnt_colunaM + coluna] = atof(pch);
                    // printf("Coluna: %d,  valor: %s\n", coluna, pch);
                    pch = strtok(NULL, ":");
                }                                
            }
        }
    }
    free(buffer_linha);
    fclose(arqMatriz);
	return matriz;
}

void imprimeTela(float m[], int linha, int coluna){
	printf("matriz\n");
	for(int i = 0; i < linha; i++){
		for(int j = 0; j < coluna; j++){
			printf("%.2f ", m[coluna*i + j]);
		}
		printf("\n");
	}
		printf("\n");
}


float* multiplica(float m1[], int l1, int c1, float m2[], int l2, int c2){
	float *mr = (float*) malloc(l1*c2*sizeof(float));
	
	
	for(int i = 0; i < l1; i++){
		for(int j = 0; j < c2; j++){
			mr[i*c2 + j] = 0;
			for(int k = 0; k < c1; k++){
				mr[i*c2 + j] += m1[i*c1 + k] * m2[k*c2 + j];
			}
		}
	}
	
	return mr;
}



void imprimirArquivo(char *arq, float m[], int linha, int coluna){
	FILE *arqResposta;
    arqResposta = fopen(arq, "w+");
    fprintf(arqResposta, "%d\n", linha);
    fprintf(arqResposta, "%d\n", coluna);
    int i, j;
    for(i=0; i < linha; i++){
		for(j = 0; j < coluna-1; j++){
			fprintf(arqResposta, "%.2f:", m[coluna*i + j]);
		}
        fprintf(arqResposta, "%.2f\n", m[coluna*i + j]);
    }
    
    fclose(arqResposta);
}

void liberarMatriz(float matriz[]){
	free(matriz);
}


int main (int argc, char * argv[]){
	int linhaM1, linhaM2, colunaM1, colunaM2;
	float *m1 = leMatriz("exemplo.txt", &linhaM1, &colunaM1);
	float *m2 = leMatriz("exemplo2.txt", &linhaM2, &colunaM2);
	//imprimeTela(m1, linha, coluna);
	//imprimirArquivo("saida.txt", m1, linha, coluna);
	imprimeTela(m2,linhaM2, colunaM2);
	
	printf("\n###################################\n");
    printf("########## MULTIPLICAÇÃO ##########\n");
    printf("###################################\n\n");

    float *m3 = multiplica(m1, linhaM1, colunaM1, m2,linhaM2, colunaM2);

	
	imprimeTela(m3,linhaM1, colunaM2);
	imprimirArquivo("saida.txt",m3,linhaM1, colunaM2);
	liberarMatriz(m1);
	liberarMatriz(m2);
	liberarMatriz(m3);
}



