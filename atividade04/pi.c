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
        return acertos;
}

int main(int argc, char* argv[]){
        int n, tamBloco;
        float result, result_final;
        int numtask, rank;
        MPI_Status status;

        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &numtask);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        
        n = atoi(argv[1]);
        tamBloco = n/numtask;

        result = monteCarloPi(tamBloco);

        MPI_Reduce(&result, &result_final, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

        if(rank == 0){        
            result_final = 4 * (result_final/n);
            printf("Pi = %.5f \n", result_final);
        }
    
        MPI_Finalize();
        return 0;
}