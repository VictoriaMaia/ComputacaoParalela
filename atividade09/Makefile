CCOMP = gcc -fopenmp
CC = gcc

all: com_openmp sem_openmp

com_openmp:
	$(CCOMP) multiplicaMatriz.c operacoesMatriz.c -o appOmp

sem_openmp:
	$(CC) multiplicaMatriz.c operacoesMatriz.c -o app

clean:
	rm app appOmp