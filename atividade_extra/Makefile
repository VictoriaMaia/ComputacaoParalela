CC = gcc

all: gerar.o
	$(CC) multiplicaMatriz.o operacoesMatriz.o -o app
	rm *.o 

gerar.o:
	$(CC) multiplicaMatriz.c operacoesMatriz.c -c

clean:
	rm app