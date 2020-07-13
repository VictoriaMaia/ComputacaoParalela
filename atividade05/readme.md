## Atividade  05

É implementado a multiplicação de matrizes utilizando operações ponto-a-ponto bloqueantes do MPI. 

Semelhante a atividade 2, o programa recebe três parâmetros:

1. O nome do arquivo contendo a matriz;
2. O nome do arquivo contendo o vetor;
3. O nome do arquivo que armazenará o resultado.

O arquivo da matriz deve seguir o seguinte formato:

- a primeira linha deve conter o número de linhas da matriz;
- a segunda linha deve conter o número de colunas da matriz;
- o restante das linhas deve conter a matriz, linha por linha, com os elementos separados por : (dois pontos).

Por exemplo, uma matriz com 3 linhas e 4 colunas seria assim representada:

3

4

1.0:1.0:1.0:1.0

1.0:1.0:1.0:1.0

1.0:1.0:1.0:1.0

A execução é feita da seguinte forma:

    $ mpicc multiplicacaoMatrizVetorParalelo.c
    $ mpirun -np 2 ./a.out matriz.txt vetor.txt resultado.txt
