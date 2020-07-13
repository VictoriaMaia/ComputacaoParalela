## Atividade  07

É implementado um programa paralelo que faça o cálculo da integral de uma função usando o método do trapézio.

O programa recebe três parâmetros:

1. O início do intervalo;
2. O fim do intervalo;
3. A precisão, ou número de trapézios.

A execução é feita da seguinte forma:

    $ mpicc paralelo.c -o paralelo -lm
    $ mpirun -np 8 ./paralelo 1.0 10000.0 80000000 
