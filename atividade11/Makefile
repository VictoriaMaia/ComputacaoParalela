CCOMP = gcc -fopenmp
CC = gcc

all: com_openmp sem_openmp

com_openmp:
	$(CCOMP) omp.c -o appOmp -lm

sem_openmp:
	$(CC) serial.c -o app -lm

clean:
	rm app appOmp