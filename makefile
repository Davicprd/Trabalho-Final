all: Trabalho.exe

Trabalho.exe:Trabalho.o processo.o 
	gcc -o Trabalho.exe Trabalho.o processo.o 

Trabalho.o:Trabalho.c
	gcc -o Trabalho.o -c Trabalho.c

processo.o:processo.c
	gcc -o processo.o -c processo.c

clean:
	rm -f *.o Trabalho.e
