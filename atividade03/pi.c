#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

float monteCarloPi(int n){
        float acertos = 0.0;
        float x,y;
        srand(time(NULL));
        for(int i = 0; i < n; i++){
                x = (float)rand()/ RAND_MAX;
                y = (float)rand()/ RAND_MAX;
                if( ((x*x) + (y*y)) < 1 ){
                        acertos = acertos + 1;
                }
        }
        return 4 * (acertos/n);
        // return acertos;
}

int main(int argc, char* argv[]){
        int n, tamBloco;
        float result, recebi;
        int numtask, rank;
        MPI_Status status;

        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &numtask);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        
        if(rank == 0){
                n = atoi(argv[1]);
                tamBloco = n/numtask;

                for(int i = 1; i < numtask; i++){
                        MPI_Send(&tamBloco, 1, MPI_INT, i, 0, MPI_COMM_WORLD);        
                }                
                result = monteCarloPi(tamBloco);
                for(int i = 1; i < numtask; i++){
                        MPI_Recv(&recebi, 1, MPI_FLOAT, i, 0, MPI_COMM_WORLD, &status);
                        result += recebi;
                }
                
                // result = 4 * (result/n);
                printf("Pi = %.5f \n", result);
        }
        else{
                MPI_Recv(&tamBloco, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
                result = monteCarloPi(tamBloco);
                MPI_Send(&result, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);        
        }

        MPI_Finalize();
        return 0;
}

