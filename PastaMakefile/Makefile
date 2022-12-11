all: TrabalhoFinal.e

TrabalhoFinal.e: Trabalho.o processo.o leitura.o
    gcc -o TrabalhoFinal.c Trabalho.o processo.o leitura.o

Trabalho.o: Trabalho.c
    gcc -o Trabalho.o -c Trabalho.c

processo.o: processo.c
    gcc -o processo.o -c processo.c

leitura.o: leitura.c
    gcc -o leitura.o -c leitura.c

clean:
    rm -f *.o TrabalhoFinal.e
