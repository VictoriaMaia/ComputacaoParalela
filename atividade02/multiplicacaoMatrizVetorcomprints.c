#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]){
    printf("Arquivo matriz: %s \nArquivo vetor: %s\nArquivo resultado: %s\n", argv[1], argv[2], argv[3]);
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
    printf("\n###################################\n");
    printf("############# MATRIZ ##############\n");
    printf("###################################\n\n");
    int qnt_linha, qnt_colunaM;

    // LER NUMERO DE LINHAS
    getline(&buffer_linha, &tamBuffer, arqMatriz);
    // printf("%s", buffer_linha);
    qnt_linha = atoi(buffer_linha);

    // LER NUMERO DE COLUNAS
    getline(&buffer_linha, &tamBuffer, arqMatriz);
    qnt_colunaM = atoi(buffer_linha);

    printf("Num de linhas : %d\nNum de colunas : %d\n", qnt_linha, qnt_colunaM);

    float matriz[qnt_linha][qnt_colunaM];
    
    // PREENCHENDO A MATRIZ    
    for(int linha=0; linha < qnt_linha; linha++){
        if(getline(&buffer_linha, &tamBuffer, arqMatriz) != -1){
            // printf("Linha : %d\nLi: %s\n", linha,buffer_linha);
            pch = strtok(buffer_linha, ":");
            for(int coluna=0; coluna < qnt_colunaM; coluna++){
                if(pch != NULL){
                    matriz[linha][coluna] = atof(pch);
                    // printf("Coluna: %d,  valor: %s\n", coluna, pch);
                    pch = strtok(NULL, ":");
                }                                
            }
        }
    }

    printf("Imprimindo matriz \n");
    for(int linha = 0; linha < qnt_linha; linha++){
        for (int coluna = 0; coluna < qnt_colunaM; coluna++ ){
            printf("[ %.2f ]", matriz[linha][coluna]);
        }
        printf("\n");
    }


    // ######################################################################
    // ############################### VETOR ################################
    // ######################################################################
    printf("\n###################################\n");
    printf("############# MATRIZ ##############\n");
    printf("###################################\n\n");
    int qnt_colunaV;
    
    // LER NUMERO DE COLUNAS
    getline(&buffer_linha, &tamBuffer, arqVetor);
    qnt_colunaV = atoi(buffer_linha);

    printf("Num de colunas : %d\n", qnt_colunaV);
    float vetor[qnt_colunaV];

    // PREENCHENDO O VETOR
    getline(&buffer_linha, &tamBuffer, arqVetor);
    pch = strtok(buffer_linha, ":");
    for(int coluna = 0; coluna < qnt_colunaV; coluna++){
        if(pch != NULL){
            vetor[coluna] = atof(pch);
            // printf("Coluna: %d,  valor: %s\n", coluna, pch);
            pch = strtok(NULL, ":");
        }   
    }

    printf("Imprimindo vetor: \n");
    for(int coluna = 0; coluna < qnt_colunaV; coluna++){
        printf("[ %.2f ]", vetor[coluna]);
    }
    printf("\n");


    // ######################################################################
    // ####################### MULTIPLICAÇÃO ################################
    // ######################################################################

    printf("\n###################################\n");
    printf("########## MULTIPLICAÇÃO ##########\n");
    printf("###################################\n\n");

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

    printf("Imprimindo vetor: \n");
    for(int i=0; i < qnt_linha; i++){
        printf("[ %.2f ]", resposta[i]);
    }
    printf("\n");

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