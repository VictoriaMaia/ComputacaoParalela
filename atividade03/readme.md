## Atividade  03

É implementado o cálculo aproximado do valor de π através do método de Monte Carlo de forma paralelizada distribuído entre vários processos MPI exibindo o resultado com até 5 casas de precisão.

O programa recebe 1 parâmetro:

 - valor de n (número de iterações)

A execução é feito da seguinte forma:

    $ mpirun -np 2 ./pi 1000
