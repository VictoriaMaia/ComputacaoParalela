#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x) {
   double return_val = 0.0;
   return_val = cos(x * log(1.0/x));
   return return_val;
}

int main(int argc, char *argv[]) {
   // Valor da integral
   double integral; 
   // Limites do intervalo
   double a, b;
   // Número de trapézios
   int n;
   // Base do trapézio
   double h;
   double x;
   int i;

   a = atof(argv[1]);
   b = atof(argv[2]);
   n = atoi(argv[3]);

   h = (b - a) / n;
   integral = (f(a) + f(b))/2.0;
   
   int trab = n/2;
   x = a;
    printf("meu inicio : 1, meu fim : %d\n", trab);
   for (i = 1; i <= trab ; i++) {
      x += h;
      integral += f(x);
   }

   double x1, integ;
   
   x1 = a + (trab+1)*h;
//    printf("meu x3 : %f\n", x1);
   integ = f(x1);
   printf("minha integ incial: %f\n", integ);

    printf("meu inicio : %d, meu fim : %d\n", trab+2, n-1);
   for(i = trab+2; i <= n-1; i++){
      x1 += h;
      integ += f(x1); 
      printf("%f\n", integ);
      if(integ < -633){
            printf("estou no i: %d", i);
            break;
       }
   }
   
//    printf("meu integral %f \n", integral);
   printf("meu integ %f \n", integ);

   integral = integral + integ;
   
   integral *= h;
   printf("%d trapézios, estimativa de %.2f a %.2f = %.5f\n", n, a, b, integral);

   return 0;
}