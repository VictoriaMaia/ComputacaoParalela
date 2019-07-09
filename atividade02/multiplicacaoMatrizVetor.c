#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]){
    FILE *arqMatriz, *arqVetor, *arqResposta;
    arqMatriz = fopen(argv[1], "r");
    arqVetor = fopen(argv[2], "r");
    arqResposta = fopen(argv[3], "w+");
    if(arqMatriz == NULL || arqVetor == NULL){
        printf("Problema na criação do arquivo\n");
        return 0;
    }
    char *pch;
    size_t tamBuffer = 100;
    char *buffer_linha = malloc(tamBuffer * sizeof(char));

    // ######################################################################
    // ############################### MATRIZ ###############################
    // ######################################################################
    int qnt_linha, qnt_colunaM;

    // LER NUMERO DE LINHAS
    getline(&buffer_linha, &tamBuffer, arqMatriz);
    qnt_linha = atoi(buffer_linha);

    // LER NUMERO DE COLUNAS
    getline(&buffer_linha, &tamBuffer, arqMatriz);
    qnt_colunaM = atoi(buffer_linha);

    float matriz[qnt_linha][qnt_colunaM];
    
    // PREENCHENDO A MATRIZ    
    for(int linha=0; linha < qnt_linha; linha++){
        if(getline(&buffer_linha, &tamBuffer, arqMatriz) != -1){
            pch = strtok(buffer_linha, ":");
            for(int coluna=0; coluna < qnt_colunaM; coluna++){
                if(pch != NULL){
                    matriz[linha][coluna] = atof(pch);
                    pch = strtok(NULL, ":");
                }                                
            }
        }
    }

    // ######################################################################
    // ############################### VETOR ################################
    // ######################################################################
    int qnt_colunaV;
    
    // LER NUMERO DE COLUNAS
    getline(&buffer_linha, &tamBuffer, arqVetor);
    qnt_colunaV = atoi(buffer_linha);

    float vetor[qnt_colunaV];

    // PREENCHENDO O VETOR
    getline(&buffer_linha, &tamBuffer, arqVetor);
    pch = strtok(buffer_linha, ":");
    for(int coluna = 0; coluna < qnt_colunaV; coluna++){
        if(pch != NULL){
            vetor[coluna] = atof(pch);
            pch = strtok(NULL, ":");
        }   
    }

    // ######################################################################
    // ####################### MULTIPLICAÇÃO ################################
    // ######################################################################

    float resposta[qnt_linha];
    for(int i=0; i < qnt_linha; i++){
        resposta[i] = 0;
    }
    if(qnt_colunaM == qnt_colunaV){
        for(int linha = 0; linha < qnt_linha; linha++){
            for(int coluna = 0; coluna < qnt_colunaM; coluna++){
                resposta[linha] += matriz[linha][coluna] * vetor[coluna]; 
            }
        }
    }


    // ######################################################################
    // ############################ RESPOSTA ################################
    // ######################################################################
    fprintf(arqResposta, "%d\n", qnt_linha);
    for(int i=0; i < qnt_linha; i++){
        if(i == (qnt_linha-1)){
            fprintf(arqResposta, "%.2f\n", resposta[i]);
        }
        else{
            fprintf(arqResposta, "%.2f:", resposta[i]);
        }        
    }
     

    fclose(arqMatriz);
    fclose(arqVetor);
    fclose(arqResposta);
    free(buffer_linha);
    return 0;
}