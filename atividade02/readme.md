## Atividade  02

É realizado a implementação serial da multiplicação matriz/vetor.

O programa recebe três parâmetros:

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

O arquivo do vetor tem o seguinte formato:

- a primeira linha deve conter o tamanho
- o restante das linhas deve conter os valores separados por : (dois pontos)

Por exemplo um vetor de 4 elementos seria informado assim:

4

1.0:1.0:1.0:1.0

A execução é feita da seguinte forma:

    $ gcc multiplicacaoMatrizVetor.c
    $ ./a.out matriz.txt vetor.txt resultado.txt
    
