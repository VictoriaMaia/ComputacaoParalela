CCOMP = mpicc -fopenmp

all: com_openmp

com_openmp:
	$(CCOMP) multiplicacaoMatrizVetorParalelo.c operacoesMatriz.c -o app

clean:
	rm app