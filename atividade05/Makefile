CC = mpicc

all: gerar.o
	$(CC) multiplicacaoMatrizVetorParalelo.o operacoesMatriz.o -o app
	rm *.o 

gerar.o:
	$(CC) multiplicacaoMatrizVetorParalelo.c operacoesMatriz.c -c

clean:
	rm app