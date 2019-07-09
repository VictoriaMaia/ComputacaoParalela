#include "mpi.h"
#include "operacoesMatriz.h"

int main (int argc, char * argv[]){
    int lM,lV,cM,cV;
    float *mat, *vet, *mresult;
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

        infoVetor[0] = lV;
        infoVetor[1] = cV;

        for(int i=1; i < numtask; i++){
            // mandei o tamanho da linha e coluna do vetor
            MPI_Send(infoVetor, 2, MPI_INT, i, 0, MPI_COMM_WORLD);
            // mandei o vetor
            MPI_Send(vet, lV*cV, MPI_FLOAT, i, 1, MPI_COMM_WORLD);
        }
        
        infoSubMatriz[0] = lM / numtask;
        infoSubMatriz[1] = cM;
        
        for(int i=1; i<numtask; i++){
            // mandei o tamanho da linha e coluna da submatriz
            MPI_Send(infoSubMatriz, 2, MPI_INT, i, 2, MPI_COMM_WORLD);
            // mandei a submatriz
            MPI_Send(mat + i*(infoSubMatriz[0]*cM), infoSubMatriz[0]*cM, MPI_FLOAT, i, 3, MPI_COMM_WORLD);
        }

        mresult = (float*) malloc(lM*cV*sizeof(float));        
        // calculo local
        multiplicaMatrizes(mresult, mat, infoSubMatriz[0], cM, vet, lV, cV);

        // receber a contribuicao dos outros ranks
        for(int i = 1; i < numtask; i++){
            MPI_Recv(mresult + i*(infoSubMatriz[0]*cV), infoSubMatriz[0]*cV, MPI_FLOAT, i, 4, MPI_COMM_WORLD, &status);
        }

        escreverMatrizArquivo(argv[3] ,mresult, lM, cV);

        liberarMatriz(mat);
        liberarMatriz(vet);
        liberarMatriz(mresult);
    }
    else{
        // recebo as informacoes de linha e coluna do vetor
        MPI_Recv(infoVetor, 2, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        vet = (float*) malloc(infoVetor[0]*infoVetor[1]*sizeof(float));         
        // recebo o vetor do rank 0  
        MPI_Recv(vet, infoVetor[0]*infoVetor[1], MPI_FLOAT, 0, 1, MPI_COMM_WORLD, &status);
        
        // recebo as informacoes de linha e coluna da submatriz
        MPI_Recv(infoSubMatriz, 2, MPI_INT, 0, 2, MPI_COMM_WORLD, &status);
        mat = (float*) malloc(infoSubMatriz[0]*infoSubMatriz[1]*sizeof(float));
        // recebo a submatriz
        MPI_Recv(mat, infoSubMatriz[0]*infoSubMatriz[1], MPI_FLOAT, 0, 3, MPI_COMM_WORLD, &status);

        // calculo local
        mresult = (float*) malloc(infoSubMatriz[0]*infoVetor[1]*sizeof(float));
        multiplicaMatrizes(mresult, mat, infoSubMatriz[0], infoSubMatriz[1], vet, infoVetor[0], infoVetor[1]);

        // enviar contribuição do calculo
        MPI_Send(mresult, infoSubMatriz[0]*infoVetor[1], MPI_FLOAT, 0, 4, MPI_COMM_WORLD);

        liberarMatriz(mat);
        liberarMatriz(vet);
        liberarMatriz(mresult);
    }
    
    MPI_Finalize();
    return 0;
}