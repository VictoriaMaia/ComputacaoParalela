#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

double f(double x) {
   double return_val = 0.0;
   return_val = cos(x * log(1.0/x));
   return return_val;
}

int main(int argc, char *argv[]) {
   // Valor da integral
   double integralGeral, integralLocal;

   // Limites do intervalo
   double a, b;
   // Número de trapézios
   int n_trap;
   // Base do trapézio
   double h, x;
   int i;

   int numtask, rank;

   double infoProb[2];
   int inicio, fim;

   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &numtask);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);

   // todo mundo lê
   n_trap = atoi(argv[3]);

   inicio = rank * ((n_trap)/numtask) + 1;
   fim = (rank + 1) *  ((n_trap)/numtask);

   if(rank == (numtask-1)){ //gambiarra
      fim = n_trap - 1;
   }

   // printf("Sou rank %d, inicio: %d, fim: %d \n", rank, inicio, fim);

   if(rank == 0){
      a = atof(argv[1]);
      b = atof(argv[2]);
  
      h = (b - a) / n_trap;
      integralLocal = (f(a) + f(b))/2.0;

      x = a;

      infoProb[0] = a;
      infoProb[1] = h; 

      // mandando os valores de A e H
      MPI_Bcast(infoProb, 2, MPI_DOUBLE, 0, MPI_COMM_WORLD);

      for (i = inicio; i <= fim; i++) {
         x += h;
         integralLocal += f(x);
      }
      
      // receber os valores calculados da integral
      MPI_Reduce(&integralLocal, &integralGeral, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

      integralGeral *= h;
      printf("%d trapézios, estimativa de %.2f a %.2f = %.5f\n", n_trap, a, b, integralGeral);


   }
   else{
      MPI_Bcast(infoProb, 2, MPI_DOUBLE, 0, MPI_COMM_WORLD);

      // infoProb[0] = a;
      // infoProb[1] = h; 
      x = infoProb[0] + inicio*infoProb[1];
      integralLocal = f(x);
      
      for (i = inicio+1; i <= fim; i++){
         x += infoProb[1];
         integralLocal += f(x);
      }

      MPI_Reduce(&integralLocal, &integralGeral, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
   }


   MPI_Finalize();
   return 0;
}
