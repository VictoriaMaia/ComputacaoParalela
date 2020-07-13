## Atividade  08

É implementado um programa que realiza broadcast de uma mensagem entre processos sendo utilizado apenas primitivas ponto-a-ponto, considerando um número fixo de 16 processos.

Cada função irá aplicar uma topologia diferente. Será utilizado a topologia mesh e a topologia em anel. Esse código recebe como parâmetro o tamanho do array a ser distribuído. Em seguinda, no rank 0, o vetor é inicializado com o valor 0 em todas as posições e depois a topologia anel é utilizada para distribuir o array. Em seguida, o rank 0 agora preenche o array com valores iguais a 1000. O novo array é distribuído com a topologia mesh.

A execução é feita da seguinte forma:

    $ mpicc broadcast_topology.c -o broadcast_topology
    $ mpirun -np 16 ./broadcast_topology 5
