#include "operacoesMatriz.h"

int main (int argc, char *argv[]){
    int l1,l2,c1,c2;
    double *m1, *m2, *mresult;
    // lendo as matrizes
    m1 = lerMatriz(argv[1], &l1, &c1);
    m2 = lerMatriz(argv[2], &l2, &c2);
    
    // verificando na tela se estão corretas
    imprimirMatrizTela(m1, l1, c1);
    imprimirMatrizTela(m2, l2, c2);

    if(c1 == l2){
        mresult = multiplicaMatrizes(m1, l1, c1, m2, l2, c2);
        imprimirMatrizTela(mresult, l1, c2);

        // escrevendo o resultado no arquivo recebido para resposta
        escreverMatrizArquivo(argv[3], mresult, l1, c2);
    }else{
        printf("Multiplicação não pode ser executada pois a coluna da matriz 1 é diferente da linha da matriz 2\n");
        liberarMatriz(m1);
        liberarMatriz(m2);    
        return 0;
    }
    
    // liberando as matrizes
    liberarMatriz(m1);
    liberarMatriz(m2);
    liberarMatriz(mresult);
    return 0;
}