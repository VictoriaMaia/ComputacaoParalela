#include "mpi.h"
#include "operacoesMatriz.h"

int main (int argc, char * argv[]){
    int lM,lV,cM,cV;
    float *mat, *vet, *mresult, *mresFinal, *minha_subM;
    int rank, numtask;
    int infoVetor[2], infoSubMatriz[2];
    MPI_Status status;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtask);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        // carregando a matriz e o vetor para a memória
        mat = lerMatriz(argv[1], &lM, &cM);
        vet = lerMatriz(argv[2], &lV, &cV);

        if(cM != lV){
            printf("Valores de tamanhos distintos. Isso vai dar errado!\n");
        }

        //armazena as informações do vetor
        infoVetor[0] = lV;
        infoVetor[1] = cV;

        // broadcast - manda o vetor para todos os processos
        MPI_Bcast(infoVetor, 2, MPI_INT, 0, MPI_COMM_WORLD);        
        MPI_Bcast(vet, lV*cV, MPI_FLOAT, 0, MPI_COMM_WORLD);
        
        //armazena as informações da matriz
        infoSubMatriz[0] = lM / numtask;
        infoSubMatriz[1] = cM;
        
        // manda o tamanho da submatriz
        MPI_Bcast(infoSubMatriz, 2, MPI_INT, 0, MPI_COMM_WORLD);
        minha_subM = (float*) malloc(infoSubMatriz[0]*infoSubMatriz[1]*sizeof(float));
       
        // manda os dados da submatriz
        MPI_Scatter(mat, infoSubMatriz[0]*infoSubMatriz[1] , MPI_FLOAT, 
               minha_subM, infoSubMatriz[0]*infoSubMatriz[1], MPI_FLOAT, 
               0, MPI_COMM_WORLD);

        mresFinal = (float*) malloc(lM*cV*sizeof(float));        
        mresult = (float*) malloc(infoSubMatriz[0]*infoVetor[1]*sizeof(float));
        // calculo local
        multiplicaMatrizes(mresult, minha_subM, infoSubMatriz[0], infoSubMatriz[1], vet, lV, cV);

        // receber a contribuicao dos outros ranks
        MPI_Gather(mresult, infoSubMatriz[0]*cV, MPI_FLOAT, mresFinal, infoSubMatriz[0]*cV, MPI_FLOAT, 0, MPI_COMM_WORLD);
        
        escreverMatrizArquivo(argv[3] ,mresFinal, lM, cV);

        liberarMatriz(mat);
        liberarMatriz(vet);
        liberarMatriz(minha_subM);
        liberarMatriz(mresult);
        liberarMatriz(mresFinal);
    }
    else{
        MPI_Bcast(infoVetor, 2, MPI_INT, 0, MPI_COMM_WORLD);
        vet = (float*) malloc(infoVetor[0]*infoVetor[1]*sizeof(float));             
        MPI_Bcast(vet, infoVetor[0]*infoVetor[1], MPI_FLOAT, 0, MPI_COMM_WORLD);

        MPI_Bcast(infoSubMatriz, 2, MPI_INT, 0, MPI_COMM_WORLD);        
        minha_subM = (float*) malloc(infoSubMatriz[0]*infoSubMatriz[1]*sizeof(float));
        MPI_Scatter(mat, infoSubMatriz[0]*infoSubMatriz[1] , MPI_FLOAT, 
                    minha_subM, infoSubMatriz[0]*infoSubMatriz[1], MPI_FLOAT, 
                    0, MPI_COMM_WORLD);


        // calculo local
        mresult = (float*) malloc(infoSubMatriz[0]*infoVetor[1]*sizeof(float));
        multiplicaMatrizes(mresult, minha_subM, infoSubMatriz[0], infoSubMatriz[1], vet, infoVetor[0], infoVetor[1]);

        // envio dos resultados
        MPI_Gather(mresult, infoSubMatriz[0]*infoVetor[1], MPI_FLOAT, mresFinal, infoSubMatriz[0]*infoVetor[1], MPI_FLOAT, 0, MPI_COMM_WORLD);

        liberarMatriz(vet);
        liberarMatriz(minha_subM);
        liberarMatriz(mresult);
    }
    
    MPI_Finalize();
    return 0;
}